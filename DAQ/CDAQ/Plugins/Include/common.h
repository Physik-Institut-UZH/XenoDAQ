#ifndef COMMON_H
#define COMMON_H

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <fstream> 
#include "global.h"


/*Author: Julien Wulf UZH
  General functions and stuff for every Module. The function name describes it very good.
*/

using namespace std;
class Common
{
  public:
	  Common();   
	  virtual ~Common();
	  int32_t get_time();
	  int GetUnixTime();
	  void gettimestring(char* buffer);
	  int   error(char *node);
	  static std::string getdotdaqdir();
	  int m_verboseFlag;		//Verbose Flag: 0 = OFF, 1 = ON
};

#endif
