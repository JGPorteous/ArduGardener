/*
Copyright (C) 2014 Justin Porteous <justin@porteous.co.za>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

Credits due to ManiacBug - http://maniacbug.wordpress.com/

*/

#include "Sensors.h"

//enum AvailableSensors { TemperatureAir, TemperatureSoil, MoistureSoil, Humidity };
int pin = -1;
int sensorValue = -1;
bool isDigital = true;
bool isReadOnly = true;


Sensors::Sensors()
{

}


Sensors::Sensors(int Pin, int SensorType, bool ReadOnly, bool Digital)
{

}

Sensors::~Sensors()
{
}

bool Sensors::IsDigital()
{
	return isDigital;
}

bool Sensors::IsReadOnly()
{
	return isReadOnly;
}

int Sensors::Value()
{
	return sensorValue;
}

int Sensors::Pin()
{
	return pin;
}

void Sensors::IsDigital(bool IsDigital)
{
	isDigital = IsDigital;
}

void Sensors::IsReadOnly(bool IsReadOnly)
{
	isReadOnly = IsReadOnly;
}

void Sensors::Pin(int Pin)
{
	pin = Pin;
}

void Sensors::Value(int Value)
{
	sensorValue = Value;
}
