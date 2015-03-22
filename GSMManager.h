#ifndef GSMMANAGER_H
#define GSMMANAGER_H

#include <SoftwareSerial.h>
#include <Arduino.h>

class GSMManager
{
  public:
    GSMManager();
	~GSMManager();
    bool init();
    bool sendSMS(char mess[]);
    
  private:
	void powerToggle();
	int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout);
	SoftwareSerial* SIM900;

};

#endif  //GSMMANAGER_H
