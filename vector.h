#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <Arduino.h>

//if you want verbose logging, else will only print out the 
#define DEBUG 1
#define P_THRESHOLD 20000.00
#define DELTA_A_THRESHOLD 10000.00
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
