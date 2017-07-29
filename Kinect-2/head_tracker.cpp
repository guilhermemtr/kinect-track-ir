#include "head_tracker.h"

// define the face frame features required to be computed by this application

static const DWORD c_FaceFrameFeatures =
FaceFrameFeatures::FaceFrameFeatures_BoundingBoxInColorSpace
| FaceFrameFeatures::FaceFrameFeatures_BoundingBoxInInfraredSpace
| FaceFrameFeatures::FaceFrameFeatures_PointsInColorSpace
| FaceFrameFeatures::FaceFrameFeatures_PointsInInfraredSpace
| FaceFrameFeatures::FaceFrameFeatures_RotationOrientation;
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
	handleError(hr, 1, "Get Default Kinect Sensor failed\n");

	__yal_log(__YAL_INFO, "Opening/subscribing to the kinect sensor\n");
	hr = m_pKinectSensor->Open();
	handleError(hr, 1, "Open Kinect Sensor failed\n");

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
		handleError(hr, 0, "Close Kinect Sensor failed");
	}

	SafeRelease(m_pKinectSensor);
}

void head_tracker::setup_readers()
{
	__yal_log(__YAL_INFO, "Setting up the kinect readers\n");

	// Initialize Kinect and get color, body and face readers
	IColorFrameSource* pColorFrameSource = nullptr;
	IBodyFrameSource* pBodyFrameSource = nullptr;

	HRESULT hr;
	hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
	handleError(hr, 1, "Get coordinate mapper failed\n");

	hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
	handleError(hr, 1, "Get color frame source failed\n");

	hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
	handleError(hr, 1, "Color frame source: open reader failed\n");

	hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
	handleError(hr, 1, "get body frame source failed\n");

	hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
	handleError(hr, 1, "Body frame source: open reader failed\n");

	// create a face frame source + reader to track each body in the fov
	for (int i = 0; i < BODY_COUNT; i++)
	{
		// create the face frame source by specifying the required face frame features
		hr = CreateFaceFrameSource(m_pKinectSensor, 0, c_FaceFrameFeatures, &m_pFaceFrameSources[i]);
		handleError(hr, 1, "Create Face Frame Source failed: %d\n", i);

		// open the corresponding reader
		hr = m_pFaceFrameSources[i]->OpenReader(&m_pFaceFrameReaders[i]);
		handleError(hr, 1, "Face Frame Sources: open reader failed: %d\n", i);
	}

	SafeRelease(pColorFrameSource);
	SafeRelease(pBodyFrameSource);
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

void head_tracker::setup()
{
	if (m_pKinectSensor)
	{
		__yal_log(__YAL_DBG, "Setting up readers and sources\n");
		setup_readers();
	}
	else
	{
		__yal_log(__YAL_DBG, "Failed getting default kinect sensor\n");
	}
}

void head_tracker::update()
{
	
	if (!m_pColorFrameReader || !m_pBodyFrameReader)
	{
		return;
	}
	
	HRESULT hr;
	IBody* ppBodies[BODY_COUNT] = { 0 };
	bool bHaveBodyData = SUCCEEDED(update_bodies(ppBodies));

	// iterate through each face reader
	for (int iFace = 0; iFace < BODY_COUNT; ++iFace)
	{
		

		// retrieve the latest face frame from this reader
		IFaceFrame* pFaceFrame = nullptr;
		hr = m_pFaceFrameReaders[iFace]->AcquireLatestFrame(&pFaceFrame);

		BOOLEAN bFaceTracked = false;
		if (SUCCEEDED(hr) && pFaceFrame != nullptr)
		{
			// check if a valid face is tracked in this face frame
			hr = pFaceFrame->get_IsTrackingIdValid(&bFaceTracked);
			__yal_log(__YAL_INFO, "I'm watching you!\n");
		}

		if (SUCCEEDED(hr))
		{
			if (bFaceTracked)
			{
				printf("tracking face\n");
				IFaceFrameResult* pFaceFrameResult = nullptr;
				RectI faceBox = { 0 };
				PointF facePoints[FacePointType::FacePointType_Count];
				Vector4 faceRotation;
				DetectionResult faceProperties[FaceProperty::FaceProperty_Count];

				hr = pFaceFrame->get_FaceFrameResult(&pFaceFrameResult);

				// need to verify if pFaceFrameResult contains data before trying to access it
				if (SUCCEEDED(hr) && pFaceFrameResult != nullptr)
				{
					// hr = pFaceFrameResult->get_FaceBoundingBoxInColorSpace(&faceBox);
					hr = pFaceFrameResult->get_FaceBoundingBoxInInfraredSpace(&faceBox);

					pos_t pos = m_hHeads[iFace]->get_pos();
					rot_t rot = m_hHeads[iFace]->get_rot();
					

					if (SUCCEEDED(hr))
					{
						hr = pFaceFrameResult->GetFacePointsInColorSpace(FacePointType::FacePointType_Count, facePoints);
					}

					if (SUCCEEDED(hr))
					{
						hr = pFaceFrameResult->get_FaceRotationQuaternion(&faceRotation);
					}

					// extract face rotation in degrees as Euler angles
					getFaceRotationInDegrees(&faceRotation, &(rot.axis[yaw]), &(rot.axis[pitch]), &(rot.axis[roll]));
					m_hHeads[iFace]->set_rot(rot);
					printf("Yaw:%d\nPitch:%d\nRoll:%d\n", rot.axis[yaw], rot.axis[pitch], rot.axis[roll]);
				}

				SafeRelease(pFaceFrameResult);
			}
			else
			{
				printf("not tracking face\n");
				// face tracking is not valid - attempt to fix the issue
				// a valid body is required to perform this step
				if (bHaveBodyData)
				{
					// check if the corresponding body is tracked 
					// if this is true then update the face frame source to track this body
					IBody* pBody = ppBodies[iFace];
					if (pBody != nullptr)
					{
						BOOLEAN bTracked = false;
						hr = pBody->get_IsTracked(&bTracked);

						UINT64 bodyTId;
						if (SUCCEEDED(hr) && bTracked)
						{
							// get the tracking ID of this body
							hr = pBody->get_TrackingId(&bodyTId);
							if (SUCCEEDED(hr))
							{
								// update the face frame source with the tracking ID
								m_pFaceFrameSources[iFace]->put_TrackingId(bodyTId);
							}
						}
					}
				}
			}
		}

		SafeRelease(pFaceFrame);
	}

	if (bHaveBodyData)
	{
		for (int i = 0; i < _countof(ppBodies); ++i)
		{
			SafeRelease(ppBodies[i]);
		}
	}
}

HRESULT head_tracker::update_bodies(IBody** ppBodies)
{
	HRESULT hr = E_FAIL;

	if (m_pBodyFrameReader != nullptr)
	{
		IBodyFrame* pBodyFrame = nullptr;
		hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);
		if (SUCCEEDED(hr))
		{
			hr = pBodyFrame->GetAndRefreshBodyData(BODY_COUNT, ppBodies);
		}
		SafeRelease(pBodyFrame);
	}

	return hr;
}