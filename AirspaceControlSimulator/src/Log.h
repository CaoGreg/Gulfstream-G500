#ifndef LOG_H_
#define LOG_H_

#include <cstddef>

class Log{
	public:
		Log(){}
		
		virtual ~Log() { delete log; } 
		
		static void createInstance(){ log = new Log(); }
		static Log* getLog(){ return log;	}

	private:
		static Log* log;
};

#endif /*LOG_H_*/
