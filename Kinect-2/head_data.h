#include <stdint.h>

#include "yal.h"

#define HEAD_DATA_AXIS 3

typedef struct {
	int64_t axis[HEAD_DATA_AXIS];
} pos_t;

typedef struct {
	int axis[HEAD_DATA_AXIS];
} rot_t;

enum axis {x = 0, y, z};
enum axis_rot { yaw = 0, pitch, roll };

class head_data
{
public:
	head_data();
	~head_data();

	pos_t get_pos();
	rot_t get_rot();

	void set_pos(pos_t pos);
	void set_rot(rot_t rot);

private:
	pos_t pos;
	rot_t rot;
};

