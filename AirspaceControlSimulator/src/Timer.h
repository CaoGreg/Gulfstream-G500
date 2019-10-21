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
		Timer();
		int getCurrentTime();
		void updateTimer(double time);
		void pause();
		void unpause();
		bool isPaused();

	private:
		bool paused;
		int currentTime;
};



#endif /* TIMER_H_ */
