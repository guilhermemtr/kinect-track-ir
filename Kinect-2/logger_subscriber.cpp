#include "logger_subscriber.h"



logger_subscriber::logger_subscriber(char *prefix)
{
	this->prefix = prefix;
}


logger_subscriber::~logger_subscriber()
{
}

void logger_subscriber::callback(head_data hd)
{
	hd.log_head_data("");
}
