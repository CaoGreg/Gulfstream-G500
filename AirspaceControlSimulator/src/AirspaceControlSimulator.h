/*
 * AirspaceControlSimulator.h
 *
 *  Created on: 18 nov. 2019
 *      Author: Alexis
 */

#ifndef AIRSPACECONTROLSIMULATOR_H_
#define AIRSPACECONTROLSIMULATOR_H_

#include "Airspace.h"
#include "Radar.h"
#include "Timer.h"
#include "Operator.h"
#include "Log.h"
#include "TrackFile.h"
#include "Task.h"
#include "DisplayManager.h"

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <time.h>
#include <sys/siginfo.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sys/poll.h>
#include <mutex>

//Timer includes
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

class AirspaceControlSimulator {
public:
	AirspaceControlSimulator(){}
	virtual ~AirspaceControlSimulator(){ delete airspacecontrolsimulator; }
	static void createInstance(){ airspacecontrolsimulator = new AirspaceControlSimulator(); }
	static AirspaceControlSimulator* getAirspaceControlSimulator(){ return airspacecontrolsimulator; }
	static void threadMutexLock(){ threadMutex.lock(); }
	static void threadMutexUnlock(){ threadMutex.unlock(); }
private:
	static AirspaceControlSimulator* airspacecontrolsimulator;
	static mutex threadMutex;
};


#endif /* AIRSPACECONTROLSIMULATOR_H_ */
