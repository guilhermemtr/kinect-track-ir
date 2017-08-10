#include "normalized_head_data.h"
#include "publisher.h"
#include "subscriber.h"


class head_data_multiplier: public subscriber<normalized_head_data>, public publisher<normalized_head_data>
{
public:
	head_data_multiplier(double x_factor, double y_factor, double z_factor, double yaw_factor, double pitch_factor, double roll_factor);
	head_data_multiplier();
	~head_data_multiplier();

	void callback(normalized_head_data hd);

private:
	void update_maximum(normalized_head_data hd);

	normalized_head_data maximum_value;
	normalized_head_data multiplier;
	normalized_head_data multiplying_factor;
};

