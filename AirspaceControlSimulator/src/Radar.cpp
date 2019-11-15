#include "Radar.h"

Radar* Radar::radar = nullptr;

void Radar::scan(){
	//scan airspace for current aircrafts
	scanned_aircrafts = Airspace::getAirspace()->getCurrentAircrafts();
	Operator::getOperator()->setHitList(scanned_aircrafts);
}

void Radar::update(){
	cout<<"update radar"<<endl;
	scan();
}
