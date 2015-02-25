/*
A file meant to handle obtaining data from the MPU-6050 Accelerometer unit

Registers for the MPU6050 are located here:
http://www.i2cdevlib.com/devices/mpu6050#registers

*/

#include "MPUAccel.h"
#define MPU_ADDRESS 0x68

bool MPUAccel::MPUInit()
{
	Wire.begin();
	Wire.beginTransmission(MPU_ADDRESS);
	Wire.write(0x6B);  // PWR_MGMT_1 register
	Wire.write(0);     // set to zero (wakes up the MPU-6050)
	Wire.endTransmission(true);

	return true;
}

MPUAccel::MPUAccel()
{

}

vec3 MPUAccel::getAccel()
{
	return accel;
}

vec3 MPUAccel::getGyro()
{
	return gyro;
}

int16_t MPUAccel::getTemp()
{
	return Tmp;
}

uint16_t getAccelAccuracy()
{
	uint16_t accuracy;

	Wire.beginTransmission(MPU_ADDRESS);

	Wire.write(0x1B);

}

//need to know the length of the payload you want and address it is coming from
//MAKE SURE THE PAYLOAD IS AN ARRAY OF LENGTH LENGTH, does not check for going over
void MPUAccel::readFromAddress(char address, char* payload, char length)
{
	Wire.beginTransmission(MPU_ADDRESS);

	Wire.write(address);

	Wire.endTransmission(false);	//need to read stuff out of the wire, so its MINE

	Wire.requestFrom(MPU_ADDRESS, length, true);

	for (int i = 0; i < length; i++)
	{
		payload[i] = Wire.read();
	}
}

//address is the register to write to, payload is what to send, length is the size of the payload (in bytes)
void MPUAccel::writeToAddress(char address, char payload)
{
	Wire.beginTransmission(MPU_ADDRESS);
	
	Wire.write(address);
	Wire.write(payload);

	Wire.endTransmission();
}

//Retrieve the values out of the buffer on the accelerometer
bool MPUAccel::retrieveValues()
{
	Wire.beginTransmission(MPU_ADDRESS);

	//starting register to read from
	Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)

	Wire.endTransmission(false);	//prevents another device from taking control of the I2C
	Wire.requestFrom(MPU_ADDRESS, 14, true);  // request a total of 14 registers
	// ^ THIS RELEASES THE I2C AFTER IT HAS READ ALL 14 BYTES
	//reads the 2 bytes for each number, the High (H) and Low (L) parts of the number
	AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
	AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
	GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
	GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
	GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

	accel = vec3(AcX, AcY, AcZ);
	gyro = vec3(GyX, GyY, GyZ);

	return true;
}
