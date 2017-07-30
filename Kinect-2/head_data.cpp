#include "head_data.h"



head_data::head_data()
{
	__yal_log(__YAL_INFO, "Creating head_data object\n");
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		this->rot.axis[i] = 0;
		this->pos.axis[i] = 0;
	}
	this->id = 0;
}


head_data::~head_data()
{
	__yal_log(__YAL_INFO, "Destroying head_data object\n");
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

void head_data::update_data(uint64_t id, pos_t pos, rot_t rot)
{
	this->pos = pos;
	this->rot = rot;
	this->id = id;

}

void head_data::log_head_data(void)
{
	__yal_log(__YAL_DBG, "\t\tRotation\t\tPosition\n");
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		__yal_log(__YAL_DBG, "%d:\t\t%d\t\t%d\n", i, rot.axis[i], pos.axis[i]);
	}
}
