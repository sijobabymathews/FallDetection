#ifndef GSMMANAGER_H
#define GSMMANAGER_H

#include <GSM.h>

class GSMManager
{
  public:
    GSMManager();
    bool init();
    bool sendSMS(char mess[]);
    
  private:
    GSM module;
	GSM_SMS message;
    
};

#endif  //GSMMANAGER_H
