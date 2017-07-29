#include "head_tracker.h"

// define the face frame features required to be computed by this application

static const DWORD c_FaceFrameFeatures =
FaceFrameFeatures::FaceFrameFeatures_BoundingBoxInColorSpace
| FaceFrameFeatures::FaceFrameFeatures_PointsInColorSpace
| FaceFrameFeatures::FaceFrameFeatures_PointsInColorSpace
| FaceFrameFeatures::FaceFrameFeatures_RotationOrientation
| FaceFrameFeatures::FaceFrameFeatures_Happy
| FaceFrameFeatures::FaceFrameFeatures_RightEyeClosed
| FaceFrameFeatures::FaceFrameFeatures_LeftEyeClosed
| FaceFrameFeatures::FaceFrameFeatures_MouthOpen
| FaceFrameFeatures::FaceFrameFeatures_MouthMoved
| FaceFrameFeatures::FaceFrameFeatures_LookingAway
| FaceFrameFeatures::FaceFrameFeatures_Glasses
| FaceFrameFeatures::FaceFrameFeatures_FaceEngagement;
//| FaceFrameFeatures::;

head_tracker::head_tracker() :
	m_hWnd(NULL),
	m_nStartTime(0),
	m_nLastCounter(0),
	m_fFreq(0),
	m_nNextStatusTime(0),
	m_nFramesSinceUpdate(0),
	m_pKinectSensor(nullptr),
	m_pDepthFrameReader(nullptr),
	m_pCoordinateMapper(nullptr),
	m_pColorFrameReader(nullptr),
	m_pBodyFrameReader(nullptr)
{
	__yal_log(__YAL_INFO, "Creating head_tracker object\n");
	LARGE_INTEGER qpf = { 0 };
	if (QueryPerformanceFrequency(&qpf))
	{
		m_fFreq = double(qpf.QuadPart);
	}
	for (int i = 0; i < BODY_COUNT; i++)
	{
		m_pFaceFrameSources[i] = nullptr;
		m_pFaceFrameReaders[i] = nullptr;
	}

	__yal_log(__YAL_INFO, "Getting default kinnect sensor\n");

	HRESULT hr;
	hr = GetDefaultKinectSensor(&m_pKinectSensor);
	handleError(hr, "Get Default Kinect Sensor failed", 1);

	__yal_log(__YAL_INFO, "Opening/subscribing to the kinect sensor\n");
	hr = m_pKinectSensor->Open();
	handleError(hr, "Open Kinect Sensor failed", 1);

	if (m_pKinectSensor)
	{
		__yal_log(__YAL_DBG, "Setting up readers and sources\n");
		setup_readers();
	}
	else
	{
		__yal_log(__YAL_DBG, "Failed getting default kinect sensor\n");
	}
	__yal_log(__YAL_INFO, "Leaving head_tracker constructor\n");
}


head_tracker::~head_tracker()
{
	__yal_log(__YAL_INFO, "Destroying head_tracker object\n");
	
	release_readers();

	// close the Kinect Sensor
	if (m_pKinectSensor)
	{
		__yal_log(__YAL_INFO, "Closing/unsubscribing the kinect sensor\n");
		HRESULT hr = m_pKinectSensor->Close();
		handleError(hr, "Close Kinect Sensor failed", 0);
	}

	SafeRelease(m_pKinectSensor);
}

void head_tracker::release_readers()
{
	__yal_log(__YAL_INFO, "Releasing readers and so on\n");
	// done with face sources and readers
	for (int i = 0; i < BODY_COUNT; i++)
	{
		SafeRelease(m_pFaceFrameSources[i]);
		SafeRelease(m_pFaceFrameReaders[i]);
	}

	// done with body frame reader
	SafeRelease(m_pBodyFrameReader);

	// done with color frame reader
	SafeRelease(m_pColorFrameReader);

	// done with coordinate mapper
	SafeRelease(m_pCoordinateMapper);
}

void head_tracker::setup_readers()
{
	__yal_log(__YAL_INFO, "Setting up the kinect readers\n");

	// Initialize Kinect and get color, body and face readers
	IColorFrameSource* pColorFrameSource = nullptr;
	IBodyFrameSource* pBodyFrameSource = nullptr;

	HRESULT hr;
	hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
	handleError(hr, "Get coordinate mapper failed", 1);
	
	hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
	handleError(hr, "Get color frame source failed", 1);

	hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
	handleError(hr, "Color frame source: open reader failed", 1);

	hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
	handleError(hr, "get body frame source failed", 1);

	hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
	handleError(hr, "Body frame source: open reader failed", 1);

	// create a face frame source + reader to track each body in the fov
	for (int i = 0; i < BODY_COUNT; i++)
	{
		// create the face frame source by specifying the required face frame features
		hr = CreateFaceFrameSource(m_pKinectSensor, 0, c_FaceFrameFeatures, &m_pFaceFrameSources[i]);
		handleError(hr, "Create Face Frame Source failed", 0);

		// open the corresponding reader
		if (m_pFaceFrameSources[i])
		{
			hr = m_pFaceFrameSources[i]->OpenReader(&m_pFaceFrameReaders[i]);
			handleError(hr, "Face Frame Sources: open reader failed", 0);
		}
	}

	SafeRelease(pColorFrameSource);
	SafeRelease(pBodyFrameSource);
}