#pragma once

//#include "Sensors.h"
//#include "SPI.h"
//#include "nRF24L01.h"
//#include "RF24.h"
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

	int NodeNumber();
	bool IsServer();
	int SensorCount();
	RF24 Radio();
	int FreeRam();

private:
 

};

