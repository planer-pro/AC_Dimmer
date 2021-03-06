#include <Arduino.h>
#include <CyberLib.h>

#define dimPin 4
#define zeroPin 2

uint8_t missTicsCount;
uint8_t dimmer = 128; //for example

bool firstDetect = true; //for property enable interrupt

void setup()
{
	Serial.begin(57600);

	pinMode(dimPin, OUTPUT);
	pinMode(zeroPin, INPUT);

	digitalWrite(dimPin, 0);

	attachInterrupt(0, detectZero, RISING);
}

void makeOutPower()
{
	missTicsCount++;

	if (missTicsCount >= dimmer)
		digitalWrite(dimPin, 1);
	else
		digitalWrite(dimPin, 0);
}

void detectZero()
{
	if (firstDetect)
	{
		firstDetect = false;

		StartTimer1(makeOutPower, 40); //~40mkS - one discrete period (10mS/255)
	}
	else
		RestartTimer1();

	missTicsCount = 0;
}

void loop()
{
	if (Serial.available())
	{
		dimmer = Serial.parseInt();
	}
}