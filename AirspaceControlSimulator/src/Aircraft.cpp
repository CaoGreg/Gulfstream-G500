#include "Aircraft.h"

Aircraft::Aircraft(int id, int x, int y, int z, int velX,int velY, int velZ){
	this->id = id;
	this->x = x;
	this->y = y;
	this->z = z;
	this->velX = velX;
	this->velY = velY;
	this->velZ = velZ;
	this->prevX = 0;
	this->prevY = 0;
	this->prevZ = 0;
	this->prevTimeStamp = 0;
	this->timeStamp = 0;
	this->holding = false;
	this->radius = 0;
}

void Aircraft::updatePosition(double time, double timeVariation){
	
	this->prevX = x;
	this->prevY = y;
	this->prevZ = z;
	this->prevTimeStamp = this->timeStamp;
	
	//update the position and the timestamp
	this->x = this->velX * timeVariation;
	this->y = this->velY * timeVariation;
	this->z = this->velZ * timeVariation;
	this->timeStamp = time;	
}

double Aircraft::getPositionX(){
	return this->x;
}

double Aircraft::getPositionY(){
	return this->y;
}

double Aircraft::getPositionZ(){
	return this->z;
}

void Aircraft::setPositionX(double x){
	this->x = x;
}

void Aircraft::setPositionY(double y){
	this->y = y;
}

void Aircraft::setPositionZ(double z){
	this->z = z;
}

void Aircraft::hold(double radius){
	this->radius = radius;
	this->holding = true;
}

bool Aircraft::isHolding(){
	return this->holding;
}

void Aircraft::stopHolding(){
	this->holding = false;
}

int Aircraft::getId(){
	return this->id;
}
