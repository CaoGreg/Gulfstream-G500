#include "Airspace.h"
#include "Timer.h"

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
	return current_aircrafts;
}
void Airspace::updateTime(){
	//uint64 prevTime = 0;
	//if()

}
void Airspace::updatePositions(double time, double timeVariation){
	for(Aircraft& aircraft : current_aircrafts){
		if(aircraft.isHolding()){
			//todo update values for holding aircraft
		}
		else{
			aircraft.updatePosition(time, timeVariation);
		}
	}
}

void Airspace::getEnteringAircrafts(){
	//todo check for aircrafts at the given time
	int time = Timer::getTimer()->getCurrentTime();
	//todo add aircrats
}
