#include "Radar.h"

Radar* Radar::radar = nullptr;

void Radar::scan(){
	//scan airspace for current aircrafts
	scanned_aircrafts = Airspace::getAirspace()->getCurrentAircrafts();
	Operator::getOperator()->setHitList(scanned_aircrafts);
	TrackFile::getTrackFile()->setHits(scanned_aircrafts);
	//Operator::getOperator()->checkViolations(180.0);
}

void Radar::update(){
	AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexLock();
	//cout<<"Radar task"<<endl;
	scan();
	AirspaceControlSimulator::getAirspaceControlSimulator()->threadMutexUnlock();
}
