#include "depth_frame_data.h"



depth_frame_data::depth_frame_data(IDepthFrameReader * depthFrameReader) :
	m_pBuffer(NULL),
	m_nBufferSize(0),
	m_nWidth(0),
	m_nHeight(0),
	m_nDepthMinReliableDistance(0),
	m_nDepthMaxDistance(0),
	m_pDepthFrame(NULL),
	m_pFrameDescription(NULL)
{
	HRESULT hr = depthFrameReader->AcquireLatestFrame(&m_pDepthFrame);

	if (SUCCEEDED(hr))
	{
		__yal_log(__YAL_MISC, "depth_frame_data::depth_frame_data: got depth frame");
		hr = m_pDepthFrame->get_FrameDescription(&m_pFrameDescription);
		if (SUCCEEDED(hr))
		{
			hr = m_pFrameDescription->get_Width(&m_nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pFrameDescription->get_Height(&m_nHeight);
		}

		if (SUCCEEDED(hr))
		{
			SafeRelease(m_pFrameDescription);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pDepthFrame->get_DepthMinReliableDistance(&m_nDepthMinReliableDistance);
		}

		if (SUCCEEDED(hr))
		{
			// In order to see the full range of depth (including the less reliable far field depth)
			// we are setting nDepthMaxDistance to the extreme potential depth threshold
			// nDepthMaxDistance = USHRT_MAX;

			// Note:  If you wish to filter by reliable depth distance, uncomment the following line.
			hr = m_pDepthFrame->get_DepthMaxReliableDistance(&m_nDepthMaxDistance);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pDepthFrame->AccessUnderlyingBuffer(&m_nBufferSize, &m_pBuffer);
		}

		//if (FAILED(hr))
		//{
		//	printf("error depth frame description: %d\n", hr);
		//}
		SafeRelease(m_pFrameDescription);
	}
	
	// failed getting depth frame
	if (FAILED(hr))
	{
		__yal_log(__YAL_MISC, "error getting depth frame: %d\t\t%p\n", hr, m_pDepthFrame);
		m_pDepthFrame = NULL;
	}
}


depth_frame_data::~depth_frame_data()
{
	SafeRelease(m_pDepthFrame);
}

USHORT depth_frame_data::get_depth(int x, int y)
{
	if (!m_pBuffer || x >= m_nWidth || x < 0 || y > m_nHeight || y < 0)
	{
		return 0;
	}

	return m_pBuffer[y*m_nWidth + x];
}

USHORT depth_frame_data::get_min_reliable_distance()
{
	return m_nDepthMinReliableDistance;
}

USHORT depth_frame_data::get_max_distance()
{
	return m_nDepthMaxDistance;
}

int depth_frame_data::get_width()
{
	return m_nWidth;
}

int depth_frame_data::get_height()
{
	return m_nHeight;
}