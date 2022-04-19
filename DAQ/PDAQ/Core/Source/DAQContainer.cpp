//c++-stuff
#include <sstream>
#include <string>
#include "DAQContainer.h"

DAQContainer::DAQContainer(){
	graphic=false;
	calibration=false;
	NumberOfEvents=0;
	NumberPerFile=0;
	savetype=0;
	TriggerRate=0;
	graphicmode=0;
	high=0;
	low=0;
	trigger=0;
	OutputDir="";
	chn0=0;
	chn1=0;
	chn2=0;
	chn3=0;
}


