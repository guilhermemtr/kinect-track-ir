#include "subscriber.h"
#include "publisher.h"

#include "head_data.h"



class dcs_client: public subscriber<head_data>, public publisher<head_data>
{
public:
	dcs_client();
	~dcs_client();
};

