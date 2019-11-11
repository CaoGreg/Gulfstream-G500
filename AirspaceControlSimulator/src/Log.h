#ifndef LOG_H_
#define LOG_H_

#include <cstddef>
#include <iostream>

class Log{
	public:
		Log(){}
		
		virtual ~Log() { delete log; } 
		
		static void createInstance(){ log = new Log(); }
		static Log* getLog(){ return log;	}
		void update();

	private:
		static Log* log;
};

#endif /*LOG_H_*/
