#pragma once

#include "Aircraft.h"
#include "Airspace.h"
#include "Testcase.h"
#include "Operator.h"
#include "Timer.h"
#include <vector>
#include <cstddef>

class Radar{
	public:
		//std::vector<Aircraft> scan(){return NULL};
		Radar(){};
		virtual ~Radar() { delete radar; } 
		
		static void createInstance(){ radar = new Radar(); }
		static Radar* getRadar(){ return radar;	}
		void scan();
		void update();

	private:
		static Radar* radar;
		std::vector<Aircraft*> scanned_aircrafts; //hits, current planes in the airspace
};
