#include "Airspace.h"

Airspace::Airspace(){
	this->minX = 0;
	this->maxX = 100;
	this->minY = 0;
	this->maxY = 100;
	this->minZ = 15000;
	this->maxZ = 40000;
}

bool Airspace::isInAirspace(Aircraft a){
	bool result = false;
	if(a.getPositionX() >= minX && a.getPositionX() <= maxX && a.getPositionY() >= minY
			&& a.getPositionY() <= maxY && a.getPositionZ() >= minZ && a.getPositionZ() <= maxZ){
		result = true;
	}
	return result;
}

std::vector<Aircraft> Airspace::getAircrafts(){
	//todo fix this thing
	return aircrafts;
}

