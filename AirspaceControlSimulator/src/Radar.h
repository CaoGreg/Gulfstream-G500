#pragma once

#include "Aircraft.h"
#include "Airspace.h"
#include "Testcase.h"
#include <vector>
using namespace std;

class Radar
{
	public:
		std::vector<Aircraft> scan();

	private:
		std::vector<Aircraft> hits;
};
