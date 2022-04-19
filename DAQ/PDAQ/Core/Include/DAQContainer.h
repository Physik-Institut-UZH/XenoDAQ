#ifndef DAQCONTAINER_H_
#define DAQCONTAINER_H_

#include <complex>


class DAQContainer{

	  public:
          	  	DAQContainer();
           	 	~DAQContainer(){}
			void SetGraphicMode(){graphic=true;}
			void SetCalibrationMode(){calibration=true;}
			bool GetGraphicMode(){return graphic;}
			bool GetCalibrationMode(){return calibration;}
			void SetOutputDir(const char* input){OutputDir=input;}
			std::string GetOutputDir(){return OutputDir;}
			void SetNumberOfEvents(const int number){NumberOfEvents=number;}
			int GetNumberOfEvens(){return NumberOfEvents;}
			void SetSaveType(const int type){savetype=type;}
			int GetSaveType(){return savetype;}
			void SetNumberPerFile(const int numberfile){NumberPerFile=numberfile;}
			int GetNumberPerFile(){return NumberPerFile;}
			void SetTriggerRate(const int rate){TriggerRate=rate;}
			int GetTriggerRate(){return TriggerRate;}
			void SetGraphicModeType(const int gmode){graphicmode=gmode;}
			int GetGraphicModeType(){return graphicmode;}
			void SetGraphicYHigh(const int yhigh){high=yhigh;}
			int GetGraphicYHigh(){return high;}
			void SetGraphicYLow(const int ylow){low=ylow;}
			int GetGraphicYLow(){return low;}
			void SetTriggerType(const int Trigger){trigger=Trigger;}
			int GetTriggerType(){return trigger;}
			void SetChannel0(const int Chn0){chn0=Chn0;}
			void SetChannel1(const int Chn1){chn1=Chn1;}
			void SetChannel2(const int Chn2){chn2=Chn2;}
			void SetChannel3(const int Chn3){chn3=Chn3;}
			int GetChannel0(){return chn0;}
			int GetChannel1(){return chn1;}
			int GetChannel2(){return chn2;}
			int GetChannel3(){return chn3;}

		
	  private:
			std::string OutputDir;
			int NumberOfEvents,savetype,NumberPerFile,TriggerRate,graphicmode,high,low,trigger,chn0,chn1,chn2,chn3;
			bool graphic,calibration;
			
};


#endif
