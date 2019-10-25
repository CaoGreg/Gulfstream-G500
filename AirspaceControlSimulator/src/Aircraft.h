#pragma once

class Aircraft
{
	public:
		Aircraft(int id, int x, int y, int z, int velX,int velY, int velZ);
		void updatePosition(double time, double timeVariation);
		double getPositionX();
		double getPositionY();
		double getPositionZ();
		void setPositionX(double x);
		void setPositionY(double y);
		void setPositionZ(double z);
		bool isHolding();
		void hold(double radius);
		void stopHolding();
		int getId();
	private:
		//id
		int id;
		double timeStamp;
		//current position		
		double x;
		double y;
		double z;
		//previous position
		int prevX;
		int prevY;
		int prevZ;	
		double prevTimeStamp;			
		//current velocity
		int velX;
		int velY;
		int velZ;
		//holding pattern
		bool holding;
		double radius;
};
