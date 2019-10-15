#ifndef ATC_H_
#define ATC_H_

#endif /*ATC_H_*/
#include "Aircraft.h"
#include "Airspace.h"
#include <vector>

class ATC
{
	public:
		ATC();
		void addAircraft(Aircraft* aircraft);				
			
	private:	
		Airspace* airspace;	
		std::vector<Aircraft*> aircraftList;		
};
