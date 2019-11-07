#pragma once
#include <vector>
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
		std::vector<Aircraft> getAircrafts();
		bool isInAirspace(Aircraft a);
		void update(){std::cout<<"Update airspace"<<endl;}

	private:		
		static Airspace* airspace;

		double maxX; //miles
		double minX;
		double maxY; //miles
		double minY;	
		double maxZ; //feet
		double minZ; //elevation	
		std::vector<Aircraft> current_aircrafts;
		std::vector<Aircraft> incoming_aircrafts;
		void updateTime();
		void updatePositions(double time, double timeVariation);
		void getEnteringAircrafts();
};

