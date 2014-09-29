/*
Copyright (C) 2014 Justin Porteous <justin@porteous.co.za>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

Credits due to ManiacBug - http://maniacbug.wordpress.com/

*/

#pragma once
class Sensors
{
public:
	Sensors();
	Sensors(int Pin, int SensorType, bool ReadOnly = true, bool Digital = true);
	~Sensors();
	bool IsDigital();
	bool IsReadOnly();
	int Value();
	int Pin();
	void IsDigital(bool IsDigital);
	void IsReadOnly(bool IsReadOnly);
	void Pin(int Pin);
	void Value(int Value);


private:
	int pin;
	int sensorValue;
	bool isDigital;
	bool isReadOnly;
};

