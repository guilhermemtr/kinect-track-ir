#include "head_data.h"



head_data::head_data()
{
	__yal_log(__YAL_INFO, "Creating head_data object\n");
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		this->rot.axis[i] = 0;
		this->pos.axis[i] = 0;
	}
}


head_data::~head_data()
{
	__yal_log(__YAL_INFO, "Destroying head_data object\n");
}


pos_t head_data::get_pos()
{
	return this->pos;
}

rot_t head_data::get_rot()
{
	return this->rot;
}

void head_data::set_pos(pos_t pos)
{
	this->pos = pos;
}

void head_data::set_rot(rot_t rot)
{
	this->rot = rot;
}

void head_data::log_head_data(void)
{
	__yal_log(__YAL_INFO, "\t\tRotation\t\tPosition\n");
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		__yal_log(__YAL_INFO, "%d:\t\t%d\t\t%d\n", i, rot.axis[i], pos.axis[i]);
	}
}
