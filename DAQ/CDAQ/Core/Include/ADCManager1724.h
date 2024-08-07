#ifndef _ADCMANAGER1724_H_
#define _ADCMANAGER1724_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CAENVMElib.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include "xmlParser.h"
#include "ADCManager.h"
#include "common.h"



using namespace std;

/*
Author: Julien Wulf UZH
Class to manage the CAEN v1720 Flash ADC 
The ADC will be configurated over the register file (NECESSARY)!!! In order to give the user the maxmimum amount of freedom
*/


class ADCManager1724: public Common, public ADCManager
{
public:
		ADCManager1724();
		virtual ~ADCManager1724();
    
		//Init Function
		int Init(int);

    
private:

		//Read Register from ADC
		int RegisterReading(int);

		int ApplyXMLFile();											//Read XML-Config for the Storage Manager
};

#endif

