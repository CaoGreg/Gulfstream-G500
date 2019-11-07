#pragma once

#include "Aircraft.h"
#include "Airspace.h"
#include "Testcase.h"
#include <vector>
#include <cstddef>

class Radar{
	public:
		//std::vector<Aircraft> scan(){return NULL};
		Radar(){}
		
		virtual ~Radar() { delete radar; } 
		
		static void createInstance(){ radar = new Radar(); }
		static Radar* getRadar(){ return radar;	}

	private:
		std::vector<Aircraft> hits;
		static Radar* radar;
};
