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


	Matrix Inverse(OUT float& determinant); // 역행렬...
	float Determinent(); //역행렬이 있는지 없는지 판단하고 
	Matrix Adjoint(); // 수반행렬
	float getCofactor(int row, int col); // 여인수행렬
	float getMinor(int row, int col); // 소행렬

	void Print();
	Matrix();
	~Matrix();

};

