#include "Timer.h"

Timer* Timer::timer = nullptr;

double Timer::getCurrentTime(){
	updateTimer();
	return currentTime;
}

void Timer::updateTimer(){

	if( clock_gettime( CLOCK_REALTIME, &current) == -1 ) {
		perror( "clock gettime" );
	}
	//string  timer =  "Current timer: " + to_string(current.tv_sec) + " "  + to_string((double)(current.tv_nsec)/(double)1000000000L) + "\n";
	currentTime = current.tv_sec;
}

void Timer::unpause(){
	this->paused = false;
}

void Timer::pause(){
	this->paused = true;
}

bool Timer::isPaused(){
	return this->paused;
}

