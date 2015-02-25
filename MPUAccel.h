#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "vector.h"
#include <Wire.h>

class MPUAccel
{
  public:
    MPUAccel();
	bool MPUInit();
    vec3 getAccel();
    vec3 getGyro();
	int16_t getTemp();
	bool retrieveValues();

  private:
    int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
	vec3 accel, gyro;

};

#endif  //ACCELEROMETER_H
