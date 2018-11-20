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

	matrix Inverse(OUT float& determinent);		// 역행렬
	float Determinent();						// 판별식
	matrix Adjoint();							// 수반행렬
	float Cofactor(int row, int col);			// 여인수행렬
	float Minor(int row, int col);				// 소행렬

	void Print();
};

