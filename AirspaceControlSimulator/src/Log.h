#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <iostream>
#include <fstream>
#include "Timer.h"
#include "Airspace.h"
using namespace std;

class Log{
	public:
		Log();
		virtual ~Log() { delete log; }
		static void createInstance(){ log = new Log(); }
		static Log* getLog(){ return log; }
		void writeLog();
		void update();

	private:
		static Log* log;
};

#endif /*LOG_H_*/
