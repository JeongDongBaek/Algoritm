#pragma once

class Vector3
{
private:

public:

	float x, y, z; // �� ��ǥ�� ����
	
	// ���� (���ϱ� ����... )
	Vector3 operator+(Vector3& vec); //������ �������̵�
	Vector3 operator-(Vector3& vec); //������ �������̵�
	Vector3 operator*(float f); //������ �������̵�
	Vector3 operator/(float f); //������ �������̵�
	bool operator==(Vector3& vec); //������ �������̵�
	bool operator!=(Vector3& vec); //������ �������̵� // ridding �θ��� Ŭ������ Ư������ �ٸ��� �ڽ�Ŭ�������� �ٸ� �޼ҵ� ���� // loading ���� �޼ҵ� �̸����� �ٸ� ��ɼ��� (�Ű������� ���� ���ڸ� �ٸ��� �Ѵٰų�)

	// ���� ����
	static float Dot(Vector3& v1, Vector3& v2);
	static Vector3 Cross(Vector3& v1, Vector3& v2);

	// ����, ����ȭ
	float Length();
	Vector3 Normalize();

	Vector3();
	~Vector3();
};

