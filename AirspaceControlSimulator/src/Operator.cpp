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

void Operator::changeAltitude(int aircraftId, double altitude){
	//update the altitude when the id matches
	if(aircraftId <= -1){
		cout << "You cannot modify an unknown aircraft!" << endl;
	}else{
		bool found = false;
		for(Aircraft* aircraft : hitsList){
			if(aircraft->getId() == aircraftId /*&& (altitude <= airspace->getMaxZ() && altitude >= airspace->getMinZ())*/){
				aircraft->changeAltitude(altitude);
				cout << "Altitude changes sent to aircraft id " << to_string(aircraftId) << endl;
				found = true;
			}
		}
		if(!found){
			cout << "Aircraft id" << to_string(aircraftId) << " not found" << endl;
		}
	}
}

void Operator::changeVelocity(int aircraftId,double velX, double velY, double velZ){
	if(aircraftId <= -1){
		cout << "You cannot modify an unknown aircraft!" << endl;
	}else{
		bool found = false;
		for(Aircraft* aircraft : hitsList){
			if(aircraft->getId() == aircraftId){
				aircraft->changeVel(velX, velY, velZ);
				found = true;
				cout << "Velocity changed!" << endl;
			}
		}
		if(!found){
			cout << "Aircraft id" << to_string(aircraftId) << " not found" << endl;
		}
	}
}

void Operator::changeDirection(int aircraftId,double x, double y){
	if(aircraftId <= -1){
		cout << "You cannot modify an unknown aircraft!" << endl;
	}else{
		bool found = false;
		for(Aircraft* aircraft : hitsList){
			if(aircraft->getId() == aircraftId){
				aircraft->changeDir(x, y);
				found = true;
				cout << "Direction changed!" << endl;
			}
		}
		if(!found){
			cout << "Aircraft id" << to_string(aircraftId) << " not found" << endl;
		}
	}
}

void Operator::setHoldingPattern(int aircraftId, bool holdingPattern){
	if(aircraftId <= -1){
		cout << "You cannot modify an unknown aircraft!" << endl;
	}else{
		bool found = false;
		for(Aircraft* aircraft : hitsList){
			if(aircraft->getId() == aircraftId){
				found = true;
				if(holdingPattern == true){
					aircraft->hold(300);
					cout << "Aircraft " << to_string(aircraft->getId()) << " is holding" << endl;
				}
				else{
					aircraft->stopHolding();
					cout << "Aircraft " << to_string(aircraft->getId()) << " stopped holding" << endl;
				}
			}
		}
		if(!found){
			cout << "Aircraft id" << to_string(aircraftId) << " not found" << endl;
		}
	}
}

string Operator::getAircraftData(int aircraftId){
	string info = "";
	for(Aircraft* aircraft : hitsList){
		if(aircraftId == aircraft->getId()){
			info = aircraft->print(2);
		}
	}
	if(info.compare("") == 0){
		info = "Could not find the specified plane ID\n";
	}
	return info;
}

void Operator::setHoldingPatternAll(bool holdingPattern){
	for(Aircraft* aircraft : hitsList){
		if(aircraft->getId() != -1){
			if(holdingPattern == true){
				aircraft->hold(300);
				cout << "Aircraft " << to_string(aircraft->getId()) << " is holding" << endl;
			}
			else{
				aircraft->stopHolding();
				cout << "Aircraft " << to_string(aircraft->getId()) << " stopped holding" << endl;
			}
		}else{
			cout << "You cannot modify an unknown aircraft!" << endl;
		}
	}
}

void Operator::addAircraft(int id, int velX,int velY, int velZ, int x, int y, int z){
	Aircraft* aircraft = new Aircraft(id,velX,velY,velZ, x,y,z, Timer::getTimer()->getCurrentTime());
	//hitsList.push_back(aircraft);
	//Airspace::getAirspace()->setCurrentAircrafts(hitsList);
	Airspace::getAirspace()->addAircraft(aircraft);
}

void Operator::deleteAircraft(int id){
	AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexLock();
	if(id <= -1){
		cout << "You cannot delete an unknown aircraft!" << endl;
	}else{
		Airspace::getAirspace()->deleteAircraft(id);
	}
	AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexUnlock();
}

void Operator::projectedPath(int id, double projectedTime){
	if(id <= -1){
		cout << "You cannot forecast an unknown aircraft!" << endl;
	}else{
		bool found = false;
		for(Aircraft* aircraft : hitsList){
			if(aircraft->getId() == id){
				double t = Timer::getTimer()->getCurrentTime();
				double time = t + projectedTime;
				Aircraft ac = predictPath(aircraft, time);
				Aircraft* pac = &(ac);
				string future = string("Aircraft: ") + to_string(pac->getId()) + " at time: " + to_string(time) + " will be at (" + to_string(pac->getPositionX()) + "," + to_string(pac->getPositionY()) + "," + to_string(pac->getPositionZ()) +
						") moving at (" + to_string(pac->getVelocityX()) + "," + to_string(pac->getVelocityY()) + "," + to_string(pac->getVelocityZ()) + ")\n";
				found = true;
				cout << future << endl;
				if(Airspace::getAirspace()->isInAirspace(pac)){
					cout << "The airspace will have left the airspace" << endl;
				}
			}
		}
		if(!found){
			cout << "Aircraft id" << to_string(id) << " not found" << endl;
		}
	}
}

void Operator::send(int id,string message){
	//TODO send message
}

void Operator::broadcast(string message){
	for(Aircraft* aircraft : hitsList){
		if(aircraft->getId() == -1){
			int newId = rand() % 1000 + 1000;
			aircraft->setId(newId);
			cout << "My id is " << to_string(newId) << endl;
		}
	}
}

Aircraft Operator::predictPath(Aircraft* ac, double projectedTime){
	//TODO predict position of the aircraft given the time
	Aircraft futureAircraft;
	bool found = false;
	for(Aircraft* aircraft : hitsList){
		if(ac->getId() == aircraft->getId()){
			futureAircraft = *aircraft;
			found = true;
		}
	}
	if(found)
		futureAircraft.updatePosition(projectedTime, futureAircraft.isHolding());
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
					Aircraft a1 = predictPath(hitsList.at(i), time);
					Aircraft* pa1 = &(a1);
					Aircraft a2 = predictPath(hitsList.at(j), time);
					Aircraft* pa2 = &(a2);
					violation = hasCollisions(pa1,pa2,time);
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
//1 9 1 1 1 948 765 18000


/* Commands: 1 = add aircraft (id velx vely velz x y z)
 * 			 2 = delete (id)
 * 			 3 = change altitude (id elevation change)
 * 			 4 = set velocity (id velx vely velz)
 * 			 5 = set direction (id x y z)
 * 			 6 = getAircraftData (id)
 * 			 7 = setHolding pattern (one or all, true or false, id
 * 			 8 = projectAircraft (id projected time)
 * 			 9 = ask for identification
 * 			 10 = help
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
			break;
		case 3:
			id = listCommand[1];
			changeAltitude(id, listCommand[2]);
			break;
		case 4:
			id = listCommand[1];
			changeVelocity(id, listCommand[2], listCommand[3], listCommand[4]);
			break;
		case 5:
			id = listCommand[1];
			changeDirection(id, listCommand[2], listCommand[3]);
			break;
		case 6:
			id = listCommand[1];
			cout << getAircraftData(id);
			break;
		case 7:
			if(listCommand[1] == 2){
				setHoldingPatternAll(listCommand[2]);
			}else if(listCommand[1] == 1){
				setHoldingPattern(listCommand[3], listCommand[2]);
			}else{
				cout << "Invalid input" << endl;
			}
			break;
		case 8:
			id = listCommand[1];
			projectedPath(id, listCommand[2]);
			break;
		case 9:
			broadcast("Identify yourself");
			break;
		case 10:
			cout << "Commands: 1 = add aircraft (id velx vely velz x y z)" << endl
			<< "	  2 = delete aircraft (id)" << endl
			<<	"	  3 = change altitude (id elevation change)" << endl
			<<	"	  4 = change velocity (id velx vely velz)" << endl
			<<	"          5 = change direction (id x y z)" << endl
			<<	"	  6 = getAircraftData (id)" << endl
			<< "	  7 = setHolding pattern (one (1) or all (2), true (1) or false (0), id)" << endl
			<< "     	  8 = projectAircraft (id projected time)" << endl
			<< "          9 = ask for identification" << endl
			<< "          10 = help" << endl;
			break;
		default:
			cout << "Invalid command" << endl;
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
