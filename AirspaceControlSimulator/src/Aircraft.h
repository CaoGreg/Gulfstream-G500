#pragma once

class Aircraft
{
	public:
		Aircraft(int id, int x, int y, int z, int velX,int velY, int velZ);
		void updatePosition(double time, double timeVariation);
		int getPositionX();
		int getPositionY();
		int getPositionZ();
		bool isHolding();
		void hold(double radius);
		void stopHolding();
	private:
		//id
		int id;
		double timeStamp;
		//current position		
		int x;
		int y;
		int z;
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
