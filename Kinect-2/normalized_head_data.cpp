#include "normalized_head_data.h"



normalized_head_data::normalized_head_data()
{
	__yal_log(__YAL_MISC, "Creating normalized_head_data object\n");
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		this->rot.axis[i] = 0.0;
		this->pos.axis[i] = 0.0;
	}
	this->id = 0;
}

normalized_head_data::~normalized_head_data()
{
}

uint64_t normalized_head_data::get_id()
{
	return id;
}

normalized_pos_t normalized_head_data::get_pos()
{
	return pos;
}

normalized_rot_t normalized_head_data::get_rot()
{
	return rot;
}

normalized_head_data normalized_head_data::operator*(normalized_head_data d)
{
	normalized_pos_t d_p = d.get_pos();
	normalized_rot_t d_r = d.get_rot();

	normalized_head_data n;
	n.update_data(id, d_p * pos, d_r * rot);
	return n;
}

void normalized_head_data::update_data(uint64_t id, normalized_pos_t pos, normalized_rot_t rot)
{
	this->pos = pos;
	this->rot = rot;
	this->id = id;
}

void normalized_head_data::log_normalized_head_data(char * prefix)
{
	__yal_log(__YAL_DBG, "%s\t\tRotation\tPosition\n", prefix);
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		__yal_log(__YAL_DBG, "%s%ld:\t\t%lf\t\t%lf\n", prefix, i, rot.axis[i], pos.axis[i]);
	}
}
