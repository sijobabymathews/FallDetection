#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

struct vec3
{
	double x;
	double y;
	double z;

	vec3(double a, double b, double c)
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

	double dot(vec3 B)
	{
		return (x * B.x + y * B.y + z * B.z);
	}

	double length()
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
