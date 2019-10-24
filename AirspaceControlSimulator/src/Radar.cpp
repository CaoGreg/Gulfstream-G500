#include "Radar.h"

vector<Aircraft> Radar::scan(){
	TestCase* testCase = new TestCase();
	int size = sizeof(testCase->airplane_schedule);
	static int ufo_position = -1;
	for(int i = 0; i < size; i+= 8){
		int id = testCase->airplane_schedule[i];
		if(id < 0){
			ufo_position--;
		}
		//TODO add aircraft to hits
	}

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
