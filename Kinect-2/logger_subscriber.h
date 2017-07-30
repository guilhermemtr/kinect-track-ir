#include "subscriber.h"

#include "head_data.h"


class logger_subscriber :
	public subscriber<head_data>
{
public:
	logger_subscriber();
	~logger_subscriber();
	void callback(head_data hd);
};

