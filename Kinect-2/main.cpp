#include <chrono>
#include <thread>

#include "head_tracker.h"
#include "yal.h"
#include "logger_subscriber.h"
#include "head_data_smoothener.h"
#include "head_data_filter.h"
#include "average_head_positioning.h"

int main() {
	__yal_init_logger();
	__yal_set_lvl_info();

	head_tracker *ht = new head_tracker();
	ht->setup();
	
	head_data_filter *hdf = new head_data_filter();
	head_data_smoothener *hds = new head_data_smoothener(0.2);
	average_head_positioning *ahp = new average_head_positioning(1.0);
	logger_subscriber *ls1 = new logger_subscriber();
	logger_subscriber *ls2 = new logger_subscriber();

	ht->add_subscriber(hdf);
	hdf->add_subscriber(hds);
	hds->add_subscriber(ahp);
	//hds->add_subscriber(ls1);
	ahp->add_subscriber(ls2);


	while (ht)
	{
		ht->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	int a;
	std::cin >> a;


	return 0;
}