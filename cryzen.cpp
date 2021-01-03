#include <stdint.h>
#include <thread>
#include <chrono>
#include <vector>

#define ARRAY_SIZE 65536*2
#define NUM_WORKERS 1

using namespace std::chrono;

uint64_t* integers;
double* doubles;
bool run;

void worker();

int main()
{
	integers = new uint64_t[ARRAY_SIZE];
	doubles = new double[ARRAY_SIZE];

	std::vector<std::thread> workers;
	run = false;
	for (int i = 0; i < NUM_WORKERS; i++)
	{
		workers.push_back(std::thread(worker));
	}

	milliseconds on_time(200);
	milliseconds off_time(1000);
	
	while (true)
	{
		run = true;
		std::this_thread::sleep_for(on_time);
		run = false;
		std::this_thread::sleep_for(off_time);
	}

	return 0;
}

void worker()
{
	while (true)
	{
		while (run)
		{
			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				integers[i] += integers[i];
				doubles[i] += doubles[i];
			}
		}
		while (!run) std::this_thread::sleep_for(milliseconds(1));
	}
}