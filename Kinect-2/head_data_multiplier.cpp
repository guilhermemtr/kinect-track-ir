#include "head_data_multiplier.h"


head_data_multiplier::head_data_multiplier(double x_factor, double y_factor, double z_factor, double yaw_factor, double pitch_factor, double roll_factor)
{
	normalized_pos_t pos_factor = { x_factor, y_factor, z_factor };
	normalized_rot_t rot_factor = { yaw_factor, pitch_factor, roll_factor };
	this->multiplier.update_data(0, pos_factor, rot_factor);
}

head_data_multiplier::head_data_multiplier():
	head_data_multiplier(1.0, 1.0, 1.0, 1.0, 1.0, 1.0)
{
}

head_data_multiplier::~head_data_multiplier()
{
}

void head_data_multiplier::callback(normalized_head_data hd)
{
	this->publish(multiplier * hd);
}