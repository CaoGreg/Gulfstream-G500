#include "Timer.h"

Timer* Timer::timer = nullptr;

double Timer::getCurrentTime(){
	return currentTime;
}

void Timer::updateTimer(double time){
	if(!this->paused){
		currentTime += time;
	}
	cout<<"timer thread"<<endl;
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

