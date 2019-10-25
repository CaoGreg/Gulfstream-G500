/*
 * Operator.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: Greg
 */
#include "Operator.h"

void Operator::setAltitude(int aircraftId, double altitude){
	std::vector<Aircraft> aircraftList = Airspace::getAirspace()->getAircrafts();
	for(Aircraft& aircraft : aircraftList){
		if(aircraft.getId() == aircraftId){
			aircraft.setPositionY(altitude*1000);
			//todo refresh computer data on airspace as well
		}
	}
}

void Operator::setSpeed(int aircraftId,double speed){
	std::vector<Aircraft> aircraftList = Airspace::getAirspace()->getAircrafts();
	for(Aircraft& aircraft : aircraftList){
		if(aircraft.getId() == aircraftId){
			//set to new speed
			//todo refresh computer data on airspace as well
		}
	}
}

void Operator::setDirection(int aircraftId,int x, int y, int z){
	std::vector<Aircraft> aircraftList = Airspace::getAirspace()->getAircrafts();
	for(Aircraft& aircraft : aircraftList){
		if(aircraft.getId() == aircraftId){
			aircraft.setPositionY(y);
			aircraft.setPositionX(x);
			aircraft.setPositionZ(x);
			//todo refresh computer data on airspace as well
		}
	}
}

void Operator::setHoldingPattern(int aircraftId, bool holdingPattern){
	std::vector<Aircraft> aircraftList = Airspace::getAirspace()->getAircrafts();
	for(Aircraft& aircraft : aircraftList){
		if(aircraft.getId() == aircraftId){
			//todo make aircraft hold function
			//todo refresh computer data on airspace as well
		}
	}
}

Aircraft Operator::getAircraftData(int aircraftId){

}

void Operator::setHoldingPatternAll(bool holdingPatter){
	std::vector<Aircraft> aircraftList = Airspace::getAirspace()->getAircrafts();
	for(Aircraft& aircraft : aircraftList){
		//todo make aircraft hold function
		//todo refresh computer data on airspace as well
	}
}

void Operator::addAircraft(int id, int x, int y, int z, int velX,int velY, int velZ){

}

void Operator::deleteAircraft(int id){

}

void Operator::send(int id,string message){

}

void Operator::broadcast(string message){

}

void Operator::predictPath(int id){

}

bool Operator::checkViolations(){
	return true;
}

bool hasCollisions(int id1, int id2){
	return true;
}

