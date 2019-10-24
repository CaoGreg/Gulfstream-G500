#include "Timer.h"

Timer* Timer::timer = nullptr;

int Timer::getCurrentTime(){
	return currentTime;
}

void Timer::updateTimer(double time){
	if(!this->paused){
		currentTime += time;
	}
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

