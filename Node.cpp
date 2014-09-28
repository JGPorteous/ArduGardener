#include "Arduino.h"
#include "Node.h"
#include "Sensors.h"
#include <SPI\SPI.h>
#include "RF24\nRF24L01.h"
#include "RF24\RF24.h"

//#include "printf.h"
 


int nodeNumber = 0;
Sensors sensors[11];  //Max free based on pins after Radio is added (Arduino Pro Mini)
 
bool isServer = true;
int sensorCount = 0;

RF24 radio(9, 10);


Node::Node()
{
	
}


Node::~Node()
{
}

Node::Node(int NodeNumber)
{
	nodeNumber = NodeNumber;
	SetupRadio();
}

void Node::AddSensor(int Pin, int SensorType, bool isReadOnly, bool isDigital)
{
	sensors[sensorCount] = Sensors(Pin, SensorType, isReadOnly, isDigital);
}

void Node::NodeNumber(int NodeNumber)
{
	nodeNumber = NodeNumber;
	isServer = (nodeNumber == 0);
}

void Node::IsServer(bool IsServer)
{
	isServer = IsServer;
}

void Node::SensorCount(int SensorCount)
{
	sensorCount = SensorCount;
}

int Node::NodeNumber()
{
	return nodeNumber;
}

bool Node::IsServer()
{
	return isServer;
}

void Node::SetupRadio()
{

}

int Node::SensorCount()
{
	return sensorCount;
}
//
//RF24 Node::Radio()
//{
//	return radio;
//}


int Node::FreeRam()
{
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}