#include <chrono>
#include <thread>

#include "logger_subscriber.h"
#include "normalized_logger_subscriber.h"

#include "head_tracker.h"

#include "head_data_smoothener.h"
#include "head_data_filter.h"
#include "average_head_positioning.h"

#include "head_data_multiplier.h"
#include "head_data_normalizer.h"


#include "yal.h"

int main() {
	__yal_init_logger();
	__yal_set_lvl_info();

	head_tracker *ht = new head_tracker();
	ht->setup();
	
	head_data_filter *hdf = new head_data_filter();
	ht->add_subscriber(hdf);

	head_data_smoothener *hds = new head_data_smoothener(0.2);
	hdf->add_subscriber(hds);

	average_head_positioning *ahp = new average_head_positioning(0.10);
	hds->add_subscriber(ahp);

	head_data_normalizer *hdn = new head_data_normalizer(ahp);
	hds->add_subscriber(hdn);

	head_data_multiplier *hdm = new head_data_multiplier(0.75, 0.75, 0.75, 0.75, 0.75, 0.75);
	hdn->add_subscriber(hdm);

	normalized_logger_subscriber *nls = new normalized_logger_subscriber("");
	logger_subscriber *ls = new logger_subscriber("");

	hdm->add_subscriber(nls);
	//ahp->add_subscriber(ls);






	// logger_subscriber *ls1 = new logger_subscriber();
	// logger_subscriber *ls2 = new logger_subscriber();


	//hds->add_subscriber(ls1);
	// ahp->add_subscriber(ls2);


	while (ht)
	{
		ht->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	int a;
	std::cin >> a;


	return 0;
}