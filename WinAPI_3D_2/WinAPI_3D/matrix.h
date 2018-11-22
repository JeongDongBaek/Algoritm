#pragma once
class vector3;
class matrix
{
public:
	matrix();
	matrix(int dimension);
	~matrix();

private:
	class row
	{
	private:
		vector<float>	m_vecData;

	public:
		row();
		~row();

		void Resize(int dimension);
		float& operator[](int index);
	};

	vector<row> m_vecData;

public:
	void Resize(int dimension);
	int Dimension();

	static matrix Identity(int dimension);

	row& operator[](int index);

	//arr.operator[](1);
	//arr[1][2];

	bool operator==(matrix& mat);
	bool operator!=(matrix& mat);
	matrix operator+(matrix& mat);
	matrix operator-(matrix& mat);
	matrix operator*(matrix& mat);
	matrix operator*(float f);
	matrix Transpose();

	matrix Inverse(OUT float& determinent);		// �����
	float Determinent();						// �Ǻ���
	matrix Adjoint();							// �������
	float Cofactor(int row, int col);			// ���μ����
	float Minor(int row, int col);				// �����
	
	// ��ȯ ���
	static matrix Translation(float x, float y, float z);
	static matrix Translation(vector3& v);
	static matrix RotationX(float angle);
	static matrix RotationY(float angle);
	static matrix RotationZ(float angle);


	// ���ý����̽� : ������ǥ�� ��ü����  /  ���彺���̽� : �������� ������ 0,0���� ��� ��ü���� ������ ��ǥ�� ������ ����  

	// ������ ���������� ����
	static matrix View(vector3& eye, vector3& lookAt, vector3& up);
	static matrix Projection(float fovY, float aspect, float nearZ, float farZ);
	static matrix Viewport(float x, float y, float width, float height, float minZ, float maxZ);
};

