/*
Copyright (C) 2014 Justin Porteous <justin@porteous.co.za>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

Credits due to ManiacBug - http://maniacbug.wordpress.com/

Configuration before uploading:
	1. Set variable thisNode, option of NodeTypes
	2. Setup sensors

*/

#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
#include "printf.h"
#include "Node.h"
#include "Sensor.h"
//#include "stdio.h"
//Node declaration
Node me;



//Define Node Type before uploading to device
const int thisNode = Node::NODE_2;


void setup()
{
	//Setup Serial interface
	Serial.begin(57600);
	printf_begin();
	printf("printf test................................................");


	//This will configure the node
	Serial.print("thisNode: ");
	Serial.println(thisNode);
	me = Node(thisNode);

	Serial.println("Setting up sensors");
	//Setup your sensors here 
	me.AddSensor(2, Sensor::SENSOR_Humidity, true, true);
	me.AddSensor(3, Sensor::SENSOR_AirTemprature, true, true);

	Serial.println("done setting up sensors");

	if (me.IsServer())
		Serial.println("Node setup as a server!");
	else
		Serial.println("Node setup as transmitter!");
}

void loop()
{
	//There are two types of nodes, servers which collect data
	// and transmitters which send data (and optionally receive instructions)
	if (thisNode == Node::NODE_Server)
		ServerLoop();
	else
		TransmitterLoop();
}

void ServerLoop()
{
	me.ReadRadio();

}

void TransmitterLoop()
{
	if (me.TimeToSendData())
		me.SendData(); 
	
	if (me.TimeToSendHearBeat())
		me.SendHeartBeat();

	

}