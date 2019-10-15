#include "ATC.h"

ATC::ATC(){
	this->airspace = new Airspace();
}

void ATC::addAircraft(Aircraft* aircraft){
	this->aircraftList.push_back(aircraft);
}