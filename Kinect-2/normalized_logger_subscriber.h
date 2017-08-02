#include "subscriber.h"
#include "normalized_head_data.h"

#ifndef __NORMALIZED_LOGGER_SUBSCRIBER__
#define __NORMALIZED_LOGGER_SUBSCRIBER__

class normalized_logger_subscriber: public subscriber<normalized_head_data>
{
public:
	normalized_logger_subscriber(char *prefix);
	~normalized_logger_subscriber();

	void callback(normalized_head_data hd);

private:
	char *prefix;
};

#endif