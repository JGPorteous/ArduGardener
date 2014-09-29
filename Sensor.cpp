/*
Copyright (C) 2014 Justin Porteous <justin@porteous.co.za>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

Credits due to ManiacBug - http://maniacbug.wordpress.com/

*/

#include "Sensor.h"
#include "Arduino.h"

int pin = -1;
int sensorValue = -1;
bool isDigital = true;
bool isReadOnly = true;
int parentNode = -1;

Sensor::Sensor()
{

}


Sensor::Sensor(int Pin, int SensorType, int ParentNode, bool ReadOnly, bool Digital)
{

	pin = Pin;
	isDigital = Digital;
	isReadOnly = ReadOnly;
	parentNode = ParentNode;
	sensorValue = 0;
	SetupSensor();
}

void Sensor::SetupSensor()
{
	if (isReadOnly)
		pinMode(pin, INPUT);
	else
		pinMode(pin, OUTPUT);

}

Sensor::~Sensor()
{
}

bool Sensor::IsDigital()
{
	return isDigital;
}

bool Sensor::IsReadOnly()
{
	return isReadOnly;
}

int Sensor::Value()
{
	return sensorValue;
}

int Sensor::Pin()
{
	return pin;
}

void Sensor::IsDigital(bool IsDigital)
{
	isDigital = IsDigital;
}

void Sensor::IsReadOnly(bool IsReadOnly)
{
	isReadOnly = IsReadOnly;
}

void Sensor::Pin(int Pin)
{
	pin = Pin;
}

void Sensor::Value(int Value)
{
	sensorValue = Value;
}

int Sensor::ReadSensor()
{
	if (isDigital)
		sensorValue = digitalRead(pin);
	else
		sensorValue = analogRead(pin);

	return sensorValue;
}

int Sensor::ParentNode()
{
	return parentNode;
}