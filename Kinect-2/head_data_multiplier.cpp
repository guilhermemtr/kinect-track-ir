#include "head_data_multiplier.h"


head_data_multiplier::head_data_multiplier(double x_factor, double y_factor, double z_factor, double yaw_factor, double pitch_factor, double roll_factor)
{
	normalized_pos_t pos_factor = { x_factor, y_factor, z_factor };
	normalized_rot_t rot_factor = { yaw_factor, pitch_factor, roll_factor };
	this->multiplying_factor.update_data(0, pos_factor, rot_factor);
	this->maximum_value.update_data(0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0});
	this->multiplier.update_data(0, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 });
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
	this->update_maximum(hd);
	this->publish(multiplier * hd);
}

void head_data_multiplier::update_maximum(normalized_head_data hd)
{
	normalized_pos_t npos_hd = hd.get_pos();
	normalized_rot_t nrot_hd = hd.get_rot();

	normalized_pos_t npos_max = maximum_value.get_pos();
	normalized_rot_t nrot_max = maximum_value.get_rot();

	normalized_pos_t npos_mult = multiplier.get_pos();
	normalized_rot_t nrot_mult = multiplier.get_rot();

	normalized_pos_t npos_mult_factor = multiplying_factor.get_pos();
	normalized_rot_t nrot_mult_factor = multiplying_factor.get_rot();

	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		// absolute value
		npos_hd.axis[i] = fabs(npos_hd.axis[i]);
		nrot_hd.axis[i] = fabs(nrot_hd.axis[i]);

		if (npos_hd.axis[i] > npos_max.axis[i] || (maximum_value.get_id() < 30 && npos_hd.axis[i] > 0.0))
		{
			npos_max.axis[i] = npos_hd.axis[i];
			npos_mult.axis[i] = npos_mult_factor.axis[i] / npos_max.axis[i];
		}

		if (nrot_hd.axis[i] > nrot_max.axis[i])
		{
			nrot_max.axis[i] = nrot_hd.axis[i];
			nrot_mult.axis[i] = nrot_mult_factor.axis[i] / nrot_max.axis[i];
		}
	}

	maximum_value.update_data(maximum_value.get_id() + 1, npos_max, nrot_max);
	multiplier.update_data(multiplier.get_id() + 1, npos_mult, nrot_mult);
}
