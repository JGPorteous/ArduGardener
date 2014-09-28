#include <SPI.h>
#include <RF24_config.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>
#include "Node.h"

//Node declaration
Node me;

enum SensorTypes { SENSOR_AirTemprature = 1, SENSOR_SoilTemperature, SENSOR_DirectTemperature, SENSOR_Humidity };
enum NodeTypes { NODE_Server = 0, NODE_1, NODE_2, NODE_3, NODE_4, NODE_5, NODE_6};
enum PinTypes { AnalogPin0 = A0, AnalogPin1 = A1, AnalogPin2 = A2, AnalogPin3 = A3, AnalogPin4 = A4, AnalogPin5 = A5, AnalogPin6 = A6, AnalogPin7 = A7,
	DigitalPin1 = 1, DigitalPin2, DigitalPin3, DigitalPin4, DigitalPin5, DigitalPin6, DigitalPin7, DigitalPin8, DigitalPin9, DigitalPin10, DigitalPin11, DigitalPin12, DigitalPin13, DigitalPin14 };

//Define Node Type before uploading to device
const int thisNode = NODE_Server;


void setup()
{
	Serial.begin(57600);
	me = Node(thisNode);

	//Setup your sensors here
	me.AddSensor(2, SENSOR_Humidity, true, true);
	me.AddSensor(3, SENSOR_AirTemprature, true, true);


}

void loop()
{
	//There are two types of nodes, servers which collect data
	// and transmitters which send data (and receive instructions)
	if (thisNode == NODE_Server)
		ServerLoop();
	else
		TransmitterLoop();
}

void ServerLoop()
{}

void TransmitterLoop()
{}