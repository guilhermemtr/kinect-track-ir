#include "head_data.h"




#ifndef __NORMALIZED_HEAD_DATA__
#define __NORMALIZED_HEAD_DATA__

typedef double head_data_normalized_t;

typedef struct normalized_axis_s {
	head_data_normalized_t axis[HEAD_DATA_AXIS];

	inline struct normalized_axis_s operator*(struct normalized_axis_s o) {
		struct normalized_axis_s n;
		for (int i = 0; i < HEAD_DATA_AXIS; i++)
		{
			n.axis[i] = axis[i] * o.axis[i];
		}
		return n;
	}
} normalized_axis_t, normalized_pos_t, normalized_rot_t;


class normalized_head_data
{
public:
	normalized_head_data();
	~normalized_head_data();

	uint64_t get_id();
	normalized_pos_t get_pos();
	normalized_rot_t get_rot();

	normalized_head_data operator*(normalized_head_data d);

	void update_data(uint64_t id, normalized_pos_t pos, normalized_rot_t rot);

	// shouldn't exist: only for debugging
	void log_normalized_head_data(char *prefix);
private:
	normalized_pos_t pos;
	normalized_rot_t rot;
	uint64_t id;
};

#endif