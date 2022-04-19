/******************************************************************************

  miniDAX  -- DAQ for XENON Detectors
  
  *****************************************************************************
  Version 0.1 
    29.09.2008	MS	first miniDAX version (= DAX w/o scaler, multipurpose 
						 module, discriminator, ...)
  *****************************************************************************
  DAX History:
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  Version 0.1:
    29.11.2007 	MS -- 	modular version of DAQTest
    03.12.2007 	MS -- 	DAQTest fully modularized
  		 	automatic baseline determination included
			separate ini-file for baselines
    04.12.2007	MS -- 	xml-file for user settings; program further modularized
    05.12.2007  MS --	basic log file included
    10.12.2007  MS --	Scaler included -- counts written to log-file
    			Graphical output of a channel during DAQ possible
    11.12.2007  MS --   colorful output; start screen; errormsg included
			Graph. output now also supports non ZLE data
    14.12.2007  MS --	code ZLE status in 3rd header word
    11.01.2008  MS --	internal debugging option for V1724
    			more settings possible via xml-File
    16.01.2008  MS --   setting of HE Veto via V1495 possible
    24.01.2008  MS --	scaler software trigger -> read all channels simultaneously
    08.02.2008  MS --   small changes and cosmetics
    10.03.2008  MS --   moving program to new DAQ machine (64bit)
    18.03.2008  MS --	errormsg printed to logfile
    19.03.2008  MS --	information file for slow control
    21.03.2008  MS -- 	xml-file: adc busy, error handling
    25.03.2008  MS --	disable analog sum output for external trigger (LED)
    26.03.2008  MS --	modifications for automatic baseline setting
    28.03.2008  MS --	increase performance of Oscilloscope Mode
  Version 1.0:
    28.03.2008  MS -- 	update to XENON100 file format
    02.04.2008  MS --   Osc. mode, cosmetics, bug fixes for Xe100 format
    03.04.2008	MS -- 	bug fixes in automatic baseline adjustment
    09.04.2008  MS --   bug fix in baseline adjustment; baseline analysis added
    12.04.2008  MS --   S1 trigger threshold setting via xml-file possible
    17.04.2008  MS --   trigger latency in post trigger setting
    21.04.2008  MS -- 	trigger latency can be adjusted in DAXConfig.ini
    05.05.2008  MS -- 	write to Conf Reload Register possible (via ini-file)
    20.05.2008  MS -- 	v1.0.1 set individual thresholds via xml-file
    10.06.2008  MS -- 	v1.0.2 print dead and lifetime to log-file
    13.06.2008  MS --   v1.0.3 Phillips in log File, changed Trg -> DAQ in output
    24.06.2008  MS --   v1.0.4 Store DAQ rate in log file; start xed-files with event 0 (was -1)
    27.06.2008  MS --   v1.0.5 catch ctrl-c
    01.07.2008  MS -- 	v1.0.6 write UNIX time and DeltaTime to CNT in logfile
    07.07.2008  MS --	v1.0.7 create directory for data automatically
    24.07.2008  MS --	v1.0.8 set discriminator via xml; debugging options for missing events
    20.11.2010  MS --   v1.0.9 cosmetics
    13.01.2012  AB --   v1.1.0 root tree, more data handling variants, shifting some settings from hard code to xml file
    02.03.2012	AB --	v1.2.0 save full waveforms in root format
    15.08.2013  DM --   v1.3.0 read out several channels. Simplified and window length de-hardcoded.
    30.05.2015  JW --   v2.0.0 A lot of changes in order to make everything more easy
	
	
  MS -- Marc Schumann, Zurich University, marc.schumann@@gmx.net    
  AB -- Annika Behrens
  DM -- Daniel Mayani
  JW -- Julien Wulf

 *****************************************************************************
  Based on: miniDAX with root readout by AB
  which is based on:		DAQTest.cpp, version from 28.11.2007 by MS
  which is based on:	Wave Dump, v1.4 (17.09.2007) by C. Tintori (c.tintori@caen.it)
******************************************************************************/

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
}

#include "global.h"	// define data structures
#include "keyb.h"	// getch() and kbhit() for Linux
#include "CAENVMElib.h"	// CAEN VME library
#include "control.h"	// functions to control the program
#include "adc.h"	// functions to deal with the CAEN fADCs
#include "xml.h"	// analyze the XML file with the user settings
#include "graph.h"	// functions for the graphics display
//#include <libxdio.h>	// for Xe100 Data Storage
#include <signal.h>	// to catch for Ctrl-C 

#include <sstream>
#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TGraph.h>

#include <TTree.h>
#include <TBranch.h>
//#include "vector.h"
#include <TFile.h>
 #define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"
//--------------------------------------------------------------------------
// catch CTRL-C, otherwise files etc. are not closed properly
void sigproc(int sig)
{ 		 
  signal(SIGINT, sigproc); 
  errormsg(0,(char*)":::: WARNING: please use 'q' to stop the DAQ ::::");
}

//--------------------------------------------------------------------------
// MAIN 
int main(int argc, char *argv[], char *envp[] ) 
{   
    signal(SIGINT, sigproc);

    // ------------------------------------------------------------------
    // Define variables
    
    // stuff for reading ini files 
    char ConfigFileName[100]   = "miniDAXConfig.ini";
    char BaselineFileName[100] = "miniDAXBaseline.ini";
    char PMTMappingFileName[100] = "miniDAXPMT.ini";
    char OutFileName[100]="";
    char XmlFileName[100]="";
    char SwRelease [100] = "2.0.0 (30/05/2015)";
    
    // variables to hold information
    crate crt;			// variable to store information on Crates    
    digitizer adc;		// variable to store information on ADCs    
    timeandtrigger t;		// variable for timing and trigger counting purposes
    scaler s;			// variable to hold scaler information
    multipurposemodule mp;	// variable to hold multipurpose model info
    
    // stuff for writing data
    int FileCounter=0;
    int FileEvtCounter=-1;
    int EventsPerFile=100;
    FILE *ofile;		// file to store data
    FILE *logfile;		// log information (times, scalers, etc)

    // stuff for reading data
    u_int32_t *buff[ADC_MAX];
    int EnableInt, EnableOLIrq, EnableBerr, EvAlign; // to read from VME Control Register
    char c;
    int quit; 
    int ret;
    int blt_bytes;
    CAEN_BYTE IrqMask, IrqCheckMask;
            
    // Variables for Program Options
    int WriteToFile=5;		// specify data format (default=ROOT tree format) 
    int time, baseline;

    var_graphics graphics;
    u_int32_t NoE;
    char text[100];
    int32_t ms;


    // ------------------------------------------------------------------
    // Start with main program

    // Program Title 
    control_printtitle(SwRelease);
        
    // Command Line Parameter processing    
    printf(KYEL);
    control_cmdline( argc, argv, envp, time, NoE, graphics, baseline, adc,  
  		OutFileName, XmlFileName);
  
    // read hardware configuration file (set default values first)
    control_setdefault(adc, s, t, crt, mp, graphics);
    if (control_configfile(ConfigFileName, crt, adc, s, mp, WriteToFile)<0) return -1;
			   
    // read baseline config file (baseline settings for all channels)
    ret=control_configfile(BaselineFileName, crt, adc, s, mp, WriteToFile); 
    if (ret<0) { if (ret!=-3) goto exit_prog; }

    // read PMT mapping file
    ret=control_configfile(PMTMappingFileName, crt, adc, s, mp, WriteToFile);
         
    // read XML file if defined; these settings overwrite the *.ini settings!
    if (strlen(XmlFileName)!=0) {
      char path[100];
      if (xml_readsettings(XmlFileName,crt,adc, s, mp, t, graphics, NoE, EventsPerFile, path, WriteToFile)!=0) {
        adc_closecrates(crt);   
 	exit(-1);
      }
      if (strlen(OutFileName)==0) control_generatefilename(OutFileName, path,baseline);
      xml_storefile(XmlFileName, OutFileName);
    } else if (strlen(OutFileName)==0) strcpy(OutFileName, "dummy");

    if (WriteToFile == 0) errormsg(0,(char *)":::: WARNING: No data is written! ::::");

    // open log-file
    if (control_openlog(&logfile,OutFileName,SwRelease)<0) goto exit_prog;    
    control_log(logfile,0,(char *)"store logfile handler");  	// store the logfile filehandle as static
							// in this function (used to write to logfile)
    // give information to Slow Control -- DAQ is running
    control_scfile(10,0,0);

    // different pre-defined configuration (no ZLE etc.) for baseline determination
    if (baseline) { 
      if (control_configbaseline(crt, adc)<0) goto exit_prog;
    }
        
    // Initialize the boards and set variables for acquisition        
    //   adc.BoardInfo==1: Information on the modules is printed to screen
    adc_init(crt, adc, EnableInt, EnableOLIrq, EnableBerr, EvAlign);	
    if (adc.BoardInfo) goto exit_prog;      

    // open root output to display waveforms graphically
    TApplication *theApp;
    TCanvas *win;
    TH1D *g;

    if (graphics.on) {
      theApp = new TApplication("App", &argc, argv);
      win = new TCanvas("win","ZDaq -- DAQ for Zuerich",1);
      g = new TH1D("g","g",adc.EventLength-1,0,adc.EventLength-1);
      if (graphics.pmtNb>0) control_getadc(adc, graphics.pmtNb, graphics.module, graphics.channel); 
      graph_init(theApp, win, g, graphics);
    }    
            
    if (!EnableBerr) {  // BERR must be enabled!
      errormsg(0,(char *)":::: ERROR: BERR must be enabled to run the program! ::::");
      goto exit_prog;
    }
    
    // wait some time 
    sleep(1);    
    printf("\n%d Boards Configured\n",adc.NumberOfADCs);
    printf("\n%i Event Length\n",adc.EventLength);
        
    //  Allocate Memory           
    //    Set maximum buffer size for event readout based on current configuration
    //    calculate needed size in Bytes first and allocate space for one more BLT
    adc.BufferSize = (EvAlign&&EnableBerr) ? (adc.ExpectedEvSize* EvAlign*4):(adc.ExpectedEvSize*4); 
    adc.BufferSize += adc.BltSize; 

    for (int i=0; i<adc.NumberOfADCs; i++) {
      if ( (buff[i] = (u_int32_t *)malloc(adc.BufferSize)) == NULL) {
        sprintf(text,":::: ERROR: Can't allocate memory buffer %d of %d kB ::::", i,adc.BufferSize/1024);
        errormsg(0,text);
        goto exit_prog;
      }
    }

    // Automatic baseline determination
    if (baseline) { 
      if (baseline==1) {
        if (adc_getbaseline(crt,adc)<0) errormsg(0,(char *)":::: ERROR in baseline determination ::::");
      } else {
        if (adc_analyzebaseline(crt,adc)<0) errormsg(0,(char *)":::: ERROR in baseline analysis ::::");
      }
      goto exit_prog;
    }  
           
    // ------------------------------------------------------------------
    // Readout    
    
    // Initialize time and trigger counters
    t.totnb=0; 
    t.last_totnb=0;
    t.tottrg=0;
    t.last_tottrg=0;    
    for (int i=0; i<10; i++) t.store10[i]=0;
    t.last_ave=0;
    t.MeasSeconds=0;
                    
    // Start Acquisition
    adc_enable(crt,adc);
    col((char *)"green"); 
	printf("\nAcquisition started. [q] quit\n"); 
    control_printlog(logfile,1,(char*)"DAQ started");    
    t.PreviousTime = get_time();
    quit = 0;
	
	//ROOT data file    
		TFile *orootfile;
		TTree *t1;
		int wf0[adc.EventLength]; 
		int wf1[adc.EventLength]; 
		int wf2[adc.EventLength]; 
		int wf3[adc.EventLength]; 
		int wf4[adc.EventLength]; 
		int wf5[adc.EventLength]; 
		int wf6[adc.EventLength]; 
		int wf7[adc.EventLength];  
		double freq;  
		freq=0;

    printf(RESET);
    // Readout Loop ----------------------------------------------------------
    while(!quit) {

        // open file if data should be stored
	if (WriteToFile>0 && FileEvtCounter==-1) {
	  if ((WriteToFile==1)||(WriteToFile==2)||(WriteToFile==4)) {
 	    if (control_openfile(&ofile,OutFileName,FileCounter,WriteToFile,adc,logfile)<0) goto exit_prog;	  
	  } 
	  else if(WriteToFile==7) {
		if (control_openrawrootfile(&orootfile,&t1,OutFileName,FileCounter,WriteToFile,adc,logfile,wf0,wf1,wf2,wf3,wf4,wf5,wf6,wf7,freq)<0) goto exit_prog;	    
	  }
	  FileCounter++;
	  FileEvtCounter=0;
	}    	
    
	// Check keyboard commands
        c = 0;
        if (kbhit()) c = getch();
        if (c == 'q' || c == 'Q') quit = 1;
	if (graphics.on) graph_checkkey(graphics, adc, c, g, OutFileName);

	// Calculate throughput rate (every second) and read scaler
	if (control_calcrate(t, s, FileEvtCounter,freq)<0) goto exit_prog;
		        	    	   	    
	// Interrupts: 
        // If enabled, wait for the interrupt request from the digitizer. In this mode,
        // there is no CPU time wasting because the process sleeps until there are at least
        // N event available for reading, where N is the content of the register Interrupt
        // Event Number (0xEF18)
        if (EnableInt) {		
	    if (EnableOLIrq) IrqMask = 0x01; // IRQ1 is used when interrupt generated via OLINK
			else IrqMask = 0xFF; // All VME Interrupt Enabled

            CAENVME_IRQEnable(crt.handle[0], IrqMask); // Enable IRQs
	    ret = CAENVME_IRQWait(crt.handle[0], IrqMask, 1000); // Wait for IRQ (max 1sec)
	    if (ret) continue; 

  	    ret=CAENVME_IRQCheck(crt.handle[0], &IrqCheckMask);                           
	    CAENVME_IRQDisable(crt.handle[0], IrqMask); // Disable IRQs	    	    	    
        }

        for (int i=0; i<adc.NumberOfADCs; i++) { // loop over all boards
	  	  
	  // Read data from module i in MBLT mode into buff[i]
          blt_bytes=adc_mblt(crt,adc,i,buff[i]);
	  if (blt_bytes<0) goto exit_prog;
	    
          t.totnb += blt_bytes;	  // Total number of bytes transferred
	  
	  // this statement is important to ensure that reading/writing
	  // always starts from module 0; i.e., the program starts again 
	  // with the first module when nothing was read
	  // (probably not neccessary when interrupts work properly)
          if (!EnableInt && blt_bytes==0) { 
            if (i==0) break; 
                 else { 
                  char errstr[100];
   		  sprintf(errstr,":::: WARNING: module %d returns nothing (evt: %d) ::::",i,FileEvtCounter); 
		  errormsg(1,errstr); 
   	 	}   
          }
	 
	  // Write Data 
	  if ((WriteToFile==0)||(WriteToFile==1)||(WriteToFile==2)||(WriteToFile==0)) {	
	    ret=control_writedata(adc,i,ofile,WriteToFile,blt_bytes,buff[i]);
	    if (ret>=0) {
	      t.tottrg+=ret; FileEvtCounter+=ret;
  	    }
		else goto exit_prog;
	  } 
  
	  else if(WriteToFile==7){ //Root tree only raw waveforms
	    ret=control_writerootrawdata(adc,i,orootfile,t1,WriteToFile,blt_bytes,buff[i],wf0,wf1,wf2,wf3,wf4,wf5,wf6,wf7,freq);
		if (ret>=0) {
			t.tottrg+=ret; FileEvtCounter+=ret;
		} 	
    	else goto exit_prog;
	  }

	  // Display Waveform?
	  if (graphics.on && graphics.module==i) {
	    if (adc.ZLE) ret=graph_display(g,buff[i],graphics.channel);
	    	    else ret=graph_displayNoZLE(g,buff[i],graphics.channel);
 	    if (ret<0) errormsg(1,(char *)":::: WARNING: Cannot display waveform! ::::"); 	    
	    else { 
 	      graph_edit(g,graphics,adc); 	
	      g->Draw();
	      win->Update();
	    }  
	  }  

       } // end: for loop over boards
              
       // max Number of Events per File reached?
		if (WriteToFile>0 && FileEvtCounter==EventsPerFile) { 
			if ((WriteToFile==1)||(WriteToFile==2)||(WriteToFile==4)) {
				if (fclose(ofile)!=0) {
					errormsg(1,(char *)":::: ERROR: cannot close data file! ::::");
					goto exit_prog;
				}
			} 
			else if ((WriteToFile==5)||(WriteToFile==6)||(WriteToFile==7)){
				orootfile->cd();
    				t1->Write();
    				orootfile->Close();   	
	   		}

				
	 FileEvtCounter=-1;	// flag to create new file
       }
        
       // Check if Number of Events to be measured are reached
       if (NoE>0 && t.tottrg==NoE) quit=1;
       // Check if time to be measured is reached
       if (time>0 && t.MeasSeconds>=time) quit=1;
       
    } // end: readout-loop ------------------------------------------------------
    printf(KGRN);
    // print summary and update logfile
    ms = get_time()-t.PreviousTime;
    control_calctime(t,ms,text);
	printf("  %s\n",text);    
    control_printlog(logfile,1,(char*)"DAQ stopped");    
    control_printlog(logfile,0,text);    
    sprintf(text,"Total Number of Events Measured = %d", t.tottrg);
    printf("  %s\n\n",text); 
    control_printlog(logfile,0,text);    
     printf(RESET);
    // close data-file(s)
    if (WriteToFile>0 && quit && FileEvtCounter>=0) {
		if ((WriteToFile==1)||(WriteToFile==2)||(WriteToFile==4)){	
			if (fclose(ofile)!=0) errormsg(1,(char *)":::: ERROR: cannot close data file! ::::\n");
		} 
		else if ((WriteToFile==5)||(WriteToFile==6)||(WriteToFile==7)){
			if (orootfile==NULL) errormsg(1,(char*)":::: output ROOT file does not exist ::::\n");
			else {
				orootfile->cd();
				t1->Write();
				orootfile->Close();
			}
		}

	}
    
    for (int i=0; i<adc.NumberOfADCs; i++) free(buff[i]);
        
// terminate program
exit_prog:
    adc_closecrates(crt);   
    if (!baseline && !adc.BoardInfo) fclose(logfile);   
    control_scfile(0,0,1);	// information to Slow Control -- DAQ is stopped
    printf(RESET);
    return 0;
}

