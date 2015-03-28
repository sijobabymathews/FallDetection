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


GSMManager gsm;
FallDetection fallDetection;
MPUAccel accel;


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

	//if (fallDetection.isFall(accel.getAccel(), accel.getGyro()))
	//{
	//	PlayFallTone(7);
	//	
	//	gsm.init();
	//	char message[128];
	//	sprintf(message, "User has fallen - Location 43.46%d N, 80.54%d W", (int)accel.getAccel().y, (int)accel.getAccel().z);
	//	gsm.sendSMS(message);
	//}

	delay(100);
}
