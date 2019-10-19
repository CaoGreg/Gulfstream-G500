#include "Radar.h"

vector<Aircraft> Radar::scan(){
	Airspace* airspace = new Airspace();
	std::vector<Aircraft> aircrafts = airspace->getAircrafts();
	this->hits.clear();

	for(Aircraft aircraft: aircrafts){
		if(airspace->isInAirspace(aircraft)){
			//aircraft detected flag?
			this->hits.push_back(aircraft);
		}
	}
	delete airspace;
	return this->hits;
}
