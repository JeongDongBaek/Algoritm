#pragma once
class vector3;

class matrix
{
public:
	matrix();
	matrix(int dimension); // 행렬의 사이즈를 정한다. 4x4 행렬
	~matrix();

private:
	class row // 행
	{
	private:
		vector<float>	m_vecData;

	public:
		row();
		~row();

		void Resize(int dimension); // 행의 사이즈를 정한다.
		float& operator[](int index); // 행의 []번째 데이타를 반환한다.
	};

	vector<row> m_vecData;

public:
	void Resize(int dimension); // 벡터의 크기를 최대크기를 설정한다. (reserver)와 비슷하지만 남은공간에 0.0f로 초기화한다.
	int Dimension(); // 행의 크기를 반환한다. 

	static matrix Identity(int dimension); // 

	row& operator[](int index); // 열의 []번째 데이타를 반환한다.

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
	float Determinent(); // 행렬					// 판별식
	matrix Adjoint();							// 수반행렬 // 여인수행렬을 전치한것 ( 대각선 중심으로 좌우를 반전시킴)
	float getCofactor(int row, int col);			// 여인수행렬 구하기
	float getMinor(int row, int col);				// 소행렬 구하기 (해당되는 행과 열을 제외한 나머지 값

	void Print();
};

