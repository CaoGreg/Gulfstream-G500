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
	cout << "DisplayManager task\n";
	cout << "Inside Airspace: " << endl;
	for(unsigned int i = 0; i < Airspace::getAirspace()->getCurrentAircrafts().size(); i++){
		cout << Airspace::getAirspace()->getCurrentAircrafts()[i]->print(2);
	}
	cout << endl;
	cout << "Potential constrain violations: " << endl;
	if(displayedViolations == ""){
		displayedViolations = "None";
	}
	cout << displayedViolations;
	cout << endl << endl;
	displayedViolations = "";
}
