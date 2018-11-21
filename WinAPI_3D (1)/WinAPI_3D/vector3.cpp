#include "stdafx.h"
#include "vector3.h"
#include "matrix.h"

//vector3 vec1;
//vector3 vec2;
//vector3 vecSum;
//vecSum = vec1.operator+(vec2);
//vecSum = vec1 + vec2;


vector3::vector3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}

vector3::vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
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

// 위치 벡터와 행렬 연산
vector3 vector3::TransformCoord(vector3 & vec, matrix & mat)
{
	vector3 vRet;

	vRet.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0] + 1.0f * mat[3][0];
	vRet.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1] + 1.0f * mat[3][1];
	vRet.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2] + 1.0f * mat[3][2];

	float w = vec.x * mat[0][3] + vec.y * mat[1][3] + vec.z * mat[2][3] + 1.0f * mat[3][3];
	if (-EPSILON > w || w > EPSILON)
	{
		vRet.x /= w;
		vRet.y /= w;
		vRet.z /= w;
	}

	return vRet;
}

// 방향 벡터와 행렬 연산
vector3 vector3::TransformNormal(vector3 & vec, matrix & mat)
{
	vector3 vRet;

	vRet.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0];
	vRet.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1];
	vRet.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2];
	
	return vRet;
}
