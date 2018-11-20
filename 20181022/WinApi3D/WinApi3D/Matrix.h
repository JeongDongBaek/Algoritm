#pragma once
class Matrix
{
public:
	class row
	{

		vector<float> m_vecData;

	public:
		row();
		~row();


		void ReSize(int dimension);
		float& operator[] (int index);
	};

	vector<row> m_vecData;

	Matrix(int dimension);
	

	void ReSize(int dimension);
	int Dimension();

	static Matrix Identity(int dimension);

	row& operator[] (int index); // == arr[1];

	bool operator==(Matrix& mat);
	bool operator!=(Matrix& mat);
	Matrix operator+(Matrix& mat);
	Matrix operator-(Matrix& mat);
	Matrix operator*(Matrix& mat);
	Matrix operator*(float f);
	Matrix TransPose();


	Matrix Inverse(OUT float& determinant); // �����...
	float Determinent(); //������� �ִ��� ������ �Ǵ��ϰ� 
	Matrix Adjoint(); // �������
	float getCofactor(int row, int col); // ���μ����
	float getMinor(int row, int col); // �����

	void Print();
	Matrix();
	~Matrix();

};

