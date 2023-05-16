# XenoDAQ
First DAQ used on Xenoscope. Code based on DAQ wrote by Julien Wulf. Includes SingleDAQ and MultiDAQ, with or without ZLE.


# Installation

The working version of the DAQ is found in the CDAQ directory. Follow these steps to compile the software:

1) Copy the git repository on your machine
2) Go to /DAQ/CDAQ/ and type the following lines:

        mkdir build

        cd build

        cmake ..

        make

The software is now compiled and ready for use

# Acquisition

Two compiled scripts can be used to acquire data: SingleDAQ and MultiDAQ. SingleDAQ is a more general version of MultiDAQ which works with only one Analog-to-Digital Converter (ADC). To launch an acquisition, use the following command:

./SingleDAQ -x "file.xml" -options

The only mendatory file which must be provided is the XML file. Templates can be found in the "master_xml_files" directory. The XML file is a configuration file which is read at the begining of the acquisition to provide settings to the ADC. Replace "file.xml" with the actual file name. Here is a list of optional arguments:

-x "file.xml" : Provides the required field values to the ADC before initilization.

-f "file_name" : Provides a file name to the acquired data. When no file name is specified, the file name is composed of the date & time of the acquisition launch.

-b : Launches the baseline calculation script. This enables the ADC to calibrate the baseline level, and should in principle be used before any "new" acquisition

-g p : Enables the oscilloscope mode for channel "p"

-o : Display the help menu for the oscilloscope mode.

-i : Display hardware information.

-v : Enable Verbose mode.

-h : Display the help menu.


The oscilloscope mode enables the graphical display of the waveforms. The acquisition rate is much slower with this mode, and should not be used during normal acquisition. In oscilloscope mode, the following commands can be used by pressing the keys on the keyboard when the terminal is selected:

"w" : Lower threshold by 10 ADC units

"e" : Raise threshold by 10 ADC units

"r" : Lower threshold by 1 ADC units

"t" : Raise threshold by 1 ADC units

"+" : Change channel number +1

"-" : Change channel number -1

"1" : Set y-axis scale to "full"

"2" : Set y-axis scale to "fixed"

"3" : Set y-axis scale to "adjusting"

------------------------------------------------------------

Finally, here are example command lines. To acquire multiple ADCs at a time, replace "./SingleDAQ" with "./MultiDAQ".

Launch baseline calculation

    ./SingleDAQ -x "file.xml" -f "file_name" -b

Launch oscilloscope mode in channel 0

    ./SingleDAQ -x "file.xml" -f "file_name" -g0   

Launch normal acquisition

    ./SingleDAQ -x "file.xml" -f "file_name"       


