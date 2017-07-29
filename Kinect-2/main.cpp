#include <chrono>
#include <thread>

#include "head_tracker.h"
#include "yal.h"


int __yal_dbg_lvl = __YAL_INFO;
FILE * __yal_output = stdout;

int main() {
	__yal_init_logger();
	__yal_set_lvl_info();

	head_tracker *ht = new head_tracker();
	ht->setup();
	while (ht)
	{
		ht->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	int a;
	std::cin >> a;

	return 0;
}