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
	
	// 변환 행렬
	static matrix Translation(float x, float y, float z);
	static matrix Translation(vector3& v);
	static matrix RotationX(float angle);
	static matrix RotationY(float angle);
	static matrix RotationZ(float angle);


	// 로컬스페이스 : 기준좌표가 객체기준  /  월드스페이스 : 기준점을 무조건 0,0으로 잡고 객체마다 고유한 좌표를 가지고 있음  

	// 렌더링 파이프라인 관련
	static matrix View(vector3& eye, vector3& lookAt, vector3& up);
	static matrix Projection(float fovY, float aspect, float nearZ, float farZ);
	static matrix Viewport(float x, float y, float width, float height, float minZ, float maxZ);
};

