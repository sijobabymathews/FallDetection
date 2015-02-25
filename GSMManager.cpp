/* 
A class meant to process the GSM requirements of the fall detection system
*/

#include "GSMManager.h"

#define CONTACT_NUMBER "4169300199"
//PIN number for the SIM card
#define PIN_NUMBER ""

GSMManager::GSMManager()
{

}

bool GSMManager::init()
{
	bool isConnected = false;

	// wait for connection to network
	while (!isConnected)
	{
		if (module.begin(PIN_NUMBER) == GSM_READY)
			isConnected = true;
		else
			delay(500);
	}

	Serial.println("GSM Connected");
	return true;
}

bool GSMManager::sendSMS(char mess[])
{
	message.beginSMS(CONTACT_NUMBER);
	message.print(mess);
	message.endSMS();
	return true;
}