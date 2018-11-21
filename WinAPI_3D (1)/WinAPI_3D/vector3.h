#pragma once
class matrix;
class vector3
{
public:
	vector3();
	vector3(float _x, float _y, float _z);
	~vector3();

	float x, y, z;

	// ����
	vector3 operator+(vector3& vec);
	vector3 operator-(vector3& vec);
	vector3 operator*(float f);
	vector3 operator/(float f);
	bool operator==(vector3& vec);
	bool operator!=(vector3& vec);

	// ���� ����
	static float Dot(vector3& v1, vector3& v2);
	static vector3 Cross(vector3& v1, vector3& v2);

	// ����, ����ȭ
	float Length();
	vector3 Normalize();

	// ��� ����
	static vector3 TransformCoord(vector3& vec, matrix& mat);
	static vector3 TransformNormal(vector3& vec, matrix& mat);
};

