#include "head_data.h"



head_data::head_data()
{
	__yal_log(__YAL_INFO, "Creating head_data object\n");
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		this->rot[i] = 0;
		this->pos[i] = 0;
	}
}


head_data::~head_data()
{
	__yal_log(__YAL_INFO, "Destroying head_data object\n");
}


void head_data::get_pos(pos_t **pos)
{
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		*(pos[i]) = this->pos[i];
	}
}

void head_data::get_rot(rot_t **rot)
{
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		*(rot[i]) = this->rot[i];
	}
}

void head_data::set_pos(pos_t *pos)
{
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		this->pos[i] = pos[i];
	}
}

void head_data::set_rot(rot_t *rot)
{
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		this->rot[i] = rot[i];
	}
}