#include <Kinect.h>
#include <Kinect.Face.h>


#include "publisher.h"

#include "utils.h"

#include "head_data.h"
#include "depth_frame_data.h"



class head_tracker: public publisher<head_data>
{
public:
	head_tracker();
	~head_tracker();

	void setup();
	void update();
	head_data* get_head_data(int i);

private:
	void setup_readers();
	void release_readers();

	void update_face(int i, IBody** ppBodies, bool bHaveBodyData, depth_frame_data& dfd);
	HRESULT update_bodies(IBody** ppBodies);

	//  Head tracking variables
	head_data *m_hHeads[BODY_COUNT];

	// Instance variables
	HWND                    m_hWnd;
	INT64                   m_nStartTime;
	INT64                   m_nLastCounter;
	double                  m_fFreq;
	INT64                   m_nNextStatusTime;
	DWORD                   m_nFramesSinceUpdate;

	// Current Kinect
	IKinectSensor*          m_pKinectSensor;

	// Depth reader
	IDepthFrameReader*      m_pDepthFrameReader;

	// Coordinate mapper
	ICoordinateMapper*     m_pCoordinateMapper;

	// Color reader
	IColorFrameReader*     m_pColorFrameReader;

	// Body reader
	IBodyFrameReader*      m_pBodyFrameReader;

	// Face sources
	IFaceFrameSource*	   m_pFaceFrameSources[BODY_COUNT];

	// Face readers
	IFaceFrameReader*	   m_pFaceFrameReaders[BODY_COUNT];
};

