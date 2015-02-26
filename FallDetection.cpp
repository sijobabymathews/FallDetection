/*
A class meant to detect falls from the user - using accelerometer and gyro information
*/

#include "FallDetection.h"

FallDetection::FallDetection()
{

}

bool FallDetection::isFall(vec3 accelData, vec3 gyroData)
{
	float orientation_mag = gyroData.length();
	history[spot] = accelData.length();
	
	char less_one = spot - 1;
	if (less_one == -1){
		less_one = HISTORY_SIZE - 1;
	}
	float change_accel = history[spot] - history[less_one];

	//Happy path: straight, fast, forward/backward fall
	if (orientation_mag >= P_THRESHOLD && change_accel > DELTA_A_THRESHOLD){
		return true;
	}

	//slower/gradual fall, if you try to break your fall
	char last_one = spot + 1;
	if (last_one > HISTORY_SIZE - 1){
		last_one = 0;
	}
	change_accel = history[spot] - history[last_one];
	if (orientation_mag >= P_THRESHOLD && change_accel > DELTA_A_THRESHOLD){
		return true;
	}

	if (++spot >= HISTORY_SIZE){
		spot = 0;
	}
	return false;
}

FallDetection::~FallDetection()
{
	if (LPFGyro)
		delete[] LPFGyro;
	if (LPFAccel)
		delete[] LPFAccel;
}