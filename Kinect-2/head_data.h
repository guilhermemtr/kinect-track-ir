#include <stdint.h>

#include "yal.h"

#ifndef __HEAD_DATA__
#define __HEAD_DATA__

#define HEAD_DATA_AXIS 3


typedef int64_t head_data_axis_t;

#define ABS_HEAD_DATA_AXIS(val) (INT64_MAX & val)

typedef struct axis_s {
	head_data_axis_t axis[HEAD_DATA_AXIS];

	inline struct axis_s operator=(struct axis_s o) {
		for (int i = 0; i < HEAD_DATA_AXIS; i++)
		{
			axis[i] = o.axis[i];
		}

		return o;
	}

	inline struct axis_s operator+(struct axis_s o) {
		struct axis_s n;
		for (int i = 0; i < HEAD_DATA_AXIS; i++)
		{
			n.axis[i] = axis[i] + o.axis[i];
		}
		return n;
	}

	inline struct axis_s operator-(struct axis_s o) {
		struct axis_s n;
		for (int i = 0; i < HEAD_DATA_AXIS; i++)
		{
			n.axis[i] = axis[i] - o.axis[i];
		}
		return n;
	}

	inline struct axis_s operator/(int64_t count) {
		struct axis_s n;
		for (int i = 0; i < HEAD_DATA_AXIS; i++)
		{
			n.axis[i] = axis[i] / count;
		}
		return n;
	}

	inline void operator+=(struct axis_s o) {
		for (int i = 0; i < HEAD_DATA_AXIS; i++)
		{
			axis[i] = axis[i] + o.axis[i];
		}
	}

	inline void operator-=(struct axis_s o) {
		for (int i = 0; i < HEAD_DATA_AXIS; i++)
		{
			axis[i] = axis[i] - o.axis[i];
		}
	}
} axis_t, pos_t, rot_t;


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

	head_data operator+(head_data d);
	head_data operator-(head_data d);
	head_data operator/(int64_t count);
	void operator+=(head_data d);
	void operator-=(head_data d);


	void update_data(uint64_t id, pos_t pos, rot_t rot);

	// shouldn't exist: only for debugging
	void log_head_data(char *prefix);
private:
	pos_t pos;
	rot_t rot;
	uint64_t id;
};

#endif