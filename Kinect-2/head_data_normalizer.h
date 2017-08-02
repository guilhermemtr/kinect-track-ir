#include <algorithm>

#include "head_data.h"
#include "normalized_head_data.h"

#include "subscriber.h"
#include "publisher.h"

#include "average_head_positioning.h"

#ifndef __HEAD_DATA_NORMALIZER__
#define __HEAD_DATA_NORMALIZER__

const int64_t max_head_data_pos[HEAD_DATA_AXIS][2] = { {0,512}, {0,424}, {500,5000} };
const int64_t max_head_data_rot[HEAD_DATA_AXIS][2] = { {-180,180}, {-180,180}, {-180,180} };

class head_data_normalizer: public subscriber<head_data>, public publisher<normalized_head_data>
{
public:
	head_data_normalizer(average_head_positioning* ahp);
	~head_data_normalizer();
	void callback(head_data hd);

private:
	average_head_positioning* ahp;
};

#endif