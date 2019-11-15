/*
 * DisplayManager.h
 *
 *  Created on: Nov 15, 2019
 *      Author: Greg
 */

#ifndef DISPLAYMANAGER_H_
#define DISPLAYMANAGER_H_

#include <string>
#include <iostream>
#include "Airspace.h"
#include "Operator.h"

using namespace std;

class DisplayManager{
public:
	//object initialization
	DisplayManager();
	virtual ~DisplayManager(){ delete displaymanager; }
	static void createInstance(){ displaymanager = new DisplayManager(); }
	static DisplayManager* getDisplayManager(){ return displaymanager; }

	void addToViolations(string s);

	void update();

private:
	static DisplayManager* displaymanager;
	string displayedViolations = "";
};



#endif /* DISPLAYMANAGER_H_ */
