/*
 * Timer.h
 *
 *  Created on: Oct 20, 2019
 *      Author: Greg
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <cstddef>

class Timer{
	public:
		Timer(){
			this->paused = false;
			this->currentTime = 0;
		}

		virtual ~Timer(){ delete timer; }

		static void createInstance(){ timer = new Timer(); }
		static Timer* getTimer(){ return timer;	}
		double getCurrentTime();
		void updateTimer(double time);
		void pause();
		void unpause();
		bool isPaused();
	private:
		static Timer* timer;
		bool paused;
		double currentTime;
};



#endif /* TIMER_H_ */
