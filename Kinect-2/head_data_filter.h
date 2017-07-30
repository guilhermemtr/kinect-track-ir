#include "head_data.h"
#include "subscriber.h"
#include "publisher.h"


class head_data_filter: public subscriber<head_data>, public publisher<head_data>
{
public:
	head_data_filter();
	~head_data_filter();
	void callback(head_data hd);
};

