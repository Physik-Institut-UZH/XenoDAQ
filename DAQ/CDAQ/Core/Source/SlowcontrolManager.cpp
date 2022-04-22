#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>
#include "SlowcontrolManager.h"
#include "global.h"
#include "common.h"

/*
Author: Julien Wulf UZH
Revised: Frédéric Girard
*/


SlowcontrolManager::SlowcontrolManager()
{
	 m_pmtNb,m_BoardInfo,m_baseline,m_errflag,m_graphics,m_lastevents,m_events,m_bytes,m_totalB,m_Nbmodule,m_triggertype=m_totalevents=m_type=m_numberChain=m_verboseFlag=0;
	printf("\n\n\n");
	printf("%s***************************************************************************\n",KGRN);
	printf("\n");
	printf("%s Y88b   d88P                            8888888b.        d8888  .d88888b.   \n",KGRN);
	printf("%s  Y88b d88P                             888  \"Y88b      d88888 d88P\" \"Y88b  \n",KGRN);
	printf("%s   Y88o88P                              888    888     d88P888 888     888  \n",KGRN);
	printf("%s    Y888P     .d88b.  88888b.   .d88b.  888    888    d88P 888 888     888  \n",KGRN);
	printf("%s    d888b    d8P  Y8b 888 \"88b d88\"\"88b 888    888   d88P  888 888     888  \n",KGRN);
	printf("%s   d88888b   88888888 888  888 888  888 888    888  d88P   888 888 Y8b 888  \n",KGRN);
	printf("%s  d88P Y88b  Y8b.     888  888 Y88..88P 888  .d88P d8888888888 Y88b.Y8b88P  \n",KGRN);
	printf("%s d88P   Y88b  \"Y8888  888  888  \"Y88P\"  8888888P\" d88P     888  \"Y888888\"   \n",KGRN);
	printf("%s                                                                      Y8b    \n\n",KGRN);
        printf("%s                        Original Code By Julien Wulf                        \n",KGRN);
        printf("%s                         Revised By Frédéric Girard                         \n",KGRN);
	printf("%s                                version: 6.0                                \n",KGRN);
        printf("%s                                   04-2022                                  \n",KGRN);
	printf("\n");
	printf("%s***************************************************************************\n\n",KGRN);
	printf(RESET);
	sleep(1);
	gettimestring(m_OutputFolder); //Standard save format
	stringstream ss;
	string s;
	ss << GetUnixTime();
	ss >> s;
	

	/*Slowcontrol Folder*/
/*    	string command= "mkdir SlowControl";
    	system(command.c_str());
    	std::cout << std::endl;
 */   
    	/*Generate Current Rate File*/
/*    	string OutputFolder = m_OutputFolder;
	string status = "SlowControl/Rate_" + OutputFolder +  ".txt" ; 
	m_DAQStatus.open(status.c_str());
*/
}


SlowcontrolManager::~SlowcontrolManager()
{
}

int SlowcontrolManager::Init(){

    ApplyXMLFile();
    return 0;
}


//-------------------------------------------------------------------
// Process command line options
int SlowcontrolManager::ProcessInput( int argc, char *argv[], char *envp[])
{
  extern char *optarg;               /* options processing */
  int start;                          /* dummy for options */
  int someArgs=0;

 
  //  search for possible options 
 while ( ( start = getopt( argc, argv, "x:g:f:biowv" ) ) != -1 )  {
      someArgs=1;
      switch (start) {
        case 'f': 
          sprintf(m_OutputFolder,"%s",optarg);
          break;
	  case 'v': 
          	m_verboseFlag = 1;
          break;
        case 'x': 
          sprintf(m_XmlFileName,"%s",optarg);
          break;
	    case 'g':
          m_graphics = 1;
	      m_pmtNb=atoi(optarg);
          break;
        case 'i': 
          m_BoardInfo = 1;
          break;
        case 'b': 
          m_baseline = 1;		// baseline adjustment
          break;
        case 'w':   
	      printf("missed WIMPs protocol:");
		  int i;
	      char txt[100];
		  gettimestring(txt);
          i = (int)((float)rand()/2147483647.*10.);
          printf("  You missed %d WIMPs since stopping DAQ.\n  Better you start it again...\n",i);
	      exit(0);	
	      break;
        case 'o':
	     //control_scopehelp();
	      exit(0);
        default: 
          m_errflag++; 
          break;
        }
  }
  if (m_errflag || someArgs==0) {
      printf(RESET);

      printf("\n===========================================================================\n" );
      printf("                                  Help Menu                                  \n" );
      printf("===========================================================================\n\n" );
      printf("usage:  %s [-f file|-x file||-g p|-b|-i|-v|-h|]\n\n", argv[1] );

      printf("\t-x   Read settings from XML-file file . (Mandatory)\n");      
      printf("\t-f   Write to file .................... (Optional)\n" );
      printf("\t-g p Oscilloscope: Display waveform p . (Optional)\n");
      printf("\t-i   Displays hardware information .... (Optional)\n" );
      printf("\t-b   Adjust baselines automatically ... (Optional)\n" );
      printf("\t-o   Show help for oscilloscope mode .. (Optional)\n");
      printf("\t-v   Enable Verbose Mode .............. (Optional)\n");
      printf("\t-h   Display this help ................ (Optional)\n\n");

      printf("\nStandard syntax to launch acquisition:\n\n" );
      printf("\t./SingleDAQ -x \"fileName.xml\" -f \"fileName\" -opts\n" );
      printf("\t./MultiDAQ  -x \"fileName.xml\" -f \"fileName\" -opts\n\n" );
      printf(RESET);
      exit( 2 );
  }
  
  return m_verboseFlag;
}


int SlowcontrolManager::StartAquistion(){
	
	printf(KYEL);
	printf("\nStart Data Aquisition\n\n");
	printf(RESET);
	gettimeofday(&m_begin, NULL);
    gettimeofday(&m_total, NULL);
	
	
	return 0;
}

int SlowcontrolManager::StopAquistion(){
	
	gettimeofday(&m_end, NULL);
	m_seconds  = m_end.tv_sec  - m_total.tv_sec;
	// print summary and update logfile
	printf(KGRN);
	printf("	\n");    
    	printf("	DAQ stopped\n"); 
    	printf("	Total Measuring time: %.2f s = %f h\n",m_seconds,m_seconds/(60*60));   
    	printf("	Total Number of Events Measured = %i\n",m_events);
   	printf("	\n\n");   
    	printf(RESET);
    	stringstream ss;
	string s;
	ss << GetUnixTime();
	ss >> s;
	
	/*Generate Summary File*/
	string OutputPath = m_OutputPath;
   	string OutputFolder = m_OutputFolder;
    
	string status =  OutputPath + "/"+ OutputFolder + "/Summary_" + OutputFolder +  ".txt" ; 
	m_DAQSummary.open(status.c_str());
	m_DAQSummary << "	DAQ stopped: " << GetUnixTime() <<  "\n" << "	Total Measuring time: "<< m_seconds << " s " << " = " << m_seconds/(60*60) << " h\n " << 	"	Total Number of Events Measured = " <<  m_events  << " \n";
	m_DAQSummary.flush();
	
	
	//Xurich specific
	//m_DAQSummary << "	Lifetime: " << m_seconds-(m_events*2.289/(1000)) ; 

	m_DAQStatus.close();
	m_DAQSummary.close();
	return 0;
}


int SlowcontrolManager::ShowStatus(int status ){
		if(status==1)
			m_events++;
			
		gettimeofday(&m_end, NULL);
		m_seconds  = m_end.tv_sec  - m_begin.tv_sec;
		m_useconds = m_end.tv_usec - m_begin.tv_usec;
		m_time = ((m_seconds) * 1000 + m_useconds/1000.0) + 0.5;
		
		 if(m_time>1000){
			/* print some progress indication */
			printf(KCYN);
			std::cout << "	" << (m_totalB/(1024*1024.))  << " GB "<<   (m_bytes/1048576.) << " MByte/s " << " DAQ-Rate: " << round(((m_events-m_lastevents)/m_time)*1000)<< " Hz " << " Total Events: " << m_events << std::endl;
			m_DAQStatus <<  GetUnixTime() << "      "<< round(((m_events-m_lastevents)/m_time)*1000) << "   "  <<  m_events << "    " <<  (m_totalB/(1024*1024.)) << "\n";
			m_lastevents=m_events;
			gettimeofday(&m_begin, NULL);
			printf(RESET);
			m_bytes=0;
		}
	return 0;
}


int SlowcontrolManager::ApplyXMLFile(){
	int temp;  
	char txt[100];
	const char *xstr;
	txt[0]='\0';

	printf(KYEL);
	printf("For help menu, use '-h'\n\n");

	printf("Initialization in progress. Please wait.\n\n");
	
	if (m_verboseFlag == 1){
		printf("Reading User Configuration XML-File %s\n\n",m_XmlFileName);
	}

	printf(RESET);

	printf(KGRN);
	// open the XML file -------------------------------------------------------
	XMLNode xMainNode=XMLNode::openFileHelper(m_XmlFileName,"settings");

	xstr=xMainNode.getAttribute("author");
	if (xstr) {
		strcpy(txt,xstr); 
		if (m_verboseFlag == 1){
			printf("	(Author: %s)\n",txt);
		}  
	} else error((char*)"XML-author"); 
	
	xstr=xMainNode.getAttribute("date");		
 	if (xstr) {
		strcpy(txt,xstr);
		if (m_verboseFlag == 1){
			printf("	(Date: %s)\n\n",txt);
		}
	} else error((char*)"XML-date"); 	
	
	// parse global DAQ settings -----------------------------------------------
	XMLNode xNode=xMainNode.getChildNode("global");
	if (m_verboseFlag == 1){
		printf("	Global Settings:\n\n");
	}
	
	xstr=xNode.getChildNode("user").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
		printf("	User:        %s\n",txt); 
	}
	} else error((char*)"XML-user");
	
	xstr=xNode.getChildNode("daq_version").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
		printf("	DAQ Version: %s\n",txt); 
	}
	} else error((char*)"XML-daq_version");
	

	xstr=xNode.getChildNode("source").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
		printf("	Source:      %s\n",txt); 
	}
	} else error((char*)"XML-source");

	xstr=xNode.getChildNode("notes").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
		printf("	Comments:    %s\n",txt);
	} 
	} else error((char*)"XML-notes");

	xstr=xNode.getChildNode("path").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
		printf("	Path:        %s\n",txt);
	}
		strcpy(m_OutputPath,txt);
	} else error((char*)"XML-path");

	xstr=xNode.getChildNode("nb_evts").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
    		if (strstr(txt, "-1")!=NULL) printf("	NoF Events:  infinite\n");
       		else printf("	NoF Events:  %s\n",txt);
	}
		m_totalevents=atoi(txt);  
	} else error((char*)"XML-nb_evts");
	
	xstr=xNode.getChildNode("nb_evts_per_file").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
		printf("	Events/File: %s\n",txt);
	}
	} else error((char*)"XML-nb_evts_per_file");

	xstr=xNode.getChildNode("store_data").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		int WriteToFile=atoi(txt); 
		if (WriteToFile<0 || WriteToFile>7) WriteToFile=0;
	if (m_verboseFlag == 1){	
		printf("	File Format: ");
	
		switch (WriteToFile) {
		case 0: printf("Data NOT stored\n"); break;
		case 1: printf("ROOT format\n"); break;
		case 2: printf("ASCII format\n"); break;
		case 3: printf("Binary format\n"); break;
  	}
  }	
	} else error((char*)"XML-store_data");

	xstr=xNode.getChildNode("displaytime").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
		printf("	DisplayTime: %s s\n\n",txt);
	}
		//t.DisplayTime=atoi(txt);  
	} else error((char*)"XML-displaytime");
	
	 // parse global ADC settings -----------------------------------------------
	xNode=xMainNode.getChildNode("adc").getChildNode("global");
	if (m_verboseFlag == 1){
		printf("	ADC: Global settings:\n\n");
	}
	
	xstr=xNode.getChildNode("ADCType").getText();
	if (xstr) {
		strcpy(txt,xstr);
		m_type=atoi(txt);
	if (m_verboseFlag == 1){
		if(m_type==0)
				printf("	ADC: v1720  \n");  
		else if(m_type==1)
				printf("	ADC: v1724    \n"); 
		else if(m_type==2)
				printf("	ADC: v1730    \n"); 
	}
	} else error((char*)"XML-ADCType");
	 
	
	xstr=xNode.getChildNode("nb_modules").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		m_Nbmodule=atoi(txt);
	if (m_verboseFlag == 1){
		printf("	Number Modules: %s\n",txt); 
	}
	} else error((char*)"XML-nb_modules");
	
	m_address=new string[m_Nbmodule];
	
	for(int i=0;i<m_Nbmodule;i++){
		char modules[300];
		sprintf(modules,"address_%i",i);
		xstr=xNode.getChildNode(modules).getText();
		if (xstr) {
			strcpy(txt,xstr);
			stringstream ss;
			ss << txt;
			ss >> m_address[i];
			if (m_verboseFlag == 1){
				printf("	ADC %i Address: %s\n",i,txt);
			}
		} else error((char*)modules);
	}
	
    xstr=xNode.getChildNode("link_in_chain").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		m_numberChain=atoi(txt);
		if (m_verboseFlag == 1){
			printf("	Link in Chain: %s\n",txt);
		} 
	} else error((char*)"link_in_chain");


	//--- Active channels of Modules-------
	for(int j=0;j<m_Nbmodule;j++){
		if (m_verboseFlag == 1){
			printf("	Module: %i\n",j);
		}
		for(int i=0;i<8;i++){
			char channel[300];
			sprintf(channel,"ch_%i",i+j*8);
			xstr=xNode.getChildNode(channel).getText();
			if (xstr) {
				strcpy(txt,xstr);
				temp=atoi(txt);
				if(temp!=0){
					if (m_verboseFlag == 1){
						printf("	Channel %i Active. Threshold: %i\n",i,temp);
					}
				}
		   } else error((char*)channel);
	  }
	}


	xstr=xNode.getChildNode("memoryorganisation").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		int bufSize=atoi(txt);
		float usec;
	    u_int32_t data;
		switch (bufSize) {
			case 512: data=0x0; break;
			case 256: data=0x1; break;
			case 128: data=0x2; break;
			case  64: data=0x3; break;
			case  32: data=0x4; break;
			case  16: data=0x5; break;
			case   8: data=0x6; break;
			case   4: data=0x7; break;
			case   2: data=0x8; break;
			case   1: data=0x9; break;
			case   0: data=0xA; break;  // 0.5 k
			default:  data=0x4; 
					  bufSize=32;
					  break; 
		}
		if (m_verboseFlag == 1){
			printf("	Memory Organisation: %sk Samples/Evt\n",txt);
		}
	} else error((char*)"XML-memoryorganisation");
  

	xstr=xNode.getChildNode("custom_size").getText();
	if (xstr) {
        strcpy(txt,xstr);
        temp=(int)(atoi(txt)/10.);       // 10 samples per memory location
	if (m_verboseFlag == 1){
        	printf("	Custom Size: %d samples\n",temp*10);
	}
	} else error((char*)"XML-custom_size");
  
  

	xstr=xNode.getChildNode("posttrigger").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		if (m_verboseFlag == 1){
			printf("	Posttrigger: %s Samples\n",txt);
		}
		temp=atoi(txt); 
	} else error((char*)"XML-posttrigger");
		
	xstr=xNode.getChildNode("baseline").getText();
	if (xstr) {
		strcpy(txt,xstr);
		if (m_verboseFlag == 1){
			printf("	Baseline:    %s ADC-Counts\n",txt);
		}
		
	} else error((char*)"XML-baseline");
	
	xstr=xNode.getChildNode("baselineiteration").getText();
	if (xstr) {
		strcpy(txt,xstr);
		if (m_verboseFlag == 1){
			printf("	Baseline Iterations:	%s \n",txt);
		}
	} else error((char*)"XML-baselineiteration");
	
	
	xstr=xNode.getChildNode("sampling_freq").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		if (m_verboseFlag == 1){
			printf("	Frequency:   %s Hz\n",txt);
		} 
	} else error((char*)"XML-sampling_freq");
	
	xstr=xNode.getChildNode("voltage_range").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		if (m_verboseFlag == 1){
			printf("	Voltage Range: %s V\n",txt); 
		}
	} else error((char*)"voltage_range");
	
	xstr=xNode.getChildNode("Sample_size_ADC").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		if (m_verboseFlag == 1){
			printf("	Sample Size ADC: %s bit\n",txt); 
		}
	} else error((char*)"Sample_size_ADC");
	
	xstr=xNode.getChildNode("Sample_size_DAC").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		if (m_verboseFlag == 1){
			printf("	Sample Size DAC: %s bit\n\n",txt); 
		}
	} else error((char*)"Sample_size_DAC");
  
	// ADC: parse ADC Trigger Settings
	xNode=xMainNode.getChildNode("adc").getChildNode("triggerSettings");
	if (m_verboseFlag == 1){
		printf("	ADC: Trigger Settings:\n\n");
	}
	
	xstr=xNode.getChildNode("trigger").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		temp=atoi(txt);

    		if (temp==0){ 
			if (m_verboseFlag == 1){
				printf("	Trigger: External\n");
			}
			xstr=xNode.getChildNode("TTL").getText();
			if(xstr) {
				strcpy(txt,xstr);
				temp=(int)(atoi(txt));
				if(temp==1)
					if (m_verboseFlag == 1){
						printf("	Trigger Logic: TTL\n\n");
					}
				else
					if (m_verboseFlag == 1){
						printf("	Trigger Logic: NIM\n\n");
					}
			} else error((char*)"XML-TTL");
		}
  		else if (temp==1){ 
			if (m_verboseFlag == 1){
				printf("	Trigger: Software\n");
			}
			xstr=xNode.getChildNode("SoftwareRate").getText();;
			if (xstr) {
				strcpy(txt,xstr);
				if (m_verboseFlag == 1){ 
					printf("	Software Rate: %s Hz\n\n",txt);
				} 
			}
			else error((char*)"XML-SoftwareRate");
		}
    		else if (temp==2) {
			if (m_verboseFlag == 1){			
				printf("	Trigger: Channel Treshold\n\n");
			}	
		}
    else {
	if (m_verboseFlag == 1){
		printf("	Trigger: Per Channel Trigger Type\n\n");
	}
	}
  } else error((char*)"XML-trigger");

	
	// ADC: parse waveform display options
	xNode=xMainNode.getChildNode("graphics");
	if (m_verboseFlag == 1){
		printf("	Graphics Settings:\n\n");
	}
	xstr=xNode.getChildNode("ydisplay").getText();
	if (xstr) {
		strcpy(txt,xstr); 
	if (m_verboseFlag == 1){
		printf("	y-display: %s\n",txt);
	}
	} else error((char*)"XML-ydisplay");

	xstr=xNode.getChildNode("yaxis_low").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		if (m_verboseFlag == 1){
			printf("	y-axis-low: %s\n",txt);
		}
	} else error((char*)"XML-yaxis_low");
  
	xstr=xNode.getChildNode("yaxis_high").getText();
	if (xstr) {
		strcpy(txt,xstr); 
		if (m_verboseFlag == 1){
			printf("	y-axis-high %s\n",txt);  
		}
	} else error((char*)"XML-yaxis_high");

  
	printf(RESET);
	
    
	return 0;
}
  
//-------------------------------------------------------------------
// stores a copy of the XML file with the data
int SlowcontrolManager::xml_storefile()
{
  char cmnd[300];
  sprintf(cmnd,"cp %s %s.xml",m_XmlFileName,m_OutputPath);
  return 0;
}


