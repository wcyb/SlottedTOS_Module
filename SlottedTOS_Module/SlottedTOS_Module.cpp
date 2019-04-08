/*
 Name:		SlottedTOS_Module.cpp
 Created:	07/04/2019 2:08:42 AM
 Author:	Wojciech Cybowski (github.com/wcyb)
 Editor:	http://www.visualmicro.com
 License:	GPL v2
*/

#include "SlottedTOS_Module.h"

void SlottedTOS::setSensorState(const sensorState& stateToSet, void(*externalHandler)() = nullptr)
{
	if (stateToSet == sensorState::disabled) { detachInterrupt(digitalPinToInterrupt(m_inputPin)); m_state = stateToSet; }
	else if (externalHandler != nullptr) { attachInterrupt(digitalPinToInterrupt(m_inputPin), externalHandler, RISING); m_state = stateToSet; }
}

void SlottedTOS::risingEdgeDetected(void)
{
	if (!m_dataProcessingState) return;
	if (eventCallbackFunction)
	{
		setSensorDataProcessing(false);
		eventCallbackFunction();
	}
}
