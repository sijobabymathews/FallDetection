#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Wire.h>
#include <"vector.h">

class MPUAccel
{
  public:
    MPUAccel();
    vec3 getAccel();
    vec3 getGyro();
  private:
  
};

#endif  //ACCELEROMETER_H
