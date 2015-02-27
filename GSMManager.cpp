/* 
A class meant to process the GSM requirements of the fall detection system
*/

#include "GSMManager.h"

#define CONTACT_NUMBER "5196350891"
//PIN number for the SIM card
#define PIN_NUMBER "2016"

GSMManager::GSMManager()
{

}

bool GSMManager::init()
{
	bool isConnected = false;

	// wait for connection to network
	while (!isConnected)
	{
		Serial.println("SHE DOESN'T EVEN GO HERE");
		Serial.println(GSM_READY, DEC);
		Serial.println(module.begin(PIN_NUMBER), DEC);
		if (module.begin(PIN_NUMBER) == GSM_READY)
		{
			Serial.println("HEREYOOO");
			isConnected = true;
		}
		else
		{
			Serial.println("ATTEMPT FAILED");
			delay(500);
		}
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