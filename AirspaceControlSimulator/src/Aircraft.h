#pragma once
#include <string>
using namespace std;

class Aircraft {
public:
	Aircraft(){}
	Aircraft(int id, double velX, double velY, double velZ, double x, double y, double z, double entrytime);
	void updatePosition(double time, bool hold);
	double getPositionX();
	double getPositionY();
	double getPositionZ();
	double getVelocityX();
	double getVelocityY();
	double getVelocityZ();
	void setPositionX(double x);
	void setPositionY(double y);
	void setPositionZ(double z);
	void setVelocityX(double x);
	void setVelocityY(double y);
	void setVelocityZ(double z);
	void setId(int id){ this->id = id; }
	void changeAltitude(double change);
	void changeVel(double velX, double velY, double velZ);
	void changeDir(double x, double y);
	bool isHolding();
	void hold(double radius);
	void stopHolding();
	int getId();
	double getEntryTime();
	double getLeftTime();
	void setLeftTime(double time);
	string print(int choice);
private:
	//id
	int id;
	double timeStamp;
	double entrytime;
	double lefttime;
	//current position
	double x;
	double y;
	double z;
	//previous position
	double prevX;
	double prevY;
	double prevZ;
	double prevTimeStamp;
	//current velocity
	double velX;
	double velY;
	double velZ;
	//holding pattern
	bool holding;
	double radius;
};
