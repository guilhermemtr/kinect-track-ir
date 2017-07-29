#include <Kinect.h>

#include "utils.h"

class depth_frame_data
{
public:
	depth_frame_data(IDepthFrameReader * depthFrameReader);
	~depth_frame_data();

	USHORT get_depth(int x, int y);
	USHORT get_min_reliable_distance();
	USHORT get_max_distance();

	int get_width();
	int get_height();

private:
	UINT16 *m_pBuffer;
	UINT m_nBufferSize;

	int m_nWidth;
	int m_nHeight;

	USHORT m_nDepthMinReliableDistance;
	USHORT m_nDepthMaxDistance;
};