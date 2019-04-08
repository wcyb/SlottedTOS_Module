/*
 Name:		SlottedTOS_Module.h
 Created:	07/04/2019 2:08:42 AM
 Author:	Wojciech Cybowski (github.com/wcyb)
 Editor:	http://www.visualmicro.com
 License:	GPL v2
*/

#ifndef _SlottedTOS_Module_h
#define _SlottedTOS_Module_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class SlottedTOS final
{
public:
	/// <summary>
	/// Possible sensor states.
	/// </summary>
	enum class sensorState : uint8_t { enabled, disabled };

	/// <summary>
	/// Sets sensor state to enabled or disabled.
	/// </summary>
	/// <param name="stateToSet">state to set</param>
	/// <param name="externalHandler">Function that will be called when interrupt happens, it must call signalDetected(). This parameter can be omitted when disabling sensor.</param>
	void setSensorState(const sensorState& stateToSet, void(*externalHandler)() = nullptr);

	/// <summary>
	/// Returns sensor state.
	/// </summary>
	/// <returns>current sensor state</returns>
	const sensorState& getSensorState(void) { return m_state; }

	/// <summary>
	/// Enables or disables sensor data processing, but not disables interrupt handling.
	/// </summary>
	/// <param name="state"></param>
	void setSensorDataProcessing(const bool& state) { m_dataProcessingState = state; }

	/// <summary>
	/// Returns sensor data processing state. All events will be ignored when data processing is disabled.
	/// </summary>
	/// <returns></returns>
	const bool& getSensorDataProcessing(void) { return m_dataProcessingState; }

	/// <summary>
	/// Function that must be called by interrupt.
	/// </summary>
	void signalDetected(void) { risingEdgeDetected(); }

	/// <summary>
	/// Constructor for slotted transmissive optical sensor object.
	/// </summary>
	/// <param name="inputPin">Pin on which sensor is connected. Refer to documentation of attachInterrupt() to know what pin you can use.</param>
	/// <param name="externalInterruptStarter">function that will call signalDetected() from this class</param>
	/// <param name="eventCallback">function that will be called when signal from sensor will be received</param>
	SlottedTOS(const uint8_t& inputPin, void(*externalInterruptStarter)(), void(*eventCallback)())
		: m_inputPin(inputPin), externalStarter(externalInterruptStarter), eventCallbackFunction(eventCallback)
	{
		pinMode(m_inputPin, INPUT);
		setSensorState(sensorState::enabled, externalStarter);
	};

	SlottedTOS(const SlottedTOS&) = delete;
	SlottedTOS& operator=(const SlottedTOS&) = delete;

	/// <summary>
	/// Destructor for slotted transmissive optical sensor object. It will deattach interrupt handler.
	/// </summary>
	~SlottedTOS() { setSensorState(sensorState::disabled); }

private:
	/// <summary>
	/// Processes received sensor signal.
	/// </summary>
	void risingEdgeDetected(void);

private:
	/// <summary>
	/// Current sensor state.
	/// </summary>
	sensorState m_state;

	/// <summary>
	/// Current sensor data processing state.
	/// </summary>
	bool m_dataProcessingState = true;

	/// <summary>
	/// Sensor signal input pin.
	/// </summary>
	const uint8_t m_inputPin;

	/// <summary>
	/// Function called when signal data processing ends.
	/// </summary>
	void(*eventCallbackFunction)();
	/// <summary>
	/// Interrupt handler function.
	/// </summary>
	void(*externalStarter)();
};

#endif

