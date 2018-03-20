// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _DS18B20AddressFinder_H_
#define _DS18B20AddressFinder_H_
#include <DallasTemperature.h>

//add your includes for the project DS18B20AddressFinder here


//end of add your includes here


//add your function definitions for the project DS18B20AddressFinder here
namespace local {
	void printOneWireAddresses(DallasTemperature* owSensors);
}


//Do not add code below this line
#endif /* _DS18B20AddressFinder_H_ */
