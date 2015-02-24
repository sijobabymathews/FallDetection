// MOSTLY TAKEN FROM http://arduino.cc/en/Tutorial/GSMExamplesSendSMS

/*

SMS Sender and Accelerometer

USing a GSM shield and a MPU-6050 to create a GSM notifying accelerometer reader

*/

#include <GSM.h>
#include <Wire.h>
#include <"Accelerometer.h">
#include <"FallDetection.h">
#include <"GSMManager.h">

#define CONTACT_NUMBER 4169300199
//PIN number for the SIM card
#define PIN_NUMBER ""
#define MPU_ADDRESS 0x68

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

GSM gsm;
GSM_SMS message;

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  //setup the messaging back to the computer
  Serial.begin(9600);
}

void setupGSM() 
{  
  bool isConnected = false;
  
  // wait for connection to network
  while(!isConnected)
  {
    if(gsm.begin(PIN_NUMBER) == GSM_READY)
      isConnected = true;
    else
      delay(500);
  }
  
  Serial.println("GSM Connected");
}

void loop() 
{
  Wire.beginTransmission(MPU_ADDRESS);
  
  //starting register to read from
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS,14,true);  // request a total of 14 registers
  
  //reads the 2 bytes for each number, the High (H) and Low (L) parts of the number
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  
  
  //Print the values out of the serial connection
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(333);
}
