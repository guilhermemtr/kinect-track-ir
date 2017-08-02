#include "head_data.h"



head_data::head_data()
{
	__yal_log(__YAL_MISC, "Creating head_data object\n");
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		this->rot.axis[i] = 0;
		this->pos.axis[i] = 0;
	}
	this->id = 0;
}


head_data::~head_data()
{
	__yal_log(__YAL_MISC, "Destroying head_data object\n");
}


uint64_t head_data::get_id()
{
	return this->id;
}

pos_t head_data::get_pos()
{
	return this->pos;
}

rot_t head_data::get_rot()
{
	return this->rot;
}

head_data head_data::operator+(head_data d)
{
	pos_t d_p = d.get_pos();
	rot_t d_r = d.get_rot();

	head_data n;
	n.update_data(id, d_p + pos, d_r + rot);
	return n;
}

head_data head_data::operator-(head_data d)
{
	pos_t d_p = d.get_pos();
	rot_t d_r = d.get_rot();

	head_data n;
	n.update_data(id, d_p - pos, d_r - rot);
	return n;
}

head_data head_data::operator/(int64_t count)
{
	head_data n;
	n.update_data(id, pos/count, rot/count);
	return n;
}

void head_data::operator+=(head_data d)
{
	pos = pos + d.get_pos();
	rot = rot + d.get_rot();
}

void head_data::operator-=(head_data d)
{
	pos = pos - d.get_pos();
	rot = rot - d.get_rot();
}

void head_data::update_data(uint64_t id, pos_t pos, rot_t rot)
{
	this->pos = pos;
	this->rot = rot;
	this->id = id;
}

void head_data::log_head_data(char *prefix)
{
	__yal_log(__YAL_DBG, "%s\t\tRotation\tPosition\n", prefix);
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		__yal_log(__YAL_DBG, "%s%ld:\t\t%ld\t\t%ld\n", prefix, i, rot.axis[i], pos.axis[i]);
	}
}
