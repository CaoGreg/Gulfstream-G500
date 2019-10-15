#ifndef AIRSPACE_
#define AIRSPACE_

#endif /*AIRSPACE_*/

class Airspace
{
	public:
		Airspace();
		bool isInAirspace(double x, double y, double z);
	private:		
		double maxX; //miles
		double minX;
		double maxY; //miles
		double minY;	
		double maxZ; //feet
		double minZ; //elevation	
};

