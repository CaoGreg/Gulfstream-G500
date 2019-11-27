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
	if(info.compare("") == 0){
		info = "Could not find the specified plane ID";
	}
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

void Operator::addAircraft(int id, int velX,int velY, int velZ, int x, int y, int z){
	Aircraft* aircraft = new Aircraft(id,velX,velY,velZ, x,y,z, Timer::getTimer()->getCurrentTime());
	//hitsList.push_back(aircraft);
	//Airspace::getAirspace()->setCurrentAircrafts(hitsList);
	Airspace::getAirspace()->addAircraft(aircraft);
	cout << Airspace::getAirspace()->getCurrentAircrafts().size();
}

void Operator::deleteAircraft(int id){
	AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexLock();
	Airspace::getAirspace()->deleteAircraft(id);
	AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexUnlock();
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
	if(Airspace::getAirspace()->isInAirspace(aircraft1) && Airspace::getAirspace()->isInAirspace(aircraft2)){
		if(abs(aircraft1->getPositionZ() - aircraft2->getPositionZ()) <= 1000.0){
			collisionRisk = true;
			DisplayManager::getDisplayManager()->addToViolations("Aircraft " + to_string(aircraft1->getId()) + " and Aircraft " + to_string(aircraft2->getId()) + " too close in elevation at " + to_string(projectedTime) + "\n");
		}
		//check the distance between the aircrafts
		if(sqrt(pow((aircraft1->getPositionX()-aircraft2->getPositionX()),2) + pow((aircraft1->getPositionY()-aircraft2->getPositionY()),2)) <= 15840){
			collisionRisk = true;
			DisplayManager::getDisplayManager()->addToViolations("Aircraft " + to_string(aircraft1->getId()) + " and Aircraft " + to_string(aircraft2->getId()) + " too close in horizontal distance at " + to_string(projectedTime) + "\n");
		}
	}
	return collisionRisk;
}

//1 8 1 1 1 948 765 18000

/* Commands: 1 = add aircraft (id, velx vely vel z, x y z)
 * 			 2 = delete (id)
 * 			 3 = set altitude (id, elevation change)
 * 			 4 = set velocity (id, velx vely velz)
 * 			 5 = set direction (id, x y z)
 * 			 6 = getAircraftData (id)
 * 			 7 = setHolding pattern (one or all, true or false, id
 * 			 8 = projectAircraft (id, projected time)
 * 			 9 = help
 *
 */

void Operator::executeCommand(string command){
	string value;
	int id, velX, velY, velZ, x, y, z;
	if(!command.empty()){
		stringstream X(command);
		vector<int> listCommand;
		while(getline(X, value, ' ')){
			int val;
			istringstream(value) >> val;
			listCommand.push_back(val);
		}
		switch(listCommand[0]){
		case 1:
			id = listCommand[1];
			velX = listCommand[2];
			velY = listCommand[3];
			velZ = listCommand[4];
			x = listCommand[5];
			y = listCommand[6];
			z = listCommand[7];

			addAircraft(id, velX, velY, velZ, x, y, z);
			cout << "Added aircraft!" << endl;
			break;
		case 2:
			id = listCommand[1];
			deleteAircraft(id);
			cout << "Delete aircraft!" << endl;
			break;
		}
	}
}

void Operator::update(){
	//AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexLock();
	//cout<<"operator thread"<<endl;
	//checkViolations(180.0);
	string command;
	getline(cin, command);
	executeCommand(command);
	//timedInput();
	//AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexUnlock();

}
