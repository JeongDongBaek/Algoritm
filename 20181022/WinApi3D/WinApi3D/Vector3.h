#pragma once

class Vector3
{
private:

public:

	float x, y, z; // 각 좌표계 저장
	
	// 연산 (더하기 빼기... )
	Vector3 operator+(Vector3& vec); //연산자 오버라이딩
	Vector3 operator-(Vector3& vec); //연산자 오버라이딩
	Vector3 operator*(float f); //연산자 오버라이딩
	Vector3 operator/(float f); //연산자 오버라이딩
	bool operator==(Vector3& vec); //연산자 오버라이딩
	bool operator!=(Vector3& vec); //연산자 오버라이딩 // ridding 부모의 클래스의 특성과는 다르게 자식클래스에서 다른 메소드 설정 // loading 같은 메소드 이름으로 다른 기능설정 (매개변수의 수나 인자를 다르게 한다거나)

	// 내적 외적
	static float Dot(Vector3& v1, Vector3& v2);
	static Vector3 Cross(Vector3& v1, Vector3& v2);

	// 길이, 정규화
	float Length();
	Vector3 Normalize();

	Vector3();
	~Vector3();
};

