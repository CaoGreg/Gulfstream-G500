#include "Airspace.h"
#include "Timer.h"
#include "TestCase.h"

Airspace* Airspace::airspace = nullptr;
constexpr int TestCase::airplane_schedule[];

Airspace::Airspace(){
	this->minX = 0;
	this->maxX = 528000; //100 miles in feet
	this->minY = 0;
	this->maxY = 528000; //100 miles in feet
	this->minZ = 15000;
	this->maxZ = 40000;
	this->time = 0;//Timer::getTimer()->getCurrentTime();

}

bool Airspace::isInAirspace(Aircraft* a){
	bool result = false;
	if((a->getPositionX()-minX)>=0.00001 && (maxX-a->getPositionX())>=0.00001 && (a->getPositionY()-minY)>=0.00001
			&& (maxY-a->getPositionY())>=0.0001 && (a->getPositionZ()-minZ)>=0.00001 && (maxZ-a->getPositionZ())>=0.00001){
		result = true;
	}/*else{
		cout << to_string((a->getPositionX()-minX)>=0.00001) << " " << to_string((maxX-a->getPositionX())>=0.00001) << " " << to_string((a->getPositionY()-minY)>=0.00001)
				<< " " << to_string((maxY-a->getPositionY())>=0.0001) << " " << to_string((a->getPositionZ()-minZ)>=0.00001) << " " << to_string((maxZ-a->getPositionZ())>=0.00001)
				<< endl;
	}*/
	return result;
}

std::vector<Aircraft*> Airspace::getAircrafts(){
	//todo fix this thing
	return current_aircrafts;
}
void Airspace::updateTime(){
	//update time in airspace
	this->time = Timer::getTimer()->getCurrentTime();

}
void Airspace::updatePositions(){
	for(Aircraft* aircraft : current_aircrafts){
		if(aircraft->isHolding()){
			//todo update values for holding aircraft
		}
		else{
			aircraft->updatePosition((double)this->time);
		}
	}
}

void Airspace::setEnteringAircrafts(){
	for(unsigned int i = 0; i < incoming_aircrafts.size(); i++){
		if(incoming_aircrafts[i]->getEntryTime() == this->time){
			current_aircrafts.push_back(incoming_aircrafts[i]);
			//pop front
			incoming_aircrafts.pop_front();
		}
	}

}

void Airspace::setIncomingAircrafts(){
	incoming_aircrafts.clear();
	for(unsigned int i = 0; i < sizeof(TestCase::airplane_schedule)/4; i += 8){
		incoming_aircrafts.push_back(new Aircraft(TestCase::airplane_schedule[i], TestCase::airplane_schedule[i+1], TestCase::airplane_schedule[i+2], TestCase::airplane_schedule[i+3], TestCase::airplane_schedule[i+4],
				TestCase::airplane_schedule[i+5], TestCase::airplane_schedule[i+6] + this->minZ, TestCase::airplane_schedule[i+7]));
	}
}

void Airspace::removeFromAirspace(){
	if(!current_aircrafts.empty()){
		std::vector<unsigned int> leavingIndex;
		for(unsigned int i = 0; i < current_aircrafts.size(); i++){
			if(!isInAirspace(current_aircrafts[i])){
				current_aircrafts[i]->setLeftTime(this->time);
				left_aircrafts.push_back(current_aircrafts[i]);
				leavingIndex.push_back(i);
			}
		}
		if(!leavingIndex.empty()){
			for(int i = leavingIndex.size()-1; i >= 0; i--){
				current_aircrafts.erase(current_aircrafts.begin()+leavingIndex[i]);
			}
			leavingIndex.clear();
		}
	}
}

void Airspace::update(){
	cout << "Airspace" << endl;
	updateTime();
	if(firstset){
		setIncomingAircrafts();
		firstset = false;
	}
	setEnteringAircrafts();
	updatePositions();
	removeFromAirspace();
}
