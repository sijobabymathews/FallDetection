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
	bool retrieveAccelValues();
	char getAccuracy();
	void setAccelAccuracy(char accuracy);
	void setGyroAccuracy(char accuracy);

  private:
	  void writeToAddress(char address, unsigned char payload);
	  void readFromAddress(char address, unsigned char* payload, char length);
      int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
	  vec3 accel, gyro;

	  int16_t accelerometerAccuracy = 0x00;
      int16_t gyroAccuracy = 0x00;
	  int16_t filterStrength = 0x00;
};

#endif  //ACCELEROMETER_H
