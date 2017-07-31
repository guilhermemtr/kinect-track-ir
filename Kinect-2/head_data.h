#include <stdint.h>

#include "yal.h"

#ifndef __HEAD_DATA__
#define __HEAD_DATA__

#define HEAD_DATA_AXIS 3


typedef int64_t head_data_axis_t;
#define ABS_HEAD_DATA_AXIS(val) (INT64_MAX & val)

typedef struct {
	head_data_axis_t axis[HEAD_DATA_AXIS];
} pos_t;

typedef struct {
	head_data_axis_t axis[HEAD_DATA_AXIS];
} rot_t;

enum axis {x = 0, y, z};
enum axis_rot { yaw = 0, pitch, roll };

class head_data
{
public:
	head_data();
	~head_data();

	uint64_t get_id();
	pos_t get_pos();
	rot_t get_rot();

	void update_data(uint64_t id, pos_t pos, rot_t rot);

	// shouldn't exist: only for debugging
	void log_head_data(void);
private:
	pos_t pos;
	rot_t rot;
	uint64_t id;
};

#endif