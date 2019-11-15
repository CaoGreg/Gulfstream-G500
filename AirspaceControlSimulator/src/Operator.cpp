/*
 * Operator.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: Greg
 */
#include "Operator.h"

Operator* Operator::operater = nullptr;

Operator::Operator(){
	
}

void Operator::setHitList(vector<Aircraft*> aircraftHits){
	this->hitsList = aircraftHits;
}

void Operator::setAltitude(int aircraftId, double altitude){
	//update the altitude when the id matches
	Airspace* airspace = Airspace::getAirspace();
	for(Aircraft* aircraft : hitsList){
		if(aircraft->getId() == aircraftId && (altitude <= airspace->getMaxZ() && altitude >= airspace->getMinZ())){
			aircraft->setPositionZ(altitude);
		}
	}
	//update the altitude in the hits list
	airspace->setCurrentAircrafts(hitsList);
	delete airspace;
}

void Operator::setVelocity(int aircraftId,double velX, double velY, double velZ){
	for(Aircraft* aircraft : hitsList){
		if(aircraft->getId() == aircraftId){
			aircraft->setVelocityX(velX);
			aircraft->setVelocityY(velY);
			aircraft->setVelocityZ(velZ);
		}
	}
	//update the velocity in the airspace
	Airspace::getAirspace()->setCurrentAircrafts(hitsList);
}

void Operator::setDirection(int aircraftId,double x, double y, double z){
	//update the position when the id matches
	for(Aircraft* aircraft : hitsList){
		if(aircraft->getId() == aircraftId){
			aircraft->setPositionY(y);
			aircraft->setPositionX(x);
			aircraft->setPositionZ(z);
		}
	}
	//update the position in the airspace
	Airspace::getAirspace()->setCurrentAircrafts(hitsList);
}

void Operator::setHoldingPattern(int aircraftId, bool holdingPattern){
	for(Aircraft* aircraft : hitsList){
		if(aircraft->getId() == aircraftId){
			if(holdingPattern == true){
				//aircraft->hold(radius);//TODO determine the radius to hold pattern
			}
			else{
				//TODO remove holding pattern;
			}
		}
	}
	//update holding pattern in airspace
	Airspace::getAirspace()->setCurrentAircrafts(hitsList);
}

string Operator::getAircraftData(int aircraftId){
	string info = "";
	for(Aircraft* aircraft : hitsList){
		if(aircraftId == aircraft->getId()){
			info = aircraft->print(2);
		}
	}
	info = "Could not find the specified plane ID";
	return info;
}

void Operator::setHoldingPatternAll(bool holdingPattern){
	for(Aircraft* aircraft : hitsList){
		if(holdingPattern == true){
			//aircraft->hold(radius);
		}
		else{
			//TODO remove holding pattern
		}
		Airspace::getAirspace()->setCurrentAircrafts(hitsList);
	}
}

void Operator::addAircraft(int id, int x, int y, int z, int velX,int velY, int velZ){
	Aircraft* aircraft = new Aircraft(id,x,y,z,velX,velY,velZ,Timer::getTimer()->getCurrentTime());
	hitsList.push_back(aircraft);
	Airspace::getAirspace()->setCurrentAircrafts(hitsList);
}

void Operator::deleteAircraft(int id){
	int counter = 0;
	for(Aircraft* aircraft : hitsList){
		if(id == aircraft->getId()){
			hitsList.erase(hitsList.begin() + counter);
		}
		counter++;
	}
}

void Operator::send(int id,string message){
	//TODO send message
}

void Operator::broadcast(string message){
	//TODO broadcast messages
}

Aircraft* Operator::predictPath(int id, double projectedTime){
	//TODO predict position of the aircraft given the time
	Aircraft* futureAircraft;
	for(Aircraft* aircraft : hitsList){
			if(id == aircraft->getId()){
				futureAircraft = aircraft;
			}
		}
	if(futureAircraft != nullptr)
		futureAircraft->updatePosition(projectedTime);
	return futureAircraft;
}

bool Operator::checkViolations(double projectedTime){
	bool violation = false;
	//check if there are any collisions with the current aircrafts in the airspace
	for(unsigned int i = 0; i < hitsList.size(); i++){
		for(unsigned int j = i; j< hitsList.size(); j++){
			//don't compare an aircraft to itself
			if(i != j){
				for(int k = 0; k <= projectedTime; k++){
					double time = Timer::getTimer()->getCurrentTime()+k;
					violation = hasCollisions(predictPath(hitsList.at(i)->getId(), time),predictPath(hitsList.at(j)->getId(), time), time);
					if(violation){
						return violation;
					}
				}
			}
		}
			//TODO add to list of danger
	}
	return violation;
}

bool Operator::hasCollisions(Aircraft* aircraft1, Aircraft* aircraft2, double projectedTime){
	bool collisionRisk = false;
	//check elevation distance
	if(abs(aircraft1->getPositionZ() - aircraft2->getPositionZ()) <= 1000.0){
		collisionRisk = true;
		cout<<"Aircraft " + to_string(aircraft1->getId()) + " and Aircraft " + to_string(aircraft2->getId()) + " too close in elevation at " + to_string(projectedTime)<<endl;
	}
	//check the distance between the aircrafts
	if(sqrt(pow((aircraft1->getPositionX()-aircraft2->getPositionX()),2) + pow((aircraft1->getPositionY()-aircraft2->getPositionY()),2)) <= 15840){
		collisionRisk = true;
		cout<<"Aircraft " + to_string(aircraft1->getId()) + " and Aircraft " + to_string(aircraft2->getId()) + " too close in horizontal distance at " + to_string(projectedTime)<<endl;
	}
	return collisionRisk;
}



void Operator::update(){
	cout<<"operator thread"<<endl;
	checkViolations(6.0);
}
