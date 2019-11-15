#include "TrackFile.h"

TrackFile* TrackFile::trackfile = nullptr;

TrackFile::TrackFile(){
	ofstream otrackFile ("trackFile.txt", ios::out);
	otrackFile.close();
}

void TrackFile::update(){
	cout << "Updating trackFile " << endl;
	string line;
	ofstream otrackFile ("trackFile.txt", ios::out);
	otrackFile << "Current time: " << Timer::getTimer()->getCurrentTime() << endl;
	otrackFile << "Incoming aircrafts" << endl;
	for(unsigned int i = 0; i < Airspace::getAirspace()->getIncomingAircrafts().size(); i++){
		otrackFile << Airspace::getAirspace()->getIncomingAircrafts()[i]->print(1);
	}
	otrackFile << "Inside Airspace: " << endl;
	for(unsigned int i = 0; i < Airspace::getAirspace()->getEnteringAircrafts().size(); i++){
		otrackFile << Airspace::getAirspace()->getEnteringAircrafts()[i]->print(2);
	}
	otrackFile << "Left aircrafts: " << endl;
	for(unsigned int i = 0; i < Airspace::getAirspace()->getLeftAircrafts().size(); i++){
		otrackFile << Airspace::getAirspace()->getLeftAircrafts()[i]->print(3);
	}

	otrackFile.close();
	ifstream itrackFile ("trackFile.txt", ios::in);
	while(itrackFile){
		getline(itrackFile, line);
		cout << line << endl;
	}
	itrackFile.close();
}
