#include "stdafx.h"
#include "vector3.h"

//vector3 vec1;
//vector3 vec2;
//vector3 vecSum;
//vecSum = vec1.operator+(vec2);
//vecSum = vec1 + vec2;


vector3::vector3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}


vector3::~vector3()
{
}

vector3 vector3::operator+(vector3 & vec)
{
	vector3 v;
	v.x = x + vec.x;
	v.y = y + vec.y;
	v.z = z + vec.z;
	return v;
}

vector3 vector3::operator-(vector3 & vec)
{
	vector3 v;
	v.x = x - vec.x;
	v.y = y - vec.y;
	v.z = z - vec.z;
	return v;
}

vector3 vector3::operator*(float f)
{
	vector3 v;
	v.x = x * f;
	v.y = y * f;
	v.z = z * f;
	return v;
}

vector3 vector3::operator/(float f)
{
	vector3 v;
	v.x = x / f;
	v.y = y / f;
	v.z = z / f;
	return v;
}

bool vector3::operator==(vector3 & vec)
{
	//if (x == vec.x && y == vec.y && z == vec.z)
	if (x - EPSILON <= vec.x &&  vec.x <= x + EPSILON &&
		y - EPSILON <= vec.y &&  vec.y <= y + EPSILON &&
		z - EPSILON <= vec.z &&  vec.z <= z + EPSILON)
		return true;

	return false;
}

bool vector3::operator!=(vector3 & vec)
{
	return !(*this == vec);
}

float vector3::Dot(vector3 & v1, vector3 & v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vector3 vector3::Cross(vector3 & v1, vector3 & v2)
{
	vector3 v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;

	return v;
}

float vector3::Length()
{
	return sqrtf(x * x + y * y + z * z);
}

vector3 vector3::Normalize()
{
	float l = Length();

	vector3 v;
	v.x = x / l;
	v.y = y / l;
	v.z = z / l;

	return v;
}
