/*
 * DisplayManager.cpp
 *
 *  Created on: Nov 15, 2019
 *      Author: Greg
 */

#include "DisplayManager.h"

DisplayManager* DisplayManager::displaymanager = nullptr;

DisplayManager::DisplayManager(){

}

void DisplayManager::addToViolations(string s){
	displayedViolations = displayedViolations + s;
}

void DisplayManager::update(){
	AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexLock();
		//cout << "DisplayManager task\n";
		//cout << "The timer when entered display: ";
		//cout << currentTime << endl;
		cout << "Forecast airspace giving the track file of the last radar hit" << endl;
		cout << "Inside Airspace: " << endl;
		for(unsigned int i = 0; i < TrackFile::getTrackFile()->getHits().size(); i++){
			cout << TrackFile::getTrackFile()->getHits()[i]->print(2);
		}
		cout << endl;
		cout << "Potential constraint violations: " << endl;
		if(displayedViolations == ""){
			displayedViolations = "None";
		}
		cout << displayedViolations;
		cout << endl << endl;
		displayedViolations = "";
	AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexUnlock();
}
