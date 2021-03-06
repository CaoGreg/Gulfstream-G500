#include "Airspace.h"
#include "Radar.h"
#include "Timer.h"
#include "Operator.h"
#include "Log.h"
#include "TrackFile.h"
#include "Task.h"

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <time.h>
#include <sys/siginfo.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sys/poll.h>


using namespace std;

void init();
pthread_t setupThread();
pthread_t startTask(Task& task);
void* startRoutine(void* arg);

int main(int argc, char *argv[]) {

	init();

	cout<<"Starting simulation" << std::endl;

	//Set up the parameters of the threads and use a FIFO scheduling
	sched_param params;
	int policy;
	pthread_getschedparam(pthread_self(), &policy, &params);
	params.sched_priority = 255;
	policy = SCHED_FIFO;
	pthread_setschedparam(pthread_self(), policy, &params);


	//Task to update the airspace
	Task airspaceTask;
	airspaceTask.priority = 254;
	airspaceTask.period = 500000000; //0.5sec
	airspaceTask.func = []() {
		Airspace::getAirspace()->update();
	};
	//Airspace::getAirspace()->update();

	//Task to update the radar
	Task radarTask;
	radarTask.priority = 253;
	radarTask.period = 500000000; //0.5sec
	radarTask.func = []() {
		Radar::getRadar()->update();
	};

	//Task to update the timer
	Task timerTask;
	timerTask.priority = 252;
	timerTask.period = 500000000; //0.5sec
	timerTask.func = []() {
		Timer::getTimer()->updateTimer(1);
	};

	//Task to update the operator
	Task operatorTask;
	operatorTask.priority = 251;
	operatorTask.period = 500000000; //0.5sec
	operatorTask.func = []() {
		Operator::getOperator()->update();
	};
	//Task to update the log
	Task logTask;
	logTask.priority = 250;
	logTask.period = 500000000; //0.5sec
	logTask.func = []() {
		Log::getLog()->update();
	};
	//Task to update the track file
	Task trackFileTask;
	trackFileTask.priority = 249;
	trackFileTask.period = 500000000; //0.5sec
	trackFileTask.func = []() {
		TrackFile::getTrackFile()->update();
	};


	while(Timer::getTimer()->getCurrentTime() < 17){
		pthread_t airspaceThread = startTask(airspaceTask);
		//pthread_t radarThread = startTask(radarTask);
		/*pthread_t operatorThread = startTask(operatorTask);
	pthread_t logThread = startTask(logTask);*/
		pthread_t trackFileThread = startTask(trackFileTask);
		pthread_t timerThread = startTask(timerTask);

		pthread_join(airspaceThread, nullptr);
		//pthread_join(radarThread, nullptr);
		pthread_join(timerThread, nullptr);
		/*pthread_join(operatorThread, nullptr);
	pthread_join(logThread, nullptr);*/
		pthread_join(trackFileThread, nullptr);
	}
	return EXIT_SUCCESS;
}

//initialize the objects
void init(){
	cout<<"Initializing simulation objects" << std::endl;
	Airspace::createInstance();
	Radar::createInstance();
	Timer::createInstance();
	Operator::createInstance();
	Log::createInstance();
	TrackFile::createInstance();
}

pthread_t startTask(Task& task) {
	sched_param schedParams;
	schedParams.sched_priority = task.priority;

	pthread_attr_t attributes;
	pthread_attr_init(&attributes);
	pthread_attr_setschedparam(&attributes, &schedParams);

	pthread_t thread;
	pthread_create(&thread, &attributes, startRoutine, &task);

	pthread_attr_destroy(&attributes);

	return thread;
}

void* startRoutine(void* arg) {
	const Task* task = reinterpret_cast<const Task*>(arg);

	/*uint64_t phase = 0;
	uint64_t startTime = 0;
	uint64_t endTime = 0;
	ClockTime(CLOCK_MONOTONIC, NULL, &phase);
	int deadline =  phase;
	//while(true) {
		deadline += task->period;
		ClockTime(CLOCK_MONOTONIC, NULL, &startTime);
		task->func();
		ClockTime(CLOCK_MONOTONIC, NULL, &endTime);
		int slack = deadline - endTime;
		timespec timeSpecification;
		timeSpecification.tv_sec = slack * 1000000000;
		timeSpecification.tv_nsec = slack % 1000000000;
		nanosleep(&timeSpecification, NULL);	
	//}*/
	task->func();
	return nullptr;
}

//pthread_t setupThread(int priority, int period){
//	//sched_param schedParams;
//	//schedParams.sched_priority = task.priority;
//}

