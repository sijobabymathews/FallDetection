#ifndef GSMMANAGER_H
#define GSMMANAGER_H

#include <GSM.h>

class GSMManager
{
  public:
    GSMManager();
    bool init();
    bool sendSMS(char* message, int16_t length);
    
  private:
    GSM module;
	GSM_SMS message;
    
};

#endif  //GSMMANAGER_H
