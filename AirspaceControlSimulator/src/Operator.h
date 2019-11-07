/*
 * Operator.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Greg
 */
#include "Aircraft.h"
#include "Airspace.h"
#include <string>
#include <vector>
//using namespace std;
#ifndef OPERATOR_H_
#define OPERATOR_H_

class Operator{
public:
	Operator();
		
	virtual ~Operator(){ delete operater; }

	static void createInstance(){ operater = new Operator(); }
	//commands for a given aircraft
	static Operator* getOperator(){ return operater; }
	void setAltitude(int aircraftId, double elevationChange);
	void setSpeed(int aircraftId, double speed);
	void setDirection(int aircraftId,int x, int y, int z);
	void setHoldingPattern(int aircraftId, bool holdingPattern);
	//commands for all aircrafts
	Aircraft getAircraftData(int aircraftId);
	void setHoldingPatternAll(bool holdingPattern);
	//operator requests
	void addAircraft(int id, int x, int y, int z, int velX,int velY, int velZ);
	void deleteAircraft(int id);
	//some vector getProjectedPosition(int id, double n); get projected postion funtion must make a vector class
	//get all aircraft

	//computer commands
	void send(int id,string message);
	void broadcast(string message);

	//setHitList(vector<Aircraft&> hits);

	//check violations
	void predictPath(int id);
	bool checkViolations();
	bool hasCollisions(int id1, int id2);
private:
	static Operator* operater; //operator is a keyword
};



#endif /* OPERATOR_H_ */
