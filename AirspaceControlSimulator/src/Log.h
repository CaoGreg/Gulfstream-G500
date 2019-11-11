#ifndef LOG_H_
#define LOG_H_

#include <cstddef>
#include <iostream>
using namespace std;

class Log{
	public:
		Log(){}
		
		virtual ~Log() { delete log; } 
		
		static void createInstance(){ log = new Log(); }
		static Log* getLog(){ return log;	}
		void update(){cout<<"log thread"<<endl;}

	private:
		static Log* log;
};

#endif /*LOG_H_*/
