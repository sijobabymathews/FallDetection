/*
A class meant to detect falls from the user - using accelerometer and gyro information
*/

#include "FallDetection.h"

FallDetection::FallDetection()
{

}

bool FallDetection::isFall(vec3 accelData, vec3 gyroData)
{
	return false;
}

FallDetection::~FallDetection()
{
	if (LPFGyro)
		delete[] LPFGyro;
	if (LPFAccel)
		delete[] LPFAccel;
}