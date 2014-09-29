/*
Copyright (C) 2014 Justin Porteous <justin@porteous.co.za>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

Credits due to ManiacBug - http://maniacbug.wordpress.com/

*/
#pragma once

#include <SPI.h>
#include "RF24\nRF24L01.h"
#include "RF24\RF24.h"

class Node
{
public:
	Node();
	Node(int NodeNumber);
	~Node();
	void NodeNumber(int NodeNumber);
	void IsServer(bool IsServer);
	void SensorCount(int SensorCount);
	void AddSensor(int Pin, int SensorType, bool isDigital, bool isReadOnly);
	void SetupRadio();
	void SetupServerMode();
	void LastSendTime(long newLastSendTime);
	void DataInterval(long newDataInterval);
	void HeartBeatInterval(long newHeartBeatInterval);
	void UpdateHeartBeat(bool newHeartBeatResult);
	bool SendHeartBeat();
	int  ReadSensor(int SensorToRead);
	void ReadAllSensors();
	bool SendData();
	bool ReadRadio();
	bool TimeToSendHearBeat();
	bool TimeToSendData();
	void SetStatusLED(int statusColour);
	long LastSendTime();
	long DataInterval();
	long HeartBeatInterval();

	int NodeNumber();
	bool IsServer();
	int SensorCount();
	RF24 Radio();
	int FreeRam();

	enum NodeTypes { NODE_Server = 0, NODE_1, NODE_2, NODE_3, NODE_4, NODE_5, NODE_6 };
	enum StatusColour { STATUS_COLOR_RED = 0, STATUS_COLOR_GREEN = 1, STATUS_COLOR_YELLOW = 2 };

private:
 

};

