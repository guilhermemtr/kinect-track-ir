#include <stdint.h>

#include "subscriber.h"
#include "publisher.h"

#include "head_data.h"

#define __AVG_HEAD_POS_WIDTH__  (512 >> 1)
#define __AVG_HEAD_POS_HEIGHT__ (424 >> 1)
#define __AVG_HEAD_POS_DEPTH__  (1600 >> 1)

class average_head_position: public subscriber<head_data>, public publisher<head_data>
{
public:
	average_head_position(float factor);
	~average_head_position();

	void callback(head_data hd);
	head_data get_center();
private:
	bool account(head_data hd);
	bool account_val(head_data_axis_t v_hd, head_data_axis_t v_c);

	uint64_t count;
	head_data aggregate;
	head_data perfect_center;

	float factor;
};

