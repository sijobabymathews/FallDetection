#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "vector.h"
#include <Wire.h>

class MPUAccel
{
  public:
    MPUAccel();
    vec3 getAccel();
    vec3 getGyro();
	int16_t getTemp();

  private:
    int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

};

#endif  //ACCELEROMETER_H
