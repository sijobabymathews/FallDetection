/*
A file meant to handle obtaining data from the MPU-6050 Accelerometer unit

Registers for the MPU6050 are located here:
http://www.i2cdevlib.com/devices/mpu6050#registers

*/

#include "MPUAccel.h"
//the I2C address for the accelerometer chip
#define MPU_ADDRESS 0x68

#define ACCEL_ACCURACY_ADDRESS 0x1C
#define GYRO_ACCURACY_ADDRESS 0x1B
#define PWR_MANAGEMENT 0x6B
#define ACCEL_ADRESS_VALUE_X 0x3B

bool MPUAccel::MPUInit()
{
	Wire.begin();

	//enable the MPU6050
	// sets the power management bit to 0, enbaling the chip
	writeToAddress(PWR_MANAGEMENT, 0);

	// +/- 2G is appropriate, but need +/- 1000 deg/s for angle measurement
	setAccelAccuracy(0x00);
	setGyroAccuracy(0x02);

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

char MPUAccel::getAccuracy()
{
	unsigned char accuracy;

	readFromAddress(ACCEL_ACCURACY_ADDRESS, &accuracy, 1);

	Serial.print("ACCURACY VAR: ");
	Serial.println(accuracy, DEC);
	return accuracy;
}

//has 3 settings of accuracy
// 0x00 : +/- 2G
// 0x01 : +/- 4G
// 0x02 : +/- 8G
// 0x03 : +/- 16G
void MPUAccel::setAccelAccuracy(char accuracy)
{
	//need the shift as per the datasheet
	writeToAddress(ACCEL_ACCURACY_ADDRESS, accuracy << 3);
	accelerometerAccuracy = accuracy;
	
}

//has 3 settings of accuracy
//0 = ± 250 ° / s, 131 LSB / ° / s
//1 = ± 500 ° / s, 65.5 LSB / ° / s
//2 = ± 1000 ° / s, 32.8 LSB / ° / s
//3 = ± 2000 ° / s, 16.4 LSB / ° / s
void MPUAccel::setGyroAccuracy(char accuracy)
{
	writeToAddress(GYRO_ACCURACY_ADDRESS, accuracy << 3);
	gyroAccuracy = accuracy;
}

//need to know the length of the payload you want and address it is coming from
//MAKE SURE THE PAYLOAD IS AN ARRAY OF LENGTH LENGTH, does not check for going over
void MPUAccel::readFromAddress(char address, unsigned char* payload, char length)
{
	Wire.beginTransmission(MPU_ADDRESS);
	//starting register to read from
	Wire.write(address);

	Wire.endTransmission(false);	//prevents another device from taking control of the I2C

	Wire.requestFrom(MPU_ADDRESS, length, true);	//closes the I2C after reading all values
	// ^ THIS RELEASES THE I2C AFTER IT HAS READ ALL BYTES
	for (char i = 0; i < length; i++)
	{
		payload[i] = Wire.read();
	}
}

//address is the register to write to, payload is what to send, length is the size of the payload (in bytes)
void MPUAccel::writeToAddress(char address, unsigned char payload)
{
	Wire.beginTransmission(MPU_ADDRESS);
	
	Wire.write(address);
	Wire.write(payload);

	Wire.endTransmission();
}

//Retrieve the values out of the buffer on the accelerometer
bool MPUAccel::retrieveAccelValues()
{
	unsigned char accelValues[14];
	readFromAddress(ACCEL_ADRESS_VALUE_X, accelValues, 14);

	//reads the 2 bytes for each number, the High (H) and Low (L) parts of the number
	AcX = accelValues[0] << 8 | accelValues[1];  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
	AcY = accelValues[2] << 8 | accelValues[3];  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	AcZ = accelValues[4] << 8 | accelValues[5];  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	Tmp = accelValues[6] << 8 | accelValues[7];  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
	GyX = accelValues[8] << 8 | accelValues[9];  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
	GyY = accelValues[10] << 8 | accelValues[11];  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
	GyZ = accelValues[12] << 8 | accelValues[13];  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

	/*Serial.print(AcX);
	Serial.print(", ");
	Serial.print(AcY);
	Serial.print(", ");
	Serial.print(AcZ);
	Serial.print(", ");
	Serial.print(GyX);
	Serial.print(", ");
	Serial.print(GyY);
	Serial.print(", ");
	Serial.println(GyZ);*/

	double scalingFactor = 1.0;
	//00 = 0 = 2G, 01 = 1 = 4G, 10 = 2 = 8G, 11 = 3 = 16G
	switch (accelerometerAccuracy) {
	case 0x00:
		scalingFactor = 2.0 / 32767.0;
		break;
	case 0x01:
		scalingFactor = 4.0 / 32767.0;
		break;
	case 0x02:
		scalingFactor = 8.0 / 32767.0;
		break;
	case 0x03:
		scalingFactor = 16.0 / 32767.0;
		break;
	}



	accel = vec3(AcX * scalingFactor, AcY * scalingFactor, AcZ * scalingFactor);


	//get the values in degrees
	switch (gyroAccuracy) {
	case 0x00:
		scalingFactor = 250.0 / 32767.0;
		break;
	case 0x01:
		scalingFactor = 500.0 / 32767.0;
		break;
	case 0x02:
		scalingFactor = 1000.0 / 32767.0;
		break;
	case 0x03:
		scalingFactor = 2000.0 / 32767.0;
		break;
	}


	gyro = vec3(GyX * scalingFactor, GyY * scalingFactor, GyZ * scalingFactor);

	return true;
}
