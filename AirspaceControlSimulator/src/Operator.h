/*
 * Operator.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Greg
 */
#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "Aircraft.h"
#include "AirspaceControlSimulator.h"
#include <string>
#include <vector>
#include <string>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <sstream>
#include <stdlib.h>
//#include <conio.h>

using namespace std;

class Operator{
public:
	//object initialization
	Operator();
	virtual ~Operator(){ delete operater; }
	static void createInstance(){ operater = new Operator(); }
	static Operator* getOperator(){ return operater; }

	//commands for a given aircraft
	void changeAltitude(int aircraftId, double elevationChange);
	void changeVelocity(int aircraftId, double velX, double velY, double velZ);
	void changeDirection(int aircraftId,double x, double y);
	void setHoldingPattern(int aircraftId, bool holdingPattern);
	//commands for all aircrafts
	string getAircraftData(int aircraftId);
	void setHoldingPatternAll(bool holdingPattern);
	//operator requests
	void addAircraft(int id, int velX,int velY, int velZ, int x, int y, int z);
	void deleteAircraft(int id);
	void projectedPath(int id, double projectedTime);
	//some vector getProjectedPosition(int id, double n); get projected postion funtion must make a vector class

	//get all aircraft
	void update();

	//computer commands
	void executeCommand(string command);
	void send(int id,string message);
	void broadcast(string message);

	void setHitList(vector<Aircraft*> hits);

	//check violations
	Aircraft predictPath(Aircraft* ac, double projectedTime);
	bool checkViolations(double projectedTime);
	bool hasCollisions(Aircraft* aircraft1, Aircraft* aircraft2, double projectedTime);
private:
	static Operator* operater; //operator is a keyword
	vector<Aircraft*> hitsList;
	int choice;
};

#endif /* OPERATOR_H_ */
