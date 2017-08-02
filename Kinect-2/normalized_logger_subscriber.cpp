#include "normalized_logger_subscriber.h"



normalized_logger_subscriber::normalized_logger_subscriber()
{
}


normalized_logger_subscriber::~normalized_logger_subscriber()
{
}

void normalized_logger_subscriber::callback(head_data hd)
{
	hd.log_head_data("");
}
