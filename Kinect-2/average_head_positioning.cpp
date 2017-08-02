#include "average_head_positioning.h"



average_head_positioning::average_head_positioning(float factor)
{
	pos_t center = {0, 0, 0};
	rot_t no_rot = {0, 0, 0};
	perfect_center.update_data(0, center, no_rot);
	aggregate = perfect_center; // because I can
	count = 0;
	this->factor = factor;
}


average_head_positioning::~average_head_positioning()
{
}

void average_head_positioning::callback(head_data hd)
{
	pos_t n_p = hd.get_pos();
	rot_t n_r = hd.get_rot();
	
	if (!account(hd))
	{
		return;
	}

	if (!count)
	{
		aggregate = hd;
	}
	else
	{
		aggregate = aggregate + hd;
	}

	count++;
	this->publish(this->get_center());
}

head_data average_head_positioning::get_center()
{
	return aggregate / count;
}

bool average_head_positioning::account(head_data hd)
{
	if (!count) return true;
	head_data avg = get_center();

	pos_t m_p = avg.get_pos();
	rot_t m_r = avg.get_rot();

	pos_t a_p = hd.get_pos();
	rot_t a_r = hd.get_rot();

	bool account = true;

	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		//if (a_p.axis[i] > range_pos.axis[i] || a_p.axis[i] < -range_pos.axis[i])
		//{
		//	return false;
		//}
		
		if (a_r.axis[i] > range_rot.axis[i] || a_r.axis[i] < -range_rot.axis[i])
		{
			return false;
		}

		account = account &&
					account_val(a_p.axis[i], m_p.axis[i], range_pos.axis[i]) &&
					account_val(a_r.axis[i], m_r.axis[i], range_rot.axis[i]);
					
	}
	return account;
}

bool average_head_positioning::account_val(head_data_axis_t v_hd, head_data_axis_t v_c, head_data_axis_t range)
{
	float l_factor = count < (1.0 / factor) ? factor * (count + 1) : factor;
	head_data_axis_t threshold = range * l_factor;

	head_data_axis_t min_c = v_c - threshold;
	head_data_axis_t max_c = v_c + threshold;

	head_data_axis_t min_hd = v_hd - threshold;
	head_data_axis_t max_hd = v_hd + threshold;

	return (min_c <= v_hd && v_hd <= max_c) || (min_hd <= v_c && v_c <= max_hd);
}
