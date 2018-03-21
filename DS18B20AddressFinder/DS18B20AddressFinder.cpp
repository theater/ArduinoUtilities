// Do not remove the include below

#include "DS18B20AddressFinder.h"

#include <HardwareSerial.h>
#include <OneWire.h>
#include <WString.h>

#define ONE_WIRE_PIN_01 5
#define BAUD_RATE 115200

//DS18B20
OneWire oneWire(ONE_WIRE_PIN_01);
DallasTemperature owSensors(&oneWire);

void log(String severity, String data) {
	Serial.println(severity +": " + data);
}

void logInfo(String data) {
	log("INFO", data);
}

void printDeviceAddress(int index, DallasTemperature* owSensors) {
	DeviceAddress deviceAddress;
	owSensors->getAddress(deviceAddress, index);
	Serial.print("INFO: Device " + String(index) + ": ");
	for (int j = 0; j < 8; j++) {
		Serial.print("0x");
		Serial.print(deviceAddress[j], HEX);
		Serial.print(j == 7 ? ".\n" : ", ");
	}
}

void printOneWireAddressesAndTemperatures(DallasTemperature* owSensors) {
	int count = owSensors->getDeviceCount();
	logInfo("Found " + String(count) + (count == 1 ? " device" : " devices\n"));
	owSensors->requestTemperatures();
	delay(200);
	for (int index = 0; index < count; index++) {
		printDeviceAddress(index, owSensors);
		float tempSensor = owSensors->getTempCByIndex(index);
		logInfo("DS18B20 Sensor " + String(index) + " temperature: " + String(tempSensor) + "C\n");
	}
}


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(BAUD_RATE);
		logInfo("Beginning setup()...");

		logInfo("Waiting 2000 ms...");
		delay(2000);

		logInfo("Update sensors...");
		owSensors.begin();
		delay(100);
		printOneWireAddressesAndTemperatures(&owSensors);
}

// The loop function is called in an endless loop
void loop()
{
	delay(10000);
	printOneWireAddressesAndTemperatures(&owSensors);
}
