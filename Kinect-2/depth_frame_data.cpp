#include "depth_frame_data.h"



depth_frame_data::depth_frame_data(IDepthFrameReader * depthFrameReader) :
	m_pBuffer(NULL),
	m_nBufferSize(0),
	m_nWidth(0),
	m_nHeight(0),
	m_nDepthMinReliableDistance(0),
	m_nDepthMaxDistance(0)
{
	IDepthFrame* pDepthFrame = NULL;
	HRESULT hr = depthFrameReader->AcquireLatestFrame(&pDepthFrame);

	IFrameDescription* pFrameDescription = NULL;


	if (SUCCEEDED(hr))
	{
		hr = pDepthFrame->get_FrameDescription(&pFrameDescription);
	}

	if (SUCCEEDED(hr))
	{
		hr = pFrameDescription->get_Width(&m_nWidth);
	}

	if (SUCCEEDED(hr))
	{
		hr = pFrameDescription->get_Height(&m_nHeight);
	}

	if (SUCCEEDED(hr))
	{
		hr = pDepthFrame->get_DepthMinReliableDistance(&m_nDepthMinReliableDistance);
	}

	if (SUCCEEDED(hr))
	{
		// In order to see the full range of depth (including the less reliable far field depth)
		// we are setting nDepthMaxDistance to the extreme potential depth threshold
		// nDepthMaxDistance = USHRT_MAX;

		// Note:  If you wish to filter by reliable depth distance, uncomment the following line.
		hr = pDepthFrame->get_DepthMaxReliableDistance(&m_nDepthMaxDistance);
	}

	if (SUCCEEDED(hr))
	{
		hr = pDepthFrame->AccessUnderlyingBuffer(&m_nBufferSize, &m_pBuffer);
	}

	SafeRelease(pFrameDescription);
	SafeRelease(pDepthFrame);
}


depth_frame_data::~depth_frame_data()
{
	// free(m_pBuffer);
}

USHORT depth_frame_data::get_depth(int x, int y)
{
	if (x > m_nWidth || y > m_nHeight)
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