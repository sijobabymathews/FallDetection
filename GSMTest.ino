// MOSTLY TAKEN FROM http://arduino.cc/en/Tutorial/GSMExamplesSendSMS

/*

SMS Sender and Accelerometer

USing a GSM shield and a MPU-6050 to create a GSM notifying accelerometer reader

*/

#include <Wire.h>
#include <GSM.h>
#include "MPUAccel.h"
#include "FallDetection.h"
#include "GSMManager.h"



GSMManager gsm;
FallDetection fallDetection;
MPUAccel accel;

void setup()
{ 
	Serial.begin(9600);

	serialPrintln("GONNA START STUFF NOW");

	accel.MPUInit();
	//setup the messaging back to the computer
	serialPrintln("INIT SYSTEM");
}

void loop() 
{
	//Serial.println("ABOUT TO GET SENSOR VALUES");
	//get the values out of the IMU sensor
	accel.retrieveValues();
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

	serialPrintln("GONNA CHECK IF I FELL");
	if (fallDetection.isFall(accel.getAccel(), accel.getGyro()))
	{
		gsm.init();
		char message[] = "TESTING_123";
		gsm.sendSMS(message);
	}

	serialPrintln("I FINISHED CHECKING");
	delay(333);
}
