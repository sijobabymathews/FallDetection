// MOSTLY TAKEN FROM http://arduino.cc/en/Tutorial/GSMExamplesSendSMS

/*

SMS Sender and Accelerometer

USing a GSM shield and a MPU-6050 to create a GSM notifying accelerometer reader

*/

#include <Wire.h>
#include <SoftwareSerial.h>
#include "MPUAccel.h"
#include "FallDetection.h"
#include "GSMManager.h"

int speakerPin = 3;

int numTones = 1;
int tones[] = { 300, 310, 320, 330, 340, 350, 360, 370, 380, 390 };

GSMManager gsm;
FallDetection fallDetection;
MPUAccel accel;

void playTones()
{
	for (int i = 0; i < numTones; i++)
	{
		tone(speakerPin, tones[i]);
		delay(1000);
	}
	noTone(speakerPin);
}

void setup()
{ 
	Serial.begin(19200);
	pinMode(3, OUTPUT);

	accel.MPUInit();
	//setup the messaging back to the computer
	serialPrintln("INIT SYSTEM");
}

void loop() 
{
	//Serial.println("ABOUT TO GET SENSOR VALUES");
	//get the values out of the IMU sensor
	accel.retrieveAccelValues();
	//Serial.println("GOT SENSOR VALUES");

	//want to print at all times, so keep as Serial.print()
	Serial.print(accel.getAccel().x);
	Serial.print(", ");
	Serial.print(accel.getAccel().y);
	Serial.print(", ");
	Serial.print(accel.getAccel().z);
	Serial.print(", ");
	Serial.print(accel.getGyro().x);
	Serial.print(", ");
	Serial.print(accel.getGyro().y);
	Serial.print(", ");
	Serial.println(accel.getGyro().z);

	if (fallDetection.isFall(accel.getAccel(), accel.getGyro()))
	{
		Serial.print("I FELL YOOOO");
		playTones();
		
		/*gsm.init();
		char message[] = "Yo man, I fell";
		gsm.sendSMS(message);*/
	}

	delay(100);
}
