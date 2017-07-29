#include <stdint.h>

#include "yal.h"

typedef int64_t pos_t;
typedef uint64_t rot_t;

#define HEAD_DATA_AXIS 3

enum axis {x = 0, y, z};

class head_data
{
public:
	head_data();
	~head_data();

	void get_pos(pos_t **pos);
	void get_rot(rot_t **rot);

	void set_pos(pos_t *pos);
	void set_rot(rot_t *rot);

private:
	pos_t pos [HEAD_DATA_AXIS];
	rot_t rot [HEAD_DATA_AXIS];
};

