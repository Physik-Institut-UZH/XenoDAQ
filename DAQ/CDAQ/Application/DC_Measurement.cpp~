/******************************************************************************


  @author  :  Julien Wulf
  @Comment :  DC meausrments over the ADC1724 standard firmware

 
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
#include <time.h>
#include "global.h"
#include "common.h"
#include "DCManager.h"

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
	SlowcontrolManager* slowcontrolManager = new SlowcontrolManager();
	slowcontrolManager->ProcessInput(argc, argv, envp);
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
		
	//DC-Manger
	std::vector <ADCManager*> adcs;
	std::vector <StorageManager*> storages;
	char baselineFile[50];
	int number=slowcontrolManager->GetNbModules();
	for(int i=0;i<slowcontrolManager->GetNbModules();i++){
		adcs.push_back(new DCManager());		
		adcs[i]->SetCrateHandle(vManager[i]->GetCrateHandle());
		adcs[i]->SetADCAddress(slowcontrolManager->GetAddress(i));
		adcs[i]->SetModuleNumber(i);
		adcs[i]->SetRegisterFile("RegisterConfig.ini");				//Should be the same for all modules
		sprintf(baselineFile, "Module_%i_DACBaseline.ini", i);
		std::string bp = Common::getdotdaqdir();
		bp.append("/Baseline/");
		bp.append(baselineFile);
		adcs[i]->SetBaselineFile(bp.c_str());
		adcs[i]->SetXMLFile(slowcontrolManager->GetXMLFile());

		if(adcs[i]->Init()==-1);
	}
	if(slowcontrolManager->GetADCInformation()) return 0;
	if(slowcontrolManager->GetBaselineCalculation()){
		for(int i=0;i<number;i++){
                        adcs[i]->EnableSoftware();
			adcs[i]->CalculateBaseLine();
		}
		return 0;
	}
	else{
		for(int i=0;i<number;i++){
				adcs[i]->ReadBaseLine();
		}
	}


	//Scope-Manager
	ScopeManager* scopeManager = new ScopeManager();
	scopeManager->SetThreshold();
	scopeManager->SetEventLength(adcs[0]->GetEventLength());				//Master Board
	scopeManager->SetXMLFile(slowcontrolManager->GetXMLFile());
	scopeManager->SetChannelNumber(slowcontrolManager->GetChannelNumber());
	scopeManager->SetModuleNumber(slowcontrolManager->GetNbModules());
	if(slowcontrolManager->GetGraphicsActive()){
		//ROOT Manager
		TApplication *theApp;
		theApp = new TApplication("App", &argc, argv);	
		if(scopeManager->Init()==-1)
			return 0;
	}





    	/*Stuff for the keyboard*/
    	char c;
    	int quit=0; 
    	c=0;
    

    	int countermax=0; 

    	slowcontrolManager->StartAquistion();
    	//adcManager->Enable();
	//adcManager->EnableChannel(0);
	//adcManager->CheckEventBuffer();		//Read Buffer before start aquisition


	double runtimeSlow=0;
	double runtime=0;
	double *baseline;
	int *threshold;
	double *rate;
	double *time;							//Storage of the current time
   	double *rms;
	//hardcoded for 3boards

	baseline = new double[24];
	rms = new double[24];
	threshold = new int[24];
	rate = new double[24];
	time = new double[24];

    	struct timeval m_begin;
    	struct timeval m_end;
		
	//Create a ROOTFile for Storage
	std::string output =  std::string(slowcontrolManager->GetPathName()) + "/" +  std::string(slowcontrolManager->GetFolderName()) + ".root";
	std::cout << "	Storage:	" << output << std::endl << std::endl;
	
	TFile* gROOTFile = new TFile(output.c_str(), "RECREATE");
	TTree *t1 = new TTree("t1","t1");
	t1->Branch("Time", time, TString::Format("time[%i]/D", 24));
	t1->Branch("Threshold", threshold, TString::Format("threshold[%i]/I",24));
	t1->Branch("Baseline", baseline, TString::Format("baseline[%i]/D",24));
	t1->Branch("RMS", rms, TString::Format("rms[%i]/D",24));
	t1->Branch("DC", rate, TString::Format("rate[%i]/D",24));

    	//Properties of the Peaks inside the trace
	for(int i=0;i<24;i++){
		rate[i]=0;
		threshold[i]=0;
		baseline[i]=0;
		rms[i]=0;
		time[i]=0;
	}

	while(slowcontrolManager->GetTotaltNumberEvents()!=countermax && quit!=1){
		// Check keyboard commands in every loop   
		printf(KCYN);
		std::cout << std::endl << "	Event: " << countermax << std::endl << std::endl;

		for(int i=0;i<slowcontrolManager->GetNbModules();i++){
			for(int k=0;k<6;k++){
				int counter=0;
				double rm=0;
				adcs[i]->Enable();
				adcs[i]->EnableChannel(k);
				//baseline[k]  =  adcManager->AverageBaseLine(k,rm);
				//rms[k] = rm;
				threshold[k+i*6] =  adcs[i]->CalculateThresholds(k,2000);
				if(slowcontrolManager->GetGraphicsActive()){	
					scopeManager->SetBuffer(adcs[i]->GetBuffer());
					scopeManager->SetChannelNumber(k);
					scopeManager->SetModulNumber(i);
					scopeManager->SetChannelTresh(threshold); 		
				} 

				if(adcs[i]->CheckEventBuffer()<-1) return 0;	
				gettimeofday(&m_begin, NULL);

				while(0<1){
					c = 0;
					if (kbhit()) c = getch();
					if (c == 'q' || c == 'Q') quit = 1;	

					//Check keys to change adc settings
					adcs[i]->Checkkeyboard(c);

					//Check if there have been an accepted trigger
					if(adcs[i]->CheckEventBuffer()<-1) return 0;	

					//Timing
			  		gettimeofday(&m_end, NULL);
					runtimeSlow =  (double) (m_end.tv_usec - m_begin.tv_usec)/ 1000000 + (double) (m_end.tv_sec - m_begin.tv_sec);
					if(runtimeSlow>2){
						rate[k+i*6] = counter/runtimeSlow;
						time[k+i*6]= slowcontrolManager->GetCurrentUnixTime();
						std::cout<< "Timing:	" << runtimeSlow << "	Counter:	" << counter << "	Channel:	" << k+i*6 << "	Baseline: " << baseline[k+i*6] << "	RMS: " << rms[k+i*6] << "	Threshold:	" << threshold[k+i*6]  << "	Rate: "  << rate[k+i*6] << " [Hz] "<<  std::endl;
						counter=0;
						break;
					}
					else{
						//Skipp events with 0-bytes
						if(adcs[i]->GetTransferedBytes()<=0){
							continue;
						}
						//Show Event if checked
						if(slowcontrolManager->GetGraphicsActive())
							scopeManager->ShowEvent();
						//status output, Slowcontrol etc
						counter++;
					}
				}
				adcs[i]->Disable();
			}
		}
		printf(RESET);
		t1->Fill();
		countermax++;
	}
	gROOTFile->cd();
	t1->Write();
	gROOTFile->Close();
	slowcontrolManager->StopAquistion();

}



