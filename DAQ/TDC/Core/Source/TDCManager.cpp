#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>
#include "TDCManager.h"
#include "IOManager.h"
#include "global.h"
#include <sys/time.h>
#include <unistd.h>
#include "keyb.h"
#include <bitset>

TDCManager::TDCManager()
{
	m_TDCAdr=m_CrateHandle=0;
}

TDCManager::~TDCManager()
{
}

int TDCManager::Init()
{		


	return 0;
}

//Set Address of the Scaler
void TDCManager::SetDiscAddress(string address){
	m_TDCAdr=StringToHex(address);
	return;
}


//Convert String to Hex
u_int32_t TDCManager::StringToHex(const string &str)
{
   stringstream ss(str);
   u_int32_t result;
   return ss >> std::hex >> result ? result : 0;
}


int TDCManager::test()
{
 		  // Get system informations
    
       		//UINT16 firmware_rev;
      		//UINT8  piggy_back_type;
        	//UINT16 serial_number;

		//Firmware
		int data;
		short firmware;
		if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x1000, &firmware,cvA32_U_DATA,cvD16)!=cvSuccess){
			printf(KRED);
			printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
			printf(RESET);
			return -1;
		}	
		std::cout<<std::hex << (firmware)<<std::endl;
		
		//Set  Thresholds

		data=100;
		for(int i=0;i<1;i++){
			if(CAENVME_WriteCycle(m_CrateHandle,m_TDCAdr+0x1080+i*4, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
				printf(KRED);
				printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
				printf(RESET);
				return -1;
			}
		}	

		for(int i=0;i<16;i++){
			if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x1080+i*4, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
				printf(KRED);
				printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
				printf(RESET);
				return -1;
			}
			std::cout<<  "Threshold Channel: " << i << " " <<std::bitset<8>(data)<<std::endl;
		}	


		//Bit Set 1 Register
		if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x1006, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
			printf(KRED);
			printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
			printf(RESET);
			return -1;
		}
		 std::cout<<  "Bit Set 1 Register: " <<std::bitset<8>(data)<<std::endl;
		
		//Status Register 1 
		if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x100E, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
			printf(KRED);
			printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
			printf(RESET);
			return -1;
		}	

		 std::cout<< "Status Register1: " <<std::bitset<8>(data)<<std::endl;		

		//Control Register 1 
		if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x1010, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
			printf(KRED);
			printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
			printf(RESET);
			return -1;
		}		
		 std::cout<< "Control Register:"<<std::bitset<7>(data)<<std::endl;

		//Status Register 2 
		if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x1022, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
			printf(KRED);
			printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
			printf(RESET);
			return -1;
		}		
		 std::cout<< "Status Register2: " <<std::bitset<8>(data)<<std::endl;

		//Event Counter Low Register 
		if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x1024, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
			printf(KRED);
			printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
			printf(RESET);
			return -1;
		}		
		 std::cout<< "Event Counter Low Register: " <<std::bitset<8>(data)<<std::endl;

	//Event Counter High Register 
		if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x1026, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
			printf(KRED);
			printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
			printf(RESET);
			return -1;
		}		
		 std::cout<< "Event Counter High Register: " <<std::bitset<8>(data)<<std::endl;
		

	//Bit Set 2 Register 
		if(CAENVME_ReadCycle(m_CrateHandle,m_TDCAdr+0x1032, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
			printf(KRED);
			printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
			printf(RESET);
			return -1;
		}	
			 std::cout<< "Bit Set 2 Register: " <<std::bitset<16>(data)<<std::endl;


	int m_MemorySize, m_BufferSize;
	u_int32_t m_ExpectedEvSize;					//Complete Eventsize

      // Expected Event Size in Words (32Bit including Header)
	m_BufferSize =  8*1024*1024;;

	// allocate memory for buffer
	if ( (buffer = (u_int32_t*)malloc(m_BufferSize)) == NULL) {  
			printf(KRED);
			printf(":::: ERROR: Can't allocate memory buffer of %d kB ::::", m_BufferSize/1024);
			printf(RESET);
			return -1;
	 }

//	data=pow(2,12);
//	//data=data+pow(2,5);
///	if(CAENVME_WriteCycle(m_CrateHandle,m_TDCAdr+0x1032, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
///				printf(KRED);
///				printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
///				printf(RESET);
///				return -1;
//			}
	data=0x1E;
	if(CAENVME_WriteCycle(m_CrateHandle,m_TDCAdr+0x1060, &data,cvA32_U_DATA,cvD16)!=cvSuccess){
				printf(KRED);
				printf(":::: VME read error!!! (ScalerManager::ReadMultipleCycles()) ::::\n");
				printf(RESET);
				return -1;
	}



	//while(1!=0){
		// read the event
       	int nb, ret;  
	blt_bytes=0;
	 do { 
		ret = CAENVME_FIFOBLTReadCycle(m_CrateHandle, m_TDCAdr, ((unsigned char*)buffer)+blt_bytes, m_BufferSize, cvA32_U_BLT, cvD32, &nb);
	   	 if ((ret != cvSuccess) && (ret != cvBusError)) {
			std::cout << "Block read error" << std::endl;   
			printf("%d bytes read\n",nb);
				return -1;  
	    	}
		blt_bytes += nb;
	} while (1); 
	std::cout << "Bytes Transfered:	" << blt_bytes << std::endl;


//}
   	return  blt_bytes;
}




