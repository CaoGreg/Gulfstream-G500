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
}

void Aircraft::updatePosition(int newX, int newY, int newZ, double time){
	
	this->prevX = x;
	this->prevY = y;
	this->prevZ = z;
	this->prevTimeStamp = this->timeStamp;
	
	//update the position and the timestamp
	this->x = newX;
	this->y = newY;
	this->z = newZ;
	this->timeStamp = time;	
}

int Aircraft::getPositionX(){
	return this->x;
}

int Aircraft::getPositionY(){
	return this->y;
}

int Aircraft::getPositionZ(){
	return this->z;
}