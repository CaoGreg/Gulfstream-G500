#include "Airspace.h"
#include "Timer.h"
#include "TestCase.h"

Airspace* Airspace::airspace = nullptr;
constexpr int TestCase::airplane_schedule[];

Airspace::Airspace(){
	this->minX = 0;
	this->maxX = 100;
	this->minY = 0;
	this->maxY = 100;
	this->minZ = 15000;
	this->maxZ = 40000;
}

bool Airspace::isInAirspace(Aircraft* a){
	bool result = false;
	if(a->getPositionX() >= minX && a->getPositionX() <= maxX && a->getPositionY() >= minY
			&& a->getPositionY() <= maxY && a->getPositionZ() >= minZ && a->getPositionZ() <= maxZ){
		result = true;
	}
	return result;
}

std::vector<Aircraft*> Airspace::getAircrafts(){
	//todo fix this thing
	return current_aircrafts;
}
void Airspace::updateTime(){
	//update time in airspace

}
void Airspace::updatePositions(double time, double timeVariation){
	for(Aircraft* aircraft : current_aircrafts){
		if(aircraft->isHolding()){
			//todo update values for holding aircraft
		}
		else{
			aircraft->updatePosition(time, timeVariation);
		}
	}
}

void Airspace::setEnteringAircrafts(){
	int time = Timer::getTimer()->getCurrentTime();
	for(int i = 0; i < incoming_aircrafts.size(); i++){
		if(incoming_aircrafts[i]->getEntryTime() == time){
			current_aircrafts.push_back(incoming_aircrafts[i]);
			//pop front
		}
	}

}

void Airspace::setIncomingAircrafts(){
	incoming_aircrafts.clear();
	for(unsigned int i = 0; i < sizeof(TestCase::airplane_schedule)/4; i += 8){
		incoming_aircrafts.push_back(new Aircraft(TestCase::airplane_schedule[i], TestCase::airplane_schedule[i+1], TestCase::airplane_schedule[i+2], TestCase::airplane_schedule[i+3], TestCase::airplane_schedule[i+4],
				TestCase::airplane_schedule[i+5], TestCase::airplane_schedule[i+6], TestCase::airplane_schedule[i+7]));
	}
}

void Airspace::update(){
	cout << "Airspace" << endl;
	if(firstset){
		setIncomingAircrafts();
		firstset = false;
	}
	setEnteringAircrafts();
}
