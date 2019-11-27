/*
 * Timer.h
 *
 *  Created on: Oct 20, 2019
 *      Author: Greg
 */

#pragma once


#include <cstddef>
#include <iostream>
//Timer includes
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <mutex>

using namespace std;

class Timer{
	public:
		Timer(){
			this->paused = false;
			this->currentTime = 0;
			this->current.tv_sec = 0;
			this->current.tv_nsec = 0;
			if( clock_settime( CLOCK_REALTIME, &current) == -1 ) {
					perror( "setclock" );
				}
		}

		virtual ~Timer(){ delete timer; }

		static void createInstance(){ timer = new Timer(); }
		static Timer* getTimer(){ return timer;	}
		double getCurrentTime();
		static void threadUnlock(){ timerMutex.unlock(); }
		static void threadLock(){ timerMutex.lock(); }
		void updateTimer();
		void pause();
		void unpause();
		bool isPaused();
	private:
		static Timer* timer;
		bool paused;
		double currentTime;
		struct timespec current;
		static mutex timerMutex;

};


