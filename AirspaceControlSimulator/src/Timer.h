/*
 * Timer.h
 *
 *  Created on: Oct 20, 2019
 *      Author: Greg
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer{
	public:
		Timer(){
			this->paused = false;
			currentTime = 0;
		}

		~Timer(){ delete timer; }

		static void createInstance(){ timer = new Timer(); }
		static Timer* getTimer(){ return timer;	}
		int getCurrentTime();
		void updateTimer(double time);
		void pause();
		void unpause();
		bool isPaused();
	private:
		static Timer* timer;
		bool paused;
		int currentTime;
};



#endif /* TIMER_H_ */
