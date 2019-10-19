#include <cstdlib>
#include <iostream>
#include "Airspace.h"
#include <time.h>
#include <sys/siginfo.h>

using namespace std;

int main(int argc, char *argv[]) {
	//ATC* atc = new ATC();
	//timer_create(1,)
	Airspace airspace = Airspace();
	int x = 100;
	int y = 20;
	int z = 40000;
	Aircraft aircraft = Aircraft(x,y,z,0,0,0,0);

	cout<<airspace.isInAirspace(aircraft);
	return EXIT_SUCCESS;
}
