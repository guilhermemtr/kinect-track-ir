#include "publisher.h"
#include "subscriber.h"

#include "head_data.h"


class head_data_smoothener: public subscriber<head_data>, public publisher<head_data>
{
public:
	head_data_smoothener(float update_ratio);
	~head_data_smoothener();
	void callback(head_data hd);
	void update(head_data hd);

private:
	float update_ratio;
	head_data last;
	head_data current_value;
	bool active;
};

