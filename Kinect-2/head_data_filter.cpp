#include "head_data_filter.h"



head_data_filter::head_data_filter()
{
}


head_data_filter::~head_data_filter()
{
}

void head_data_filter::callback(head_data hd)
{
	if (hd.get_pos().axis[z])
	{
		this->publish(hd);
	}
}