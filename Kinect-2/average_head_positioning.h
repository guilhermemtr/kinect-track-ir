#include <stdint.h>

#include "subscriber.h"
#include "publisher.h"

#include "head_data.h"

#define __AVG_HEAD_POS_WIDTH__  (512)
#define __AVG_HEAD_POS_HEIGHT__ (424)
#define __AVG_HEAD_POS_DEPTH__  (600)
#define __MAX_HEAD_ROT_YAW__    (180)
#define __MAX_HEAD_ROT_PITCH__  (180)
#define __MAX_HEAD_ROT_ROLL__   (180)

class average_head_positioning: public subscriber<head_data>, public publisher<head_data>
{
public:
	average_head_positioning(float factor);
	~average_head_positioning();

	void callback(head_data hd);
	head_data get_center();
private:
	bool account(head_data hd);
	bool account_val(head_data_axis_t v_hd, head_data_axis_t v_c, head_data_axis_t range);

	uint64_t count;
	head_data aggregate;
	head_data perfect_center;

	float factor;

	const pos_t range_pos = { __AVG_HEAD_POS_WIDTH__ , __AVG_HEAD_POS_HEIGHT__ , __AVG_HEAD_POS_DEPTH__ };
	const rot_t range_rot = { __MAX_HEAD_ROT_YAW__ , __MAX_HEAD_ROT_PITCH__ , __MAX_HEAD_ROT_ROLL__ };
};

