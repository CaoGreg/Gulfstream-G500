#include "Log.h"
using namespace std;

Log* Log::log = nullptr;

void Log::update(){
	cout<<"log thread"<<endl;
}
