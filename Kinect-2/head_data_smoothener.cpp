#include "head_data_smoothener.h"



head_data_smoothener::head_data_smoothener(float update_ratio)
{
	active = false;
	last = head_data();
	current_value = last;
	this->update_ratio = update_ratio;
}


head_data_smoothener::~head_data_smoothener()
{
}

void head_data_smoothener::callback(head_data hd)
{
	if (!active)
	{
		active = true;
		last = hd;
		current_value = hd;
	}
	else 
	{
		this->update(hd);
	}
}

void head_data_smoothener::update(head_data hd)
{
	if (last.get_id() != hd.get_id())
	{
		pos_t c_p = current_value.get_pos();
		rot_t c_r = current_value.get_rot();

		pos_t r_p = hd.get_pos();
		rot_t r_r = hd.get_rot();

		pos_t n_p;
		rot_t n_r;

		for (int i = 0; i < HEAD_DATA_AXIS; i++)
		{
			n_p.axis[i] = r_p.axis[i] * update_ratio + c_p.axis[i] * (1.0 - update_ratio);
			n_r.axis[i] = r_r.axis[i] * update_ratio + c_r.axis[i] * (1.0 - update_ratio);
		}

		current_value.update_data(hd.get_id(), n_p, n_r);
		last = hd;

		this->publish(current_value);
	}
}
