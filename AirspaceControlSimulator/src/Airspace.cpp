#include "Airspace.h"

Airspace::Airspace(){
	this->minX = 0;
	this->maxX = 100;
	this->minY = 0;
	this->maxY = 100;
	this->minZ = 15000;
	this->maxZ = 40000;
}

bool Airspace::isInAirspace(double x, double y, double z){
	bool result = false;
	if(x >= minX && x <= maxX && y >= minY && y <= maxY && z >= minZ && z <= maxZ){
		result = true;
	}
	return result;
}
