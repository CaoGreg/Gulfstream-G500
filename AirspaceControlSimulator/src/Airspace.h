#pragma once
#include <vector>
#include <deque>
#include "Aircraft.h"
#include <iostream>
using namespace std;

class Airspace
{
	public:
		Airspace();
		virtual ~Airspace(){ delete airspace; }
		static void createInstance(){airspace = new Airspace(); }
		static Airspace* getAirspace(){ return airspace; }
		std::vector<Aircraft*> getAircrafts();
		bool isInAirspace(Aircraft* a);
		void update();
		void updateTime();
		void updatePositions();
		void setEnteringAircrafts();
		void setIncomingAircrafts();
		std::vector<Aircraft*> getEnteringAircrafts(){ return current_aircrafts; }
		std::deque<Aircraft*> getIncomingAircrafts(){ return incoming_aircrafts; }
		std::vector<Aircraft*> getLeftAircrafts(){ return left_aircrafts; }
		void removeFromAirspace();

	private:		
		static Airspace* airspace;
		double maxX; //miles
		double minX;
		double maxY; //miles
		double minY;	
		double maxZ; //feet
		double minZ; //elevation	
		std::vector<Aircraft*> current_aircrafts;
		std::deque<Aircraft*> incoming_aircrafts;
		std::vector<Aircraft*> left_aircrafts;
		bool firstset = true;
		double time;

};
