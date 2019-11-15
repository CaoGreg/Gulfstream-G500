#include "Log.h"

Log* Log::log = nullptr;

Log::Log(){
	ofstream oLogFile ("Log.txt", ios::out);
	oLogFile.close();
}

void Log::writeLog(){
	string line;
	ofstream oLogFile ("Log.txt", ios::out|ios::app);
	oLogFile << "Current time: " << Timer::getTimer()->getCurrentTime() << endl;
	/*oLogFile << "Incoming aircrafts" << endl;
	for(unsigned int i = 0; i < Airspace::getAirspace()->getIncomingAircrafts().size(); i++){
		oLogFile << Airspace::getAirspace()->getIncomingAircrafts()[i]->print(1);
	}*/
	oLogFile << "Inside Airspace: " << endl;
	for(unsigned int i = 0; i < Airspace::getAirspace()->getCurrentAircrafts().size(); i++){
		oLogFile << Airspace::getAirspace()->getCurrentAircrafts()[i]->print(2);
	}
/*	oLogFile << "Left aircrafts: " << endl;
	for(unsigned int i = 0; i < Airspace::getAirspace()->getLeftAircrafts().size(); i++){
		oLogFile << Airspace::getAirspace()->getLeftAircrafts()[i]->print(3);
	}*/
	oLogFile << endl << endl;
	oLogFile.close();
}

void Log::update(){
	cout<<"Log Thread"<<endl;
	writeLog();
}
