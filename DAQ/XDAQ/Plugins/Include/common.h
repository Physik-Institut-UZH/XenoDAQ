#ifndef COMMON_H
#define COMMON_H

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <fstream> 
#include "CAENVMElib.h"


/*Author: Julien Wulf UZH
  General functions and stuff for every Module. The function name describes it very good.
*/

using namespace std;
class Common
{
  public:                            
	Common();   
	string GetTime();    
	int GetUnixTime();
	string GetDayYear();
	string GetDay();
  private:
	string t;
        char* buffer;
  protected:
	string Message;
};

#endif
