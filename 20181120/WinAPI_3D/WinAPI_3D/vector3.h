#pragma once
class vector3
{
public:
	vector3();
	~vector3();

	float x, y, z;

	// 연산
	vector3 operator+(vector3& vec);
	vector3 operator-(vector3& vec);
	vector3 operator*(float f);
	vector3 operator/(float f);
	bool operator==(vector3& vec);
	bool operator!=(vector3& vec);

	// 내적 외적
	static float Dot(vector3& v1, vector3& v2);
	static vector3 Cross(vector3& v1, vector3& v2);

	// 길이, 정규화
	float Length();
	vector3 Normalize();
};

