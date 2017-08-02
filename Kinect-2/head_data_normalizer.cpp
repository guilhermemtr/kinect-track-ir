#include "head_data_normalizer.h"



head_data_normalizer::head_data_normalizer(average_head_positioning* ahp)
{
	this->ahp = ahp;
}


head_data_normalizer::~head_data_normalizer()
{
	this->ahp = nullptr;
}

void head_data_normalizer::callback(head_data hd)
{
	head_data centered = hd - (ahp->get_center());

	pos_t pos_norm_data = {
		(max_head_data_pos[x][1] - max_head_data_pos[x][0]),
		(max_head_data_pos[y][1] - max_head_data_pos[y][0]),
		(max_head_data_pos[z][1] - max_head_data_pos[z][0])
	};

	rot_t rot_norm_data = {
		(max_head_data_rot[yaw][1] - max_head_data_rot[yaw][0]),
		(max_head_data_rot[pitch][1] - max_head_data_rot[pitch][0]),
		(max_head_data_rot[roll][1] - max_head_data_rot[roll][0])
	};
	
	head_data norm;
	norm.update_data(0, pos_norm_data, rot_norm_data);

	pos_t h_pos = centered.get_pos();
	rot_t h_rot = centered.get_rot();

	pos_t n_pos = norm.get_pos();
	rot_t n_rot = norm.get_rot();

	normalized_pos_t normalized_pos;
	normalized_rot_t normalized_rot;

	// This cuts off some theoretically possible results, but I believe a person would die before being capable of turning the head 180 degrees.
	for (int i = 0; i < HEAD_DATA_AXIS; i++)
	{
		normalized_rot.axis[i] = std::max(std::min(((double)h_rot.axis[i]) / ((double)n_rot.axis[i]), 1.0), -1.0);
		normalized_pos.axis[i] = std::max(std::min(((double)h_pos.axis[i]) / ((double)n_pos.axis[i]), 1.0), -1.0);
	}
	uint64_t id = hd.get_id();

	normalized_head_data nhd;
	nhd.update_data(id, normalized_pos, normalized_rot);
	this->publish(nhd);
}
