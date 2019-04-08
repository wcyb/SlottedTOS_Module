/*
 Name:		SlottedTOS_Module_Demo.ino
 Created:	07/04/2019 2:09:53 AM
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/

#include "SlottedTOS_Module.h"

SlottedTOS* sensor = nullptr;
bool changeDetected = false;

/// <summary>
/// Called when signal from sensor was received.
/// </summary>
void sensorEvent(void);
/// <summary>
/// Called when sensor signal data is incomming (interrupt starts) !do not change!
/// </summary>
void sensorInterrupt(void);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	sensor = new SlottedTOS(static_cast<uint8_t>(3), sensorInterrupt, sensorEvent);
	Serial.println("...Slotted TOS monitoring started...");
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (changeDetected)
	{
		Serial.println("Signal received");
		changeDetected = false;
		sensor->setSensorDataProcessing(true);//remember to enable sensor data processing after you end processing this event
	}
}

void sensorEvent()
{
	//this function starts when signal from sensor is received
	//---remember that below code must execute as fast as possible because it is called inside interrupt---
	changeDetected = true;
}

void sensorInterrupt()
{
	sensor->signalDetected();
}
