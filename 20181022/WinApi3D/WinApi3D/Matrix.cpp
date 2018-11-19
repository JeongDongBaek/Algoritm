#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

Matrix::row::row()
{
}

Matrix::row::~row()
{
}




void Matrix::row::ReSize(int dimension)
{ // 4 x 4 행렬을 생성하여 4가 들어간다고 가정
	row::m_vecData.resize(dimension); // float형 변수가 4개 들어가는 벡터가 만들어지겠지
} 


// 주소값을 넘긴다.
float & Matrix::row::operator[](int index)
{
	return row::m_vecData[index]; // float& 이니까 레퍼런스로 넘겨준다는 뜻. 받는 변수가 이것을 별칭으로 쓸 수 있다.
}

Matrix::Matrix(int dimension)
{
}

void Matrix::ReSize(int dimension)
{
	m_vecData.resize(dimension);
	for (int i = 0; i < dimension; ++i)
	{
		m_vecData[i].ReSize(dimension);
	}
}

int Matrix::Dimension()
{

	return (int)m_vecData.size();
}

Matrix Matrix::Identity(int dimension)
{
	//스태틱 함수는 클래스의 함수 자체를 호출하면된다. ex)
	//// main()
	//{
	//	matrix mat;
	//	mat.indentity; < -이것은 일반적인 함수호출
	//	matrix::identity; 요렇게 해야한다

	//}
	
	Matrix matRet(dimension);
	for (int i = 0; i < dimension; ++i)
	{
		for (int j = 0; j < dimension; ++j)
		{
			if (i == j)
				matRet[i][j] = 1;
			else
				matRet[i][j] = 0;
			// matRet[i][j] = (i == j ) ? 1 : 0
		}
	}




	return matRet;
}

Matrix::row & Matrix::operator[](int index)
{
	return m_vecData[index];

	// TODO: 여기에 반환 구문을 삽입합니다.
}

bool Matrix::operator==(Matrix & mat)
{
	// 차수가 같아야하며 원소의 값이 같아야한다. 여기서 차수는 무조건 4이므로 패스

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			if ((*this)[i][j] - EPSILON > mat[i][j])
				return false;
			if ((*this)[i][j] + EPSILON < mat[i][i])
				return false;
		}
	}

	return true;
}

bool Matrix::operator!=(Matrix & mat)
{
	return !((*this) == mat);
}

Matrix Matrix::operator+(Matrix & mat)
{

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			(*this)[i][j] += mat[i][j];
		}
	}

	return (*this);
}

Matrix Matrix::operator-(Matrix & mat)
{
	Matrix matRet;

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}

	return matRet;
}

Matrix Matrix::operator*(Matrix & mat)
{
	Matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = 0.0f;
			for (int k = 0; k < Dimension(); ++k)
			{
				matRet[i][j] += (*this)[i][k] * mat[k][j];
			}
		}
	}

	return (*this);
}

Matrix Matrix::operator*(float f)
{
	Matrix matRet;


	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}

	return (*this);
	
}

Matrix Matrix::TransPose() // 전치행렬
{
	Matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][i] = (*this)[j][i];
		}
	}


	return (*this);
}

Matrix Matrix::Inverse(OUT float & determinant)
{
	return Matrix();
}

float Matrix::Determinent()
{
	// ad -bc




	return 0.0f;
}

Matrix Matrix::Adjoint()
{
	return Matrix();
}

float Matrix::getCofactor(int row, int col)
{
	


	return 0.0f;
}

float Matrix::getMinor(int row, int col) // 4 x 4 행렬이라고 가정한다.
{
	Matrix temp;

	for (int i = 0; i < Determinent(); ++i)
	{
		for (int j = 0; j < Determinent(); ++j)
		{
			if (i == row || j == col) continue; // 해당되는 행과 열은 제외된다.
			
			temp.m_vecData
		}
	}


	return 0.0f;
}


