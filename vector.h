#ifndef VECTOR_H
#define VECTOR_H

/*
Kinda more like a helper with a bunch of helpful functions that just a vector header.
*/


#include <math.h>
#include <Arduino.h>

//if you want verbose logging, else will only print out the 
#define DEBUG 1

#define P_THRESHOLD 250.0
#define DELTA_A_THRESHOLD 0.1
#define A_THRESHOLD 25000.00
#define HISTORY_SIZE 5




template<typename T> void serialPrint(T message)
{
	if (DEBUG)
		Serial.print(message);
}

template<typename T> void serialPrintln(T message)
{
	if (DEBUG)
		Serial.println(message);
}

//Length in seconds
static void PlayFallTone(int8_t length)
{

	// Which pin the speaker is on
	int speakerPin = 3;
	//tones to play for success
	int numTones = 1;
	int tones[] = { 300 };

	for (int i = 0; i < numTones; i++)
	{
		tone(speakerPin, tones[i]);
		delay(1000 * length);
	}
	noTone(speakerPin);
}

static void PlayTextFailed()
{


	// Which pin the speaker is on
	int speakerPin = 3;
	//tones to play for success
	int numTones = 5;
	int tones[] = { 400, 400, 300, 400, 400 };

	for (int i = 0; i < numTones; i++)
	{
		tone(speakerPin, tones[i]);
		delay(1000);
		noTone(speakerPin);
		delay(500);
	}
	noTone(speakerPin);
}

struct vec3
{
	float x;
	float y;
	float z;

	vec3(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}

	vec3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	vec3 cross(vec3 B)
	{
		return vec3(y*B.z - z*B.y, z*B.x - x*B.z, x*B.y - y*B.x);
	}

	float dot(vec3 B)
	{
		return (x * B.x + y * B.y + z * B.z);
	}

	float length()
	{
		
		return sqrt(x * x + y * y + z * z);
	}

	void normalize()
	{
		if (length() == 0)
			return;

		x = x / length();
		y = y / length();
		z = z / length();
	}

	vec3 normalized()
	{
		if (length() == 0)
			return vec3(0,0,0);
		return vec3(x / length(), y / length(), z / length());
	}

	vec3 operator-(const vec3 &a)
	{
		return vec3(x - a.x, y - a.y, z - a.z);
	}
	//COPY CONSTRUCTOR
	vec3& operator=(const vec3 &a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}
};

#endif  //VECTOR_H
