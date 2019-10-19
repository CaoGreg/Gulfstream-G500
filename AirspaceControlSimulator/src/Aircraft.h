#pragma once

class Aircraft
{
	public:
		Aircraft(int id, int x, int y, int z, int velX,int velY, int velZ);
		void updatePosition(int newX,int newY, int newZ, double time);
		int getPositionX();
		int getPositionY();
		int getPositionZ();
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
};
