#include "Airspace.h"
#include "Radar.h"
#include "Timer.h"

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <sys/siginfo.h>

using namespace std;

int main(int argc, char *argv[]) {
	//initialize the objects
	Airspace* airspace = new Airspace();
	Radar* radar = new Radar();
	Timer* timer = new Timer();

	//todo create threads
	cout<<"hello there";

	//destroy the objects
	delete airspace;
	delete radar;
	delete timer;

	return EXIT_SUCCESS;
}
