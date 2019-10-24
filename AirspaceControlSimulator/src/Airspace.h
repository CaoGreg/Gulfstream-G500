#pragma once
#include <vector>
#include "Aircraft.h"
using namespace std;

class Airspace
{
	public:
		Airspace();
		std::vector<Aircraft> getAircrafts();
		bool isInAirspace(Aircraft a);

	private:		
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

