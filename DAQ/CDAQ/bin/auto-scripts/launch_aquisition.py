#!/bin/env python

import serial,sys,glob,select,time		#imports in order to run the core program 
import subprocess,os				#imports in order to send variables to the bash script	
			
voltages = [29.00,30.00,31.00,32.00,33.00,34.00,35.00]		#Input voltage values before every run
temperature = "-190K"							#Input the temperature value before every run

#loop variables 
i = 0
i1 = 0 
i2 = 0

#Input voltage tracker (Records which index within the voltages list that the program is running)
index_volt = 0

for x in voltages: #Loop over all voltages


	dev  = "/dev/ttyACM0"  #Path of usb port
	scan = glob.glob(dev)  #Returns a list of pathname of dev 
	serport = scan[0]				#extracts the required pathname from the list
	ser=serial.Serial(serport,9600, timeout=1)	#Opens the port 	
	ser.flush()					#Flushes file objects 
	print("\n\n================================================")
	print("connected to: " + ser.portstr)		#Specifies connection to the device by name 
	print("================================================")
	#======================================================

	#Turns of the first channel of power supply by sending the `out1 0` command; prints out the status of the command
	print("\nTurning off the power supply.")
	print("Sending command:")
	time.sleep(0.1)
	ser.write("out1 0\r")
	time.sleep(0.5)
	rcv = ser.readline()
	print("{}".format(rcv))
	print("Status: ")
	rcv = ser.readline()
	print("{}".format(rcv))	
	ser.flush()
	time.sleep(1)

	#Reads and prints out the voltage output of the first channel of the power supply by sending the 'mvo1' command and reads the value.
	print("\nVoltage reading: ")
	time.sleep(0.1)
	ser.flush()
	ser.write("mvo1\r")
	time.sleep(3)
	for i in range(3):
		ser.flush		
		rcv = ser.readline()
	print("{}".format(rcv))
	ser.flush()
	time.sleep(1)

	#Changes voltage of the first channel to the designated value within the loop by sending the 'svo1 x' command; prints out the status of the command
	print("\nChanging voltage to: {}V.\nStatus: ".format(x))
	time.sleep(5)
	ser.flush()
	ser.write("svo1 {}\r".format(x))
	time.sleep(10)
	for i1 in range(3):
		ser.flush()
		rcv = ser.readline()
	print("{}".format(rcv))
	ser.flush()
	time.sleep(1)
	
	#Turns on the first channel of the power supply by sending the 'out1 1' command; prints out the status of the command.
	print("\nTurning on the power supply.\nStatus: ")
	time.sleep(0.1)
	ser.flush()
	ser.write("out1 1\r")
	time.sleep(0.5)
	for i2 in range(3):
		ser.flush()
		rcv = ser.readline()		
	print("{}".format(rcv))
	ser.flush()
	time.sleep(0.25)

	#Reads the voltage of the first channel of the power supply by sending the 'mvo1' command and prints the value.
	print("\nVoltage reading: ")
	time.sleep(5)
	ser.flush()
	ser.write("mvo1\r")
	time.sleep(10)
	for i2 in range(3):
		ser.flush()
		rcv = ser.readline()		
	print("{}".format(rcv))
	time.sleep(0.25)

	#Closes the port connection
	ser.close()	

	#Prints out the final voltage 
	print("\n\nEnd of voltage {} V".format(x))

	time.sleep(2)
	
	#Converts the integer voltage values into string values in order to be utilized while naming save files 
	print(x)
	voltstr=str(float(voltages[index_volt]))
	voltstrnamefile=voltstr.replace('.','_')
	voltstrnamefile=voltstrnamefile+"V"+temperature
	print(voltstrnamefile)
		

	os.system("~/DAQ_zero/DAQ/CDAQ/bin/FBK-auto.sh  %s" % (voltstrnamefile))	#os.system("~/path/bash.sh %s/d/.f" %variable) 
										 		#takes a variable from the python script of any type (string(s)/integer(d)/float(f)
										 		#and inserts this value into the bash file which was specified
											#Also possible to use with multiple variables: os.system("~/path/bash.sh %s %d %.f" %(var1,var2,var3))
											#If the above function does not work try: os.system("./path/bash.sh %s/d/.f" %variable)
	
	#increments the voltage list index keeper 
	index_volt = index_volt+1

dev  = "/dev/ttyACM0"  #Path of usb port
scan = glob.glob(dev)  #Returns a list of pathname of dev 
serport = scan[0]				#extracts the required pathname from the list
ser=serial.Serial(serport,9600, timeout=1)	#Opens the port 	
ser.flush()	


#Turns of the first channel of power supply by sending the `out1 0` command; prints out the status of the command
print("\nTurning off the power supply.")
print("Sending command:")
time.sleep(0.1)
ser.write("out1 0\r")
time.sleep(0.5)
rcv = ser.readline()
print("{}".format(rcv))
print("Status: ")
rcv = ser.readline()
print("{}".format(rcv))	
ser.flush()
time.sleep(1)
#Closes the port connection
ser.close()
time.sleep(2)
