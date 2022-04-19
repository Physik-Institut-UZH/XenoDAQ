//-------------------------------------------------------------------
//  xml.cpp   --   DAX: DAQ for XENON
// 
//  the xml library contains functions to read the XML settings file
//
//  04.12.2007 MS
//  last revision: 21.03.2008 MS  -- now with proper error handling
//  modified: 17.04.2008 MS
//  modified: 21.04.2008 MS  -  Trigger Latency
//  modified: 20.05.2008 MS  -  Individual ZLE Thresholds
//  modified: 13.06.2008 MS  -  Phillips Hex pattern included
//  modified: 21.07.2008 MS  -	read discriminator settings and 
//				set discriminator
//  modified: 29.11.2010 MS  -  Custom Event length
//   30.05.2015 JW A lot of changes in order to make everything more easy

//-------------------------------------------------------------------

extern "C" {
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#ifdef WIN32
    #include <time.h>
    #include <sys/timeb.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <sys/time.h>
#endif
}

#include "global.h"
#include "adc.h"
#include "control.h"
#include "xmlParser.h"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

//-------------------------------------------------------------------
// display xml parsing error message
int xml_error(char *node)
{
  char txt[120];
  sprintf(txt,":::: WARNING: missing information in xml-file (%s) ::::",node);
  errormsg(0,txt);
  return 0;
}

//-------------------------------------------------------------------
// reads the XML settings file
int xml_readsettings(char filename[100], crate& crt, digitizer& adc, scaler& s,
	multipurposemodule& mp, timeandtrigger& t, var_graphics& graphics,
	u_int32_t& NoE, int& EventsPerFile, char *path, int& WriteToFile)
{
  int temp;  
  char txt[100];
  u_int32_t data, data2, addr;
  const char *xstr;
  txt[0]='\0';
  int bufSize=-1;
  printf(KYEL);
  printf("Reading User Configuration File %s\n",filename);
  
  // open the XML file -------------------------------------------------------
  XMLNode xMainNode=XMLNode::openFileHelper(filename,"settings");

  printf("Settings File %s\n", filename);

  xstr=xMainNode.getAttribute("author");
  if (xstr) {
	strcpy(txt,xstr); 
	printf("  (Author: %s,",txt);	  
  } else xml_error((char*)"author"); 
  
  xstr=xMainNode.getAttribute("date");		
  if (xstr) {
	strcpy(txt,xstr);
	printf("  Date: %s)\n",txt);
  } else xml_error((char*)"date"); 

  // parse global DAQ settings -----------------------------------------------
  XMLNode xNode=xMainNode.getChildNode("global");
  printf("Global Settings:\n");
  
  xstr=xNode.getChildNode("source").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    printf("  Source:      %s\n",txt); 
  } else xml_error((char*)"source");

  xstr=xNode.getChildNode("notes").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  Comments:    %s\n",txt); 
  } else xml_error((char*)"notes");

  xstr=xNode.getChildNode("path").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  Path:        %s\n",txt);
    strcpy(path,txt);
  } else xml_error((char*)"path");

  xstr=xNode.getChildNode("daq_version").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  DAQ Version: %s\n",txt); 
  } else xml_error((char*)"daq_version");

  xstr=xNode.getChildNode("nb_evts").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    if (strstr(txt, "-1")!=NULL) printf("  NoF Events:  infinite\n");
       		            else printf("  NoF Events:  %s\n",txt);
    NoE=atoi(txt); 
  } else xml_error((char*)"nb_evts");

  xstr=xNode.getChildNode("store_data").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    WriteToFile=atoi(txt); 
    if (WriteToFile<0 || WriteToFile>7) WriteToFile=0;	// DM, no data is written as default
    printf("  File Format: ");
    switch (WriteToFile) {
      case 0: printf("Data NOT stored\n"); break;
      case 1: printf("old CAEN format\n"); break;
      case 2: printf("ASCII\n"); break;
      case 3: printf("XENON100 format\n"); break;
      case 4: printf("Integral\n"); break;
      case 7: printf("Write to root file\n"); break; //DM
    }	
  } else xml_error((char*)"store_data");

   xstr=xNode.getChildNode("nb_evts_per_file").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  Events/File: %s\n",txt);
    EventsPerFile=atoi(txt);
  } else xml_error((char*)"nb_evts_per_file");

  xstr=xNode.getChildNode("displaytime").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  DisplayTime: %s s\n",txt);
    t.DisplayTime=atoi(txt);  
  } else xml_error((char*)"displaytime");
    
  xstr=xNode.getChildNode("user").getText();
  if (xstr) {
	strcpy(txt,xstr); 
  printf("  User:        %s\n",txt); 
  } else xml_error((char*)"user");
  
  
  // parse global ADC settings -----------------------------------------------
  xNode=xMainNode.getChildNode("adc").getChildNode("global");
  printf("ADC: Global settings:\n");
  
  xstr=xNode.getChildNode("nb_chs").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    adc.NbChannels=atoi(txt);
   printf("  Channels:    %s\n",txt); 
  } else xml_error((char*)"nb_chs");

  //--- Active channels -------

  xstr=xNode.getChildNode("ch_0").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    //adc.ch0=atoi(txt);
    adc.channel[0]=atoi(txt);
   printf("  Channel 0:     %s\n",txt); 	
  } else xml_error((char*)"ch_0");
  xstr=xNode.getChildNode("ch_1").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    //adc.ch1=atoi(txt);
    adc.channel[1]=atoi(txt);
  printf("  Channel 1:     %s\n",txt); 
  } else xml_error((char*)"ch_1");
  xstr=xNode.getChildNode("ch_2").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    //adc.ch2=atoi(txt);
    adc.channel[2]=atoi(txt);
     printf("  Channel 2:     %s\n",txt); 	
  } else xml_error((char*)"ch_2");
  xstr=xNode.getChildNode("ch_3").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    //adc.ch3=atoi(txt);
    adc.channel[3]=atoi(txt);
    printf("  Channel 3:     %s\n",txt); 	
  } else xml_error((char*)"ch_3");
  xstr=xNode.getChildNode("ch_4").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    //adc.ch4=atoi(txt);
    adc.channel[4]=atoi(txt);
    printf("  Channel 4:     %s\n",txt);	
  } else xml_error((char*)"ch_4");
  xstr=xNode.getChildNode("ch_5").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    //adc.ch5=atoi(txt);
    adc.channel[5]=atoi(txt);
   printf("  Channel 5:     %s\n",txt);
  } else xml_error((char*)"ch_5");
  xstr=xNode.getChildNode("ch_6").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    //adc.ch6=atoi(txt);
    adc.channel[6]=atoi(txt);
    printf("  Channel 6:     %s\n",txt); 	
  } else xml_error((char*)"ch_6");
  xstr=xNode.getChildNode("ch_7").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    //adc.ch7=atoi(txt);
    adc.channel[7]=atoi(txt);
    printf("  Channel 7:     %s\n",txt); 	
  } else xml_error((char*)"ch_7");


  
  xstr=xNode.getChildNode("nb_samples_per_evt").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    bufSize=atoi(txt);
    float usec;
    switch (bufSize) {
      case 512: data=0x0; usec=5242.88; break;
      case 256: data=0x1; usec=2621.44; break;
      case 128: data=0x2; usec=1310.72; break;
      case  64: data=0x3; usec=655.36; break;
      case  32: data=0x4; usec=327.98; break;
      case  16: data=0x5; usec=163.84; break;
      case   8: data=0x6; usec=81.92; break;
      case   4: data=0x7; usec=40.96; break;
      case   2: data=0x8; usec=20.48; break;
      case   1: data=0x9; usec=10.24; break;
      case   0: data=0xA; usec=5.12; break;  // 0.5 k
      default:  data=0x4; 
      	        errormsg(0,(char*)":::: WARNING: Set Samples/Evt to 32k ::::");
		bufSize=32;
	break; 
    }
    printf("  Samples/Evt: %sk (%.2f us)\n",txt,usec);
    for (int i=0; i<adc.NumberOfADCs; i++) {
      if (adc_writereg(crt,adc,i,BlockOrganizationReg,data)<0) return -1; 
    }  
  } else xml_error((char*)"nb_samples_per_evt");

  xstr=xNode.getChildNode("custom_size").getText();
  if (xstr) {
        strcpy(txt,xstr);
        temp=(int)(atoi(txt)/2.);       // 2 samples per memory location
    // catch possible errors
        if (temp!=0 && bufSize==-1) {
          errormsg(0,(char*)":::: ERROR: define 'nb_samples_per_event' before 'custom_size' ::::");
          return -1;
        }
        bufSize=bufSize*1024;
    if (bufSize==0) bufSize=512;
    if (temp*2>bufSize) {
          errormsg(0,(char*)":::: ERROR: custom window must be smaller than nb_samples_per_event*1024 ::::");
          return -1;
        }
        printf("  Custom Size: %d samples\n",temp*2);
        data=temp;
        adc.EventLength=data*2;
    for (int i=0; i<adc.NumberOfADCs; i++) {
          if (adc_writereg(crt,adc,i,CustomWindow,data)<0) return -1;
        }
  } else xml_error((char*)"custom_size");
  
  xstr=xNode.getChildNode("posttrigger").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  Posttrigger: %s\n",txt);
    temp=atoi(txt);
    data=(temp-adc.TriggerLatency)/2;	// convert in 32bit words words  
    for (int i=0; i<adc.NumberOfADCs; i++) {
      if (adc_writereg(crt,adc,i,PostTriggerReg,data)<0) return -1; 
    }  
  } else xml_error((char*)"posttrigger");

  xstr=xNode.getChildNode("baseline").getText();
  if (xstr) {
	strcpy(txt,xstr);
    printf("  Baseline:    %s\n",txt);
    adc.baseline=atoi(txt);
  } else xml_error((char*)"baseline");

  xstr=xNode.getChildNode("trigger").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    adc.trig=atoi(txt);
    if (adc.trig!=0) printf("  Trigger:     S%d\n",adc.trig);
  	        else printf("  Trigger:     external\n");
    if (adc.trig<0 || adc.trig>2) {
      errormsg(0,(char*)":::: WARNING: This trigger mode does not exist. Set to S2 trigger. ::::\n");
      adc.trig=2;
    }  
    if (adc.trig==1) data=0x0;	// S1: Majority Mode
                else data=0x2;  // S2: Analog Sum (also used if external trigger, adc.trig=0
    for (int i=0; i<adc.NumberOfADCs; i++) {
      if (adc_writereg(crt,adc,i,MonitorModeReg,data)<0) return -1; 
    }  
  } else xml_error((char*)"trigger");
                         
  // check if correct!!!
  if (adc.trig==0) { // external trigger -> disable all internal triggering
    adc.trigmask=0x0;
  }

  if (adc.trig==1) {
    xstr=xNode.getChildNode("s1_thresh").getText();
    if (xstr) {
      strcpy(txt,xstr); 
      temp=atoi(txt);
      printf("  S1 threshold %s\n",txt); 
      data=adc.baseline-temp;
      for (int i=0; i<adc.NumberOfADCs; i++) {
        if (adc_writereg(crt,adc,i,S1Threshold,data)<0) return -1; 
      }
    } else xml_error((char*)"s1_thresh");
  }

  xstr=xNode.getChildNode("sampling_freq").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    adc.sampling_freq=atoi(txt);
     printf("  Frequency:   %s Hz\n",txt); 
  } else xml_error((char*)"sampling_freq");
  
  xstr=xNode.getChildNode("sample_size").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    adc.sample_size=atoi(txt);
     printf("  Sample Size: %s bit\n",txt); 
  } else xml_error((char*)"sample_size");

  xstr=xNode.getChildNode("voltage_range").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    adc.voltage_range=atof(txt);
   printf("  Volt. Range: %s V\n",txt); 
  } else xml_error((char*)"sampling_freq");
  
  xstr=xNode.getChildNode("busy").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    adc.busy=atoi(txt);
    if (adc.busy) printf("  BUSY:        On\n");
  	         else printf("  BUSY:        Off\n");
    if (adc.busy!=0) adc.busy=1;
    xstr=xNode.getChildNode("ttl").getText();
    strcpy(txt,xstr); 
    int ttl=atoi(txt);
    if (ttl==1){ printf("  TTL:        On\n");}
    else{printf("  TTL:        OFF\n");}
    if(ttl==1){	
    	for (int i=0; i<adc.NumberOfADCs; i++) {	
      	if (adc.busy) {
        	if (adc_writereg(crt,adc,i,FrontPanelIOData,0x41)<0) return -1; // enable busy output
      	} else {
        	if (adc_writereg(crt,adc,i,FrontPanelIOData,0x1)<0) return -1;  // disable busy output 
      	}
     }
    }
     else{
	for (int i=0; i<adc.NumberOfADCs; i++) {	
      	if (adc.busy) {
        	if (adc_writereg(crt,adc,i,FrontPanelIOData,0x40)<0) return -1; // enable busy output
      	} else {
        	if (adc_writereg(crt,adc,i,FrontPanelIOData,0x0)<0) return -1;  // disable busy output 
      	}
	}
     }
  } else xml_error((char*)"busy");

   // ADC: parse ZLE settings -----------------------------------------------
  xNode=xMainNode.getChildNode("adc").getChildNode("zle_settings");
  printf("ADC: ZLE Settings:\n");
  
  // This XML-entry sets the ZLE mode and takes also care of the 
  // trigger mask, that is read above
  xstr=xNode.getChildNode("zle").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    temp=atoi(txt);  
    // Falling + Sequential + External signal + Non Overlap Triggers + AnalogSum
    if (temp==1) { 	// ZLE
      data=0x200D0; 
      printf("  ZLE:         On\n");	    
      if (WriteToFile==4) {
        errormsg(0,(char*)":::: ERROR: Integral Mode only works when ZLE is disabled ::::");
        return -1;
      }  
    } else { 		// no ZLE encoding	
      data=0xD0; 	
      printf("  ZLE:         Off\n");
    }   

    int trg;  
    for (int i=0; i<adc.NumberOfADCs; i++) {	
      if (adc.trigmask>>i&0x1) { data2=data; trg=1; }
      		  	  else { data2=data-0x80; trg=0; } // no Analog Sum Output
      if (adc_writereg(crt,adc,i,ChannelConfigReg,data2)<0) return -1; 
      if (trg==0) {
        if (adc.trig==1) 
          if (adc_writereg(crt,adc,i,MonitorModeReg,0x2)<0) return -1; // set to Analog Monitor Mode
								       // in order to disable channels
        if (adc_writereg(crt,adc,i,AnalogMonitorSettings,0x0)<0) return -1;  // disable all 8 channels
      }
      //adc_writereg(crt,adc,i,ChannelConfigReg,data2+0x8);
      //errormsg(0,"Generate Test Pattern on Module");
    }  
  } else xml_error((char*)"zle");
  
  xstr=xNode.getChildNode("threshold").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  Threshold:   %s\n",txt);
    temp=atoi(txt);
    data=adc.baseline-temp;
    data=data+0x80000000;
    for (int i=0; i<adc.NumberOfADCs; i++) {
      if (adc_writereg(crt,adc,i,ZLEThreshold,data)<0) return -1; 
    }  
  } else xml_error((char*)"threshold");
  
  xstr=xNode.getChildNode("n_pre").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  N_pre:       %s\n",txt);
    temp = atoi(txt)/2;  
    data = temp;  
  } else xml_error((char*)"n_pre");
   
  xstr=xNode.getChildNode("n_post").getText();
  if (xstr) {
	strcpy(txt,xstr); 
    printf("  N_post:      %s\n",txt);
    temp = atoi(txt)/2;
    data = data + (temp<<16);
    for (int i=0; i<adc.NumberOfADCs; i++) {
      if (adc_writereg(crt,adc,i,LookBackForward,data)<0) return -1; 
    }  
  } else xml_error((char*)"n_post");
    
  // special thresholds for particular PMTs
  xNode=xMainNode.getChildNode("adc").getChildNode("zle_settings").getChildNode("special_thresholds");
  int specialNb=xNode.nChildNode("pmt_thresh");

  int tmp1=0;
  int tmp2=0;
  int pmt, threshold, module, channel;
  printf("  Special ZLE Thresholds:\n");	  
  for (int i=0; i<specialNb; i++) {
    xstr=xNode.getChildNode("pmt_thresh",&tmp1).getAttribute("pmtNb");
    if (xstr) pmt=atoi(xstr);
         else xml_error((char*)"pmt_thresh"); 
    xstr=xNode.getChildNode("pmt_thresh",&tmp2).getAttribute("value");
    if (xstr) threshold=atoi(xstr);
         else xml_error((char*)"pmt_thresh"); 
    printf("    PMT%3d:    %d\n",pmt,threshold);
    if (control_getadc(adc, pmt, module, channel)==0) {
      addr=SingleZLEThresh+channel*0x100;
      data=adc.baseline-threshold;
      data=data+0x80000000;
      if (adc_writereg(crt,adc,module,addr,data)<0) return -1;
    } else errormsg(0,(char*)":::: WARNING: PMT does not exist ::::");
  }
  
  // ADC: parse waveform display options
  xNode=xMainNode.getChildNode("adc").getChildNode("graphics");
  
  xstr=xNode.getChildNode("xdisplay").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    graphics.x_display = atoi(txt);    
  } else xml_error((char*)"xdisplay");

  xstr=xNode.getChildNode("ydisplay").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    graphics.y_display = atoi(txt);    
  } else xml_error((char*)"ydisplay");

  xstr=xNode.getChildNode("xaxis_low").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    graphics.x_low = atoi(txt);    
  } else xml_error((char*)"xaxis_low");
  
  xstr=xNode.getChildNode("xaxis_high").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    graphics.x_high = atoi(txt);    
  } else xml_error((char*)"xaxis_high");

  xstr=xNode.getChildNode("yaxis_low").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    graphics.y_low = atoi(txt);    
  } else xml_error((char*)"yaxis_low");
  
  xstr=xNode.getChildNode("yaxis_high").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    graphics.y_high = atoi(txt);    
  } else xml_error((char*)"yaxis_high");

  xstr=xNode.getChildNode("xautorange").getText();
  if (xstr) {
    strcpy(txt,xstr); 
    graphics.x_autorange = atoi(txt);    
  } else xml_error((char*)"xautorange");
  printf(RESET);
  return 0;
}

	
//-------------------------------------------------------------------
// stores a copy of the XML file with the data
int xml_storefile(char *filename, char *OutFileName)
{
  char cmnd[300];
  sprintf(cmnd,"cp %s %s.xml",filename,OutFileName);
  if (system(cmnd)!=0) errormsg(0,(char*)":::: WARNING: Could not save a copy of XML-file ::::");
  
  return 0;
}


