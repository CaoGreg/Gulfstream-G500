#pragma once
#include "Aircraft.h"
#include "Timer.h"
#include "TestCase.h"
#include "Operator.h"
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

class Airspace
{
	public:
		//object initialization
		Airspace();
		virtual ~Airspace(){ delete airspace; }
		static void createInstance(){airspace = new Airspace(); }
		static Airspace* getAirspace(){ return airspace; }

		//airspace functionality
		bool isInAirspace(Aircraft* a);
		void update();
		void updateTime();
		void updatePositions();
		void updateCurrentAircrafts();
		void setCurrentAircrafts(vector<Aircraft*> updatedAircrafts);
		void setIncomingAircrafts();
		std::vector<Aircraft*> getCurrentAircrafts(){ return current_aircrafts; }
		std::deque<Aircraft*> getIncomingAircrafts(){ return incoming_aircrafts; }
		std::vector<Aircraft*> getLeftAircrafts(){ return left_aircrafts; }
		void removeFromAirspace();
		double getMinZ(){ return this->minZ; }
		double getMaxZ(){ return this->maxZ; }


	private:
		//airspace instance
		static Airspace* airspace;

		//dimensions of the airspace
		double maxX; //miles
		double minX;
		double maxY; //miles
		double minY;	
		double maxZ; //feet
		double minZ; //elevation	

		//lists holding the aircrafts
		std::vector<Aircraft*> current_aircrafts;
		std::deque<Aircraft*> incoming_aircrafts;
		std::vector<Aircraft*> left_aircrafts;
		double time;
};
