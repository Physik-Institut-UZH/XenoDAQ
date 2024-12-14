/******************************************************************************

  DAQ      : DAQ for any kind of Detectors
  @author  : Julien Wulf
  @Comment : DAQ to control a Multiple CAEN flash ADC

  LogBook:
			JW - 07.12.2015 - First Stable Version v1.0.0 (Some Trigger features are missing)
			JW - 08.12.2015 - Self Trigger implemented, trehshold can be controlled with w, e, r, t and i
			JW - 10.01.2016 - ADC Extended for v1720, v1724 and 1730D, Postrigger controlable with o & p
******************************************************************************/


//C++ Libraries
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <math.h>
#include <vector>
#include <sys/time.h>
#include <string>
#include <Riostream.h>
#include <iostream>

//Some Classes
#include "keyb.h"	// getch() and kbhit() for Linux
#include <signal.h>	// to catch for Ctrl-C 
#include <global.h>
#include <VMEManager.h>
#include <ADCManager1730.h>
#include <ADCManager1724.h>
#include <ADCManager1720.h>
#include "ADCManager.h"
#include <ScopeManager.h>
#include <StorageManager.h>
#include <SlowcontrolManager.h>


//Root Libaries
#include <TH1D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFile.h>
#include <TLatex.h>
#include "TTree.h"
#include "TFile.h"
#include "TROOT.h"

//--------------------------------------------------------------------------
// catch CTRL-C, otherwise files etc. are not closed properly
void sigproc(int sig)
{ 		 
  signal(SIGINT, sigproc); 
  printf(KRED);
  printf("	WARNING: please use 'q' to stop the DAQ\n");
  printf(RESET);
}
//--------------------------------------------------------------------------
// MAIN
int main(int argc, char *argv[], char *envp[] )
{
    	signal(SIGINT, sigproc);
    
    	//Managers
    
    	//SlowcontrolManager
	int m_verboseFlag = 0;
	SlowcontrolManager* slowcontrolManager = new SlowcontrolManager();
	m_verboseFlag = slowcontrolManager->ProcessInput(argc, argv, envp);
	if(slowcontrolManager->Init()==-1)
		return 0;
		
	//VME-Manger (optical daisychain)
	std::vector <VMEManager*> vManager;
	for(int i=0;i<slowcontrolManager->GetNbModules();i++){
		vManager.push_back(new VMEManager());	
		vManager[i]->SetPCILink(0);
		vManager[i]->SetBoardNumber(i);
    		if(vManager[i]->Init()==-1)
			return 0;
	}
	
	
	std::vector <ADCManager*> adcs;
	std::vector <StorageManager*> storages;
	char baseline[50];
	int number=slowcontrolManager->GetNbModules();
	for(int i=0;i<slowcontrolManager->GetNbModules();i++){
		if(slowcontrolManager->GetADCType()==0)
			adcs.push_back(new ADCManager1720());	
		else if(slowcontrolManager->GetADCType()==1)
			adcs.push_back(new ADCManager1724());	
		else if(slowcontrolManager->GetADCType()==2)
			adcs.push_back(new ADCManager1730());	
			
		adcs[i]->SetCrateHandle(vManager[i]->GetCrateHandle());
		adcs[i]->SetADCAddress(slowcontrolManager->GetAddress(i));
		adcs[i]->SetModuleNumber(i);
		if(i==0){
			adcs[i]->SetRegisterFile("RegisterConfig_Module_0.ini");
		}
		else{
			adcs[i]->SetRegisterFile("RegisterConfig_Module_x.ini");
		}				
		sprintf(baseline, "Module_%i_DACBaseline.ini", i);
		std::string bp = Common::getdotdaqdir();
		bp.append("/Baseline/");
		bp.append(baseline);
		adcs[i]->SetBaselineFile(bp.c_str());
		adcs[i]->SetXMLFile(slowcontrolManager->GetXMLFile());

		if(adcs[i]->Init(m_verboseFlag)==-1);
	}
	if(slowcontrolManager->GetADCInformation()) return 0;
	if(slowcontrolManager->GetBaselineCalculation()){
		for(int i=0;i<number;i++){
                        adcs[i]->ReadBaseLine(m_verboseFlag);
			adcs[i]->CalculateBaseLine();
		}
		return 0;
	}
	else{
		for(int i=0;i<number;i++){
				adcs[i]->ReadBaseLine(m_verboseFlag);
		}
	}
	//Scope-Manager
	ScopeManager* scopeManager = new ScopeManager();
	scopeManager->SetEventLength(adcs[0]->GetEventLength());				//Master Board
	scopeManager->SetXMLFile(slowcontrolManager->GetXMLFile());
	scopeManager->SetChannelNumber(slowcontrolManager->GetChannelNumber());
	scopeManager->SetModuleNumber(slowcontrolManager->GetNbModules());
	if(slowcontrolManager->GetGraphicsActive()){
		//ROOT Manager
		TApplication *theApp;
		theApp = new TApplication("App", &argc, argv);	
		if(scopeManager->Init(m_verboseFlag)==-1)
			return 0;
	}

	//StorageManager
	for(int i=0;i<slowcontrolManager->GetNbModules();i++){
		storages.push_back(new StorageManager());	
		storages[i]->SetBuffer(adcs[i]->GetBuffer());
		storages[i]->SetEventLength(adcs[i]->GetEventLength());
		storages[i]->SetXMLFile(slowcontrolManager->GetXMLFile());
		storages[i]->SetFolderName(slowcontrolManager->GetFolderName());
		string folder=Form("Module%i/",i);
		storages[i]->SetModuleFolder(folder);
		storages[i]->SetModuleNumber(i);
		if(storages[i]->Init(m_verboseFlag)==-1);
	}
	

   //Stuff for the keyboard
    char c;
    int quit=0; 
    int* counter;
	counter = new int[slowcontrolManager->GetNbModules()];
	for(int i=0;i<slowcontrolManager->GetNbModules();i++){
		counter[i]=0;
	}
    c=0;
   
	printf(KYEL);
	printf("Initialization Complete.\n");
	printf(RESET);

    slowcontrolManager->StartAquistion();
    for(int i=0;i<slowcontrolManager->GetNbModules();i++){
		adcs[i]->ClearMemory();				//clear memory before aquisition
		adcs[i]->Enable();
    }

	while(slowcontrolManager->GetNumberEvents()!=storages[0]->GetNumberEvents() && quit!=1){
		
		c = 0;  
		if (kbhit()) c = getch();
		if (c == 'q' || c == 'Q') quit = 1;	

		if(slowcontrolManager->GetGraphicsActive())	
			scopeManager->graph_checkkey(c);

		if(adcs[0]->GetTriggerType()==1){
				usleep(adcs[0]->GetSoftwareRate());
		}


		if(adcs[0]->CheckInterrupt()){
		 	continue;
		}

		//Get Event Check all ADCs always <slowcontrolManager->GetNbModules()
		for(int i=0;i<slowcontrolManager->GetNbModules();i++){	

					if(adcs[0]->GetTriggerType()==1 && i==0){				//software trigger from the master board
						if(adcs[0]->SoftwareTrigger()<-1) return 0;						
					}
	
					if(adcs[i]->CheckEventBuffer()==-1) return 0;
										
					//std::cout << adcs[i]->GetTransferedBytes() << std::endl;	

					//Skip events with 0-bytes
					if(adcs[i]->GetTransferedBytes()<=0){	//always start from the first board
						if(i==0){
							slowcontrolManager->ShowStatus(-1);
							break;
						}
						else{
            						char errstr[100];
   		  					sprintf(errstr,":::: WARNING: module %d returns nothing (evt: %d) ::::",i,storages[0]->GetNumberEvents()); 

						}
					}	
   	
					slowcontrolManager->AddBytes(adcs[i]->GetTransferedBytes());

					//Show Event if checked
					if(slowcontrolManager->GetGraphicsActive() && scopeManager->GetModule()==i){
						adcs[i]->Checkkeyboard(c);
						scopeManager->SetBuffer(adcs[i]->GetBuffer());
						scopeManager->SetChannelTresh(adcs[i]->GetTreshold());
						scopeManager->ShowEvent();
					}
			
					//Save the events or not :)
					storages[i]->FillContainer();	

					//status output, Slowcontrol etc
					if(i==0)
						slowcontrolManager->ShowStatus(1);

		 /*
			//Create new file if noE is bigger than noEF
			if(counter[i]==storages[i]->GetEventsPerFile() && storages[i]->GetNumberEvents()>slowcontrolManager->GetNumberEvents()){
				counter[i]=0;
				storages[i]->NewFile();
			}
		*/

		}
	}

    for(int i=0;i<slowcontrolManager->GetNbModules();i++){
		adcs[i]->Disable();
		adcs[i]->ClearMemory();
		storages[i]->SaveContainer();
   }
	slowcontrolManager->StopAquistion();


    return 0;
}


