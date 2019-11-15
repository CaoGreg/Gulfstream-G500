#include "Aircraft.h"
#include <iostream>
using namespace std;

Aircraft::Aircraft(int id, double velX, double velY, double velZ, double x, double y, double z, double entrytime){
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
	this->prevTimeStamp = entrytime;
	this->timeStamp = entrytime;
	this->entrytime = entrytime;
	this->holding = false;
	this->radius = 0;
	this->lefttime = 0;
}

void Aircraft::updatePosition(double time){

	this->prevX = x;
	this->prevY = y;
	this->prevZ = z;
	this->prevTimeStamp = this->timeStamp;
	double timeVariation = time - this->prevTimeStamp;

	//update the position and the timestamp
	this->x += this->velX * timeVariation;
	this->y += this->velY * timeVariation;
	this->z += this->velZ * timeVariation;
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

double Aircraft::getVelocityX(){
	return this->velX;
}

double Aircraft::getVelocityY(){
	return this->velY;
}

double Aircraft::getVelocityZ(){
	return this->velZ;
}

void Aircraft::setVelocityX(double velx){
	this->x = velx;
}

void Aircraft::setVelocityY(double vely){
	this->y = vely;
}

void Aircraft::setVelocityZ(double velz){
	this->z = velz;
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

double Aircraft::getEntryTime(){
	return this->entrytime;
}

double Aircraft::getLeftTime(){
	return this->lefttime;
}

void Aircraft::setLeftTime(double time){
	this->lefttime = time;
}

string Aircraft::print(int choice){
	string aircraft;
	switch(choice){
	case 1:	aircraft =  string("Aircraft: ") + to_string(getId()) + " at (" + to_string(getPositionX()) + "," + to_string(getPositionY()) + "," + to_string(getPositionZ()) +
			") moving at (" + to_string(getVelocityX()) + "," + to_string(getVelocityY()) + "," + to_string(getVelocityZ()) + ") and entry time: " + to_string(getEntryTime()) + "\n";
	break;
	case 2: aircraft =  string("Aircraft: ") + to_string(getId()) + " at (" + to_string(getPositionX()) + "," + to_string(getPositionY()) + "," + to_string(getPositionZ()) +
			") moving at (" + to_string(getVelocityX()) + "," + to_string(getVelocityY()) + "," + to_string(getVelocityZ()) + "), entry time: " + to_string(getEntryTime()) +
			" and current time: "+ to_string(this->timeStamp) + "\n";
	break;
	case 3: aircraft =  string("Aircraft: ") + to_string(getId()) + " at (" + to_string(getPositionX()) + "," + to_string(getPositionY()) + "," + to_string(getPositionZ()) +
			") moving at (" + to_string(getVelocityX()) + "," + to_string(getVelocityY()) + "," + to_string(getVelocityZ()) + ") and leaving time: " + to_string(getLeftTime()) + "\n";
	break;
	}
	return aircraft;
}
