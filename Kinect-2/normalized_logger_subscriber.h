#include "subscriber.h"
#include "normalized_head_data.h"

#ifndef __NORMALIZED_LOGGER_SUBSCRIBER__
#define __NORMALIZED_LOGGER_SUBSCRIBER__

class normalized_logger_subscriber: public subscriber<normalized_head_data>
{
public:
	normalized_logger_subscriber();
	~normalized_logger_subscriber();

	void callback(head_data hd);
};

#endif