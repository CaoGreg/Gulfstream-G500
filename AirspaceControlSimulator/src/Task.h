#ifndef TASK_H_
#define TASK_H_

#include <cstdint>

//A task is composed of a priority, its period and the function to be executed in a thread
struct Task {
	uint64_t priority;
	uint64_t period;
	void (*func)();	
};

#endif /*TASK_H_*/
