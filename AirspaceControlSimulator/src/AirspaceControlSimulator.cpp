#include "AirspaceControlSimulator.h"

AirspaceControlSimulator* AirspaceControlSimulator::airspacecontrolsimulator = nullptr;
mutex AirspaceControlSimulator::threadMutex;
void init();
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
	airspaceTask.period = 1000000000; //1sec
	airspaceTask.func = []() {
		Airspace::getAirspace()->update();
	};

	//Task to update the operator
	Task operatorTask;
	operatorTask.priority = 253;
	operatorTask.period = 2000000000; //2sec
	operatorTask.func = []() {
		Operator::getOperator()->update();
	};

	//Task to update the track file
	Task trackFileTask;
	trackFileTask.priority = 252;
	trackFileTask.period = 3000000000; //3sec
	trackFileTask.func = []() {
		TrackFile::getTrackFile()->update();
	};

	//Task for the display
	Task displayTask;
	displayTask.priority = 251;
	displayTask.period = 5000000000; //5sec
	displayTask.func = []() {
		DisplayManager::getDisplayManager()->update();
	};

	//Task to update the radar
	Task radarTask;
	radarTask.priority = 250;
	radarTask.period = 15000000000; //15sec
	radarTask.func = []() {
		Radar::getRadar()->update();
	};

	//Task to update the log
	Task logTask;
	logTask.priority = 249;
	logTask.period = 60000000000; //60sec
	logTask.func = []() {
		Log::getLog()->update();
	};

	Airspace* airspace = Airspace::getAirspace();

	pthread_t airspaceThread = startTask(airspaceTask);
	pthread_t operatorThread = startTask(operatorTask);
	pthread_t trackThread = startTask(trackFileTask);
	pthread_t displayThread = startTask(displayTask);
	pthread_t radarThread = startTask(radarTask);
	pthread_t logThread = startTask(logTask);

	//Join threads
	pthread_join(airspaceThread, nullptr);
	pthread_join(operatorThread, nullptr);
	pthread_join(trackThread, nullptr);
	pthread_join(displayThread, nullptr);
	pthread_join(radarThread, nullptr);
	pthread_join(logThread, nullptr);


	return EXIT_SUCCESS;
}

//initialize the objects
void init(){
	cout<<"Initializing simulation objects" << std::endl;
	AirspaceControlSimulator::createInstance();
	Airspace::createInstance();
	Radar::createInstance();
	Timer::createInstance();
	Operator::createInstance();
	Log::createInstance();
	TrackFile::createInstance();
	DisplayManager::createInstance();
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

	uint64_t phase = 0;
	uint64_t startTime = 0;
	uint64_t endTime = 0;
	ClockTime(CLOCK_MONOTONIC, NULL, &phase);
	uint64_t deadline =  phase;
	while(true) {
		deadline += task->period;
		ClockTime(CLOCK_MONOTONIC, NULL, &startTime);
		task->func();
		ClockTime(CLOCK_MONOTONIC, NULL, &endTime);
		uint64_t slack = deadline - endTime;
		struct timespec timeSpecification;
		timeSpecification.tv_sec = slack / 1000000000;
		timeSpecification.tv_nsec = slack % 1000000000;
		nanosleep(&timeSpecification, NULL);
	}
	//task->func();
	return nullptr;
}
