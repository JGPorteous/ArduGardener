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

