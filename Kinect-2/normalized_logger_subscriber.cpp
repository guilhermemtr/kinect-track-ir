#include "normalized_logger_subscriber.h"



normalized_logger_subscriber::normalized_logger_subscriber(char *prefix)
{
	this->prefix = prefix;
}


normalized_logger_subscriber::~normalized_logger_subscriber()
{
}

void normalized_logger_subscriber::callback(normalized_head_data hd)
{
	hd.log_normalized_head_data("");
}
