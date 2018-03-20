// Do not remove the include below

#include "DS18B20AddressFinder.h"

#include <DallasTemperature.h>
#include <HardwareSerial.h>
#include <OneWire.h>
#include <WString.h>
#include <Util.h>

#define ONE_WIRE_PIN_01 5
#define BAUD_RATE 115200

//DS18B20
OneWire oneWire(ONE_WIRE_PIN_01);
DallasTemperature owSensors(&oneWire);

void local::printOneWireAddresses(DallasTemperature* owSensors) {
	int count = owSensors->getDeviceCount();
	logDebug("Found " + String(count) + (count == 1 ? " device" : " devices"));
	for (int i = 0; i < count; i++) {
		DeviceAddress deviceAddress;
		owSensors->getAddress(deviceAddress, i);
			Serial.print("Device " + String(i) + ": ");
		for (int j = 0; j < 8; j++) {
			Serial.print("0x");
			Serial.print(deviceAddress[j], HEX);
			Serial.print(j==7 ? ".\n" : ", ");
		}
		float tempSensor = owSensors->getTempCByIndex(i);
		logDebug("DS18B20 Sensor " + String(i) + " temperature: " + String(tempSensor) + "C");
	}
}


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(BAUD_RATE);
		logDebug("Beginning setup()...");

		logDebug("Waiting 2000 ms...");
		delay(2000);

		logDebug("Update sensors...");
		owSensors.begin();
		local::printOneWireAddresses(&owSensors);
}

// The loop function is called in an endless loop
void loop()
{
	delay(10000);
	local::printOneWireAddresses(&owSensors);
}
