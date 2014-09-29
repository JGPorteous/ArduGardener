/*
Copyright (C) 2014 Justin Porteous <justin@porteous.co.za>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

Credits due to ManiacBug - http://maniacbug.wordpress.com/

*/

#pragma once
#include "Arduino.h"

class Sensor
{
public:
	Sensor();
	Sensor(int Pin, int SensorType, int ParentNode, bool ReadOnly = true, bool Digital = true);
	~Sensor();
	bool IsDigital();
	bool IsReadOnly();
	int Value();
	int Pin();
	void IsDigital(bool IsDigital);
	void IsReadOnly(bool IsReadOnly);
	void Pin(int Pin);
	void Value(int Value);
	void SetupSensor();
	int ParentNode();

	int ReadSensor(); 
	void WriteSensor(int value);

	enum SensorTypes { SENSOR_HeartBeat = 0, SENSOR_AirTemprature = 1, SENSOR_SoilTemperature, SENSOR_DirectTemperature, SENSOR_Humidity, SENSOR_Other };
	enum PinTypes {
		AnalogPin0 = A0, AnalogPin1 = A1, AnalogPin2 = A2, AnalogPin3 = A3, AnalogPin4 = A4, AnalogPin5 = A5, AnalogPin6 = A6, AnalogPin7 = A7,
		DigitalPin1 = 1, DigitalPin2, DigitalPin3, DigitalPin4, DigitalPin5, DigitalPin6, DigitalPin7, DigitalPin8, DigitalPin9, DigitalPin10, DigitalPin11, DigitalPin12, DigitalPin13, DigitalPin14
	};


private:
	int pin;
	int sensorValue;
	bool isDigital;
	bool isReadOnly;
	int parentNode;
};

