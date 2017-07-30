#include <chrono>
#include <thread>

#include "head_tracker.h"
#include "yal.h"
#include "logger_subscriber.h"
#include "head_data_smoothener.h"
#include "head_data_filter.h"

int main() {
	__yal_init_logger();
	__yal_set_lvl_info();

	head_tracker *ht = new head_tracker();
	ht->setup();
	
	head_data_filter *hdf = new head_data_filter();
	head_data_smoothener *hds = new head_data_smoothener(0.2);
	logger_subscriber *ls = new logger_subscriber();
	ht->add_subscriber(hdf);
	hdf->add_subscriber(hds);
	hds->add_subscriber(ls);


	while (ht)
	{
		ht->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	int a;
	std::cin >> a;

	delete ls;

	return 0;
}