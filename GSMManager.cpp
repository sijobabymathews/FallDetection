/* 
A class meant to process the GSM requirements of the fall detection system
*/

#include "GSMManager.h"

GSMManager::GSMManager()
{

}

bool GSMManager::init()
{
	//setup the software serial connection for the system
	SIM900 = new SoftwareSerial(7, 8);

	SIM900->begin(19200);
	powerToggle();

	delay(2000);	//pause for 2 seconds to wait to register on network
	sendATcommand("AT+CPIN?", "+CREG: 1", 10000);
}

bool GSMManager::sendSMS(char mess[])
{
	sendATcommand("AT+CMGF=1", "OK", 1000);                                                        // AT command to send SMS message
	delay(100);

	//CHANGE THE CONTACT NUMBER HERE - NEED THE +1 infront for country code
	int8_t ans = sendATcommand("AT+CMGS=\"+12267929610\"", "> ", 2000);                                     // recipient's mobile number, in international format
	if (ans == 1)
	{
		SIM900->println(mess);        // message to send
		delay(1000);
		SIM900->write(0x1A);                       // End AT command with a ^Z, ASCII code 26
		ans = sendATcommand("", "OK", 20000);
	}
	if (ans)
		Serial.println("SENT MESSAGE");
	else
		Serial.println("FAILED");
	delay(1000);                                     // give module time to send SMS
	return ans;
}

GSMManager::~GSMManager()
{
	delete SIM900;
}

//NEED TO SOLDER THE PINS TO ENABLE THIS
void GSMManager::powerToggle()
{
	digitalWrite(9, HIGH);
	delay(1000);
	digitalWrite(9, LOW);
	delay(1000);
}

int8_t GSMManager::sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

	uint8_t x = 0, answer = 0;
	char response[100];
	unsigned long previous;

	memset(response, '\0', 100);    // Initialice the string

	delay(100);

	while (SIM900->available() > 0) SIM900->read();    // Clean the input buffer

	SIM900->println(ATcommand);    // Send the AT command 

	delay(100);
	x = 0;
	previous = millis();

	// this loop waits for the answer
	do{
		// if there are data in the UART input buffer, reads it and checks for the asnwer
		if (SIM900->available() != 0){
			response[x] = SIM900->read();
			x++;
			// check if the desired answer is in the response of the module
			if (strstr(response, expected_answer) != NULL)
			{
				answer = 1;
			}
		}
		// Waits for the asnwer with time out
	} while ((answer == 0) && ((millis() - previous) < timeout));
	return answer;
}