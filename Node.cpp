/*
Copyright (C) 2014 Justin Porteous <justin@porteous.co.za>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

Credits due to ManiacBug - http://maniacbug.wordpress.com/

*/

#include "Arduino.h"
#include "Node.h"
#include "Sensor.h"
#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
//#include "printf.h"
//#include "stdio.h"
//#include "printf.h"

RF24 radio(9, 10);
int nodeNumber = 0;
bool isServer = true;
bool heartBeatStatus = false;
int sensorCount = 0;
long lastSendTimeData = 0;
long lastSendTimeHB = 0;
long sendDataInterval = 15000; // Every 15 Minutes 1800000 = 30 minutes
long sendHeartBeatInterval = 5000; //Every Minutes

int pinStatusGreen = A0; 
int pinStatusRed = A1;


Sensor sensors[11];  //Max free based on pins after Radio is added (Arduino Pro Mini)
	// I know there is a better, more memory efficitent way to hand this
	// but this will have to be update at a later stage, maybe using vectors or dynamic arrays

const uint64_t pipes[7] = { 0xF0F0F0F000LL, 0xF0F0F0F0A1LL, 0xF0F0F0F0B2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0D4LL, 0xF0F0F0F0E5LL, 0xF0F0F0F0F62LL };

 


Node::Node()
{

}

Node::~Node()
{

}

Node::Node(int NodeNumber)
{
	Serial.println("Inside class Node(int NodeNumber)");
	nodeNumber = NodeNumber;

	isServer = (nodeNumber == NODE_Server);
	//First sensor is used for heartbeat   SENSOR_HeartBeat = 0
	sensors[Sensor::SENSOR_HeartBeat] = Sensor(0, 0, true, true);
	sensors[Sensor::SENSOR_HeartBeat].Value(13);
	
	pinMode(pinStatusGreen, OUTPUT);
	pinMode(pinStatusRed, OUTPUT);
	SetupRadio();
}


 
long Node::DataInterval()
{
	return sendDataInterval;
}

void Node::DataInterval(long newDataInterval)
{
	sendDataInterval = newDataInterval;
}

long Node::HeartBeatInterval()
{
	return sendHeartBeatInterval;
}

void Node::HeartBeatInterval(long newHeartBeatInterval)
{
	sendHeartBeatInterval = newHeartBeatInterval;
}

void Node::AddSensor(int Pin, int SensorType, bool isReadOnly, bool isDigital)
{
	sensorCount++;
	sensors[sensorCount] = Sensor(Pin, SensorType, isReadOnly, isDigital);
}

void Node::NodeNumber(int NodeNumber)
{
	nodeNumber = NodeNumber;
	isServer = (nodeNumber == NODE_Server);
}

void Node::IsServer(bool IsServer)
{
	isServer = (nodeNumber == NODE_Server);
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

	Serial.println("Inside SetupRadio()");
	radio.begin();
	radio.setRetries(15, 15);
	radio.setPayloadSize(8);
	radio.setAutoAck(true);
	radio.setChannel(56);
	
	if (isServer)  //if is server, open all pipes and Listen
	{
		for (int i = 0; i < 6; i++)
			radio.openReadingPipe(i, pipes[i]);
		//radio.startListening();
	}
	else //Transmitter
	{
		radio.openWritingPipe(pipes[nodeNumber]); 
		radio.openReadingPipe(nodeNumber, pipes[nodeNumber]);
		
	}

	Serial.print("Radio.available(): ");
	Serial.println(radio.available());

	radio.startListening();
	//Display radio info
	radio.printDetails();
 
}

int Node::SensorCount()
{
	return sensorCount;
}

RF24 Node::Radio()
{
	return radio;
}


int Node::FreeRam()
{
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void Node::SetupServerMode()
{

}

bool Node::TimeToSendData()
{
	bool isTime = (millis() >= (lastSendTimeData + sendDataInterval));
	return isTime;
}

bool Node::TimeToSendHearBeat()
{
	bool isTime = (millis() >= (lastSendTimeHB + sendHeartBeatInterval));
	return isTime;
}

bool Node::SendHeartBeat()
{
	//Serial.println("SENDING HEART BEAT ---------------------");

	bool resultHB = false;
	radio.stopListening();

	radio.openWritingPipe(pipes[nodeNumber]);
	resultHB = radio.write(&sensors[Sensor::SENSOR_HeartBeat], sizeof(Sensor));
	
	//if (resultHB)
	//	Serial.println("HeartBeat sent...");
	//else
	//	Serial.println("HeartBeat failed.\n\r");

	radio.startListening();
	
	lastSendTimeHB = millis();
	UpdateHeartBeat(resultHB);
	return resultHB;
}

void Node::UpdateHeartBeat(bool newHeartBeatResult)
{
	if (heartBeatStatus != newHeartBeatResult)
	{
		heartBeatStatus = newHeartBeatResult;
		if (heartBeatStatus)
		{
			SetStatusLED(STATUS_COLOR_GREEN);
			printf("Heartbeat Status : Good\r\n");
		}
		else
		{
			SetStatusLED(STATUS_COLOR_RED);
			printf("Hearbeat Status : Failed\r\n");
		}
	}

}

void Node::SetStatusLED(int statusColour)
{
	//Turn all off
	pinMode(pinStatusGreen, INPUT);
	pinMode(pinStatusRed, INPUT);

	digitalWrite(pinStatusGreen, LOW);

	digitalWrite(pinStatusRed, LOW);
	Serial.print("statusColour");
	Serial.println(statusColour);

	printf("Turning on LED: ");


	//Turn on correct Colour:
	switch (statusColour)
	{
		case STATUS_COLOR_GREEN:
			printf("Green \r\n");
			pinMode(pinStatusGreen, OUTPUT);
			digitalWrite(pinStatusGreen, HIGH);
			break;
		case STATUS_COLOR_RED:
			printf("Red \r\n"); 
			pinMode(pinStatusRed, OUTPUT);
			digitalWrite(pinStatusRed, HIGH);
			break;

		case STATUS_COLOR_YELLOW:
			printf("Yellow \r\n"); 
			pinMode(pinStatusGreen, OUTPUT);
			pinMode(pinStatusRed, OUTPUT);
			digitalWrite(pinStatusGreen, HIGH);
			digitalWrite(pinStatusRed, HIGH);
			break;
	default:
		printf("Failed to turn on LED");
		break;
	}
}

bool Node::SendData()
{

	Serial.println("SENDING DATA ---------------------");
	bool dataStatus = false;
	bool dataStatusAll = true;
	radio.stopListening();
	sensors[0].Value(millis());

	for (int i = 1; i <= sensorCount; i++)
	{
		dataStatus = radio.write(&sensors[i], sizeof(Sensor));

		if (dataStatus)
		{
			Serial.print("Data sent... Sensor ");
			Serial.println(i);
		}
		else
		{
			dataStatusAll = false;
			Serial.print("Data failed. Sensor ");
			Serial.println(i);
			SetStatusLED(STATUS_COLOR_YELLOW); //No need to set to green if sends data as heartbeat will do it
		}
			
	}

	radio.startListening();
	lastSendTimeData = millis();
 
	return dataStatusAll;
}

int Node::ReadSensor(int SensorToRead)
{
	//TODO 
	// this reads the value at a moment in time, update this to take an average reading - must be configurable per sensor instance
	return sensors[SensorToRead].ReadSensor();
}

void Node::ReadAllSensors()
{
	for (int i = 1; i <= sensorCount; i++)
		ReadSensor(i);
}

bool Node::ReadRadio()
{
	bool radioRead = false;
	if (radio.available())
	{
		Serial.println("Incoming data.....");
		Sensor s = Sensor();
		radioRead = radio.read(&s, sizeof(Sensor));

		/*printf("Read Status %s\n\r", radioRead);
		printf("Pin %l\n\r", s.Pin());
		printf("IsDigital%s\n\r", s.IsDigital());
		printf("IsReadOnly %s\n\r", s.IsReadOnly());
		printf("Value %s\n\r", s.Value());*/

		Serial.print("Read Status: ");
		Serial.println(radioRead);
		Serial.print("Pin: ");
		Serial.println(s.Pin());
		Serial.print("IsDigital: ");
		Serial.println(s.IsDigital());
		Serial.print("IsReadOnly: ");
		Serial.println(s.IsReadOnly());
		Serial.print("Value: ");
		Serial.println(s.Value());
		Serial.print("Node: ");
		Serial.println(s.ParentNode());
		Serial.println(" ");

	}
	//else
		//Serial.println("Radio not available .....");


	return radioRead;
}

