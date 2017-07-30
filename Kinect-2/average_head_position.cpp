#include "average_head_position.h"



average_head_position::average_head_position(float factor)
{
	pos_t center = { __AVG_HEAD_POS_WIDTH__, __AVG_HEAD_POS_HEIGHT__, __AVG_HEAD_POS_DEPTH__ };
	rot_t no_rot = { 0, 0, 0 };
	perfect_center.update_data(0, center, no_rot);
	aggregate = perfect_center;
	count = 1;
	this->factor = factor;
}


average_head_position::~average_head_position()
{
}

void average_head_position::callback(head_data hd)
{
	if (!account(hd))
	{
		return;
	}

	pos_t c_p = aggregate.get_pos();
	rot_t c_r = aggregate.get_rot();

	pos_t n_p = hd.get_pos();
	rot_t n_r = hd.get_rot();

	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		c_p.axis[i] += n_p.axis[i];
		c_r.axis[i] += n_r.axis[i];
	}

	count++;

	this->publish(this->get_center());
}

head_data average_head_position::get_center()
{
	pos_t c_p = aggregate.get_pos();
	rot_t c_r = aggregate.get_rot();

	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		c_p.axis[i] = c_p.axis[i]/count;
		c_r.axis[i] = c_r.axis[i]/count;
	}

	head_data tmp;
	tmp.update_data(0, c_p, c_r);
	return tmp;
}

bool average_head_position::account(head_data hd)
{
	head_data avg = get_center();

	pos_t m_p = avg.get_pos();
	rot_t m_r = avg.get_rot();

	pos_t a_p = hd.get_pos();
	rot_t a_r = hd.get_rot();

	bool account = true;

	for (int i = 0; i < HEAD_DATA_AXIS && account; i++)
	{
		if (!account_val(a_p.axis[i], m_p.axis[i])) {
			account = false;
		}
		if (!account_val(a_r.axis[i], m_r.axis[i])) {
			account = false;
		}
	}
	return true;
}

bool average_head_position::account_val(head_data_axis_t v_hd, head_data_axis_t v_c)
{
	head_data_axis_t min = v_c * (1.0 - factor);
	head_data_axis_t max = v_c * (1.0 + factor);

	return min <= v_hd && v_hd <= max;
}
