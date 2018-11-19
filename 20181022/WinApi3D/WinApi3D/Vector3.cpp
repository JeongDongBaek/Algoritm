#include "stdafx.h"
#include "Vector3.h"


//// ���ʹ� �̷��� ������ �ϴ°�
//Vector3 vec1;
//Vector3 vec2;
//Vector3 vecSum;
//
//vecSum = vec1.operator+(vec2); // �����ڸ� �������̵� �ϱ����� ��Ģ�̴�.
//vecSum = vec1 + vec2; // ���� �̷��� �� ���� �ִ�.


Vector3::Vector3()
	:x(0.0f), y(0.0f), z(0.0f)
{
}


Vector3::~Vector3()
{
}



// operator��? 
Vector3 Vector3::operator+(Vector3 & vec)
{
	Vector3 v;
	v.x = x + vec.x;
	v.y = y + vec.y;
	v.z = z + vec.z;
	return v;



	// ���� ���
	//// ���������� vector3 a, vector3 b, vector3 c�� �������� c = a.operator+(b) �� �����Ҽ��ְ��Ѵ�.
	//Vector3 tempVector3;
	//tempVector3.x = x + vec.x;
	//tempVector3.y = y + vec.y;
	//tempVector3.z = z + vec.z;

	//return tempVector3;
}

Vector3 Vector3::operator-(Vector3 & vec)
{
	Vector3 v;
	v.x = x - vec.x;
	v.y = y - vec.y;
	v.z = z - vec.z;
	return v;




	//// ���Ǵ��
	//Vector3 tempVector3;
	//tempVector3.x = x - vec.x;
	//tempVector3.y = y - vec.y;
	//tempVector3.z = z - vec.z;

	//return tempVector3;
}

Vector3 Vector3::operator*(float f)
{

	Vector3 v;
	v.x = x * f;
	v.y = y * f;
	v.z = z * f;
	return v;



	/*Vector3 tempVector3;
	tempVector3.x = x * f;
	tempVector3.y = y * f;
	tempVector3.z = z * f;

	return tempVector3;*/
}

Vector3 Vector3::operator/(float f)
{
	Vector3 v;
	v.x = x / f;
	v.y = y / f;
	v.z = z / f;
	return v;




	//Vector3 tempVector3;
	//tempVector3.x = x / f;
	//tempVector3.y = y / f;
	//tempVector3.z = z / f;

	//return tempVector3;
}

bool Vector3::operator==(Vector3 & vec)
{
	if (x - EPSILON <= vec.x && x <= vec.x + EPSILON &&
		y - EPSILON <= vec.y && y <= vec.y + EPSILON &&
		z - EPSILON <= vec.z && z <= vec.z + EPSILON  )
		return true;

	return false;

	/*Vector3 tempVector3;
	if ( fabsf(x - vec.x) < EPSILON )
		if (fabsf(y - vec.y) < EPSILON)
			if (fabsf(z - vec.z) < EPSILON)
				return true;*/
}

bool Vector3::operator!=(Vector3 & vec)
{
	return !(*this == vec);
}

float Vector3::Dot(Vector3 & v1, Vector3 & v2) 
{ //���� // ������������ �ʴ�. -> �Ӹ������� �׸��� �׸����� ����. // �������Ͷ� ? ũ�Ⱑ 1�� ����
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

  
  /*float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;*/
}

Vector3 Vector3::Cross(Vector3 & v1, Vector3 & v2)
{
	Vector3 v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;

	return v;


	/*Vector3 tempVec;
	tempVec.x = (v1.y * v2.z) - (v1.z * v2.y);
	tempVec.y = (v1.z * v2.x) - (v1.x * v2.z);
	tempVec.z = (v1.x * v2.y) - (v1.y * v2.x);
	return tempVec;*/
}

float Vector3::Length()
{
	return sqrtf(x*x + y*y + z*z);

	/*float fLength = x*x + y*y + z*z;
	return sqrtf(fLength);*/
}

Vector3 Vector3::Normalize()
{
	float l = Length();
	Vector3 v;
	v.x = x / l;
	v.y = y / l;
	v.z = z / l;

	return v;


	/*Vector3 tempVec;

	tempVec.x = x / this->Length();
	tempVec.y = y / this->Length();
	tempVec.z = z / this->Length();

	return tempVec;*/
}
