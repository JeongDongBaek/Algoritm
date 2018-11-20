#include "stdafx.h"
#include "matrix.h"

matrix::row::row()
{
}

matrix::row::~row()
{
}

matrix::matrix()
{
}

matrix::matrix(int dimension)
{
	if (dimension <= 4)
		Resize(dimension);
	else
		return;
}

matrix::~matrix()
{
}




void matrix::row::Resize(int dimension)
{
	m_vecData.resize(dimension);
}

float & matrix::row::operator[](int index) 
{
	return m_vecData[index];
}



void matrix::Resize(int dimension) // 열을 먼저 할당하면 이 안에서 열의 크기만큼 행 또한 할당한다. 
{
	m_vecData.resize(dimension); // 열의 최대크기를 dimension만큼 지정. 나머지는 0으로 할당
	for (int i = 0; i < dimension; ++i)
	{
		m_vecData[i].Resize(dimension); // 4x4 정사각 행렬의 경우 각 열을 4번씩 반복하여 Resize를 할경우
		// 16개의 실수형 정보가 들어갈 수 있는 벡터공간이 할당된다.
	}
}

int matrix::Dimension()
{
	return m_vecData.size(); // 열의 최대크기를 반환한다.
}

matrix matrix::Identity(int dimension) //(0,0), (1,1), (2,2), (3,3) 인식하여 초기화
{
	matrix matRet(dimension); // dimension x dimension 만큼의 행렬을 할당하였다.

	for (int i = 0; i < dimension; ++i)
	{
		for (int j = 0; j < dimension; ++j)
		{
			matRet[i][j] = (i == j) ? 1 : 0; // 4 x 4 기준으로 (0,0), (1,1), (2,2), (3,3)에 1이 할당될것이다.
		}
	}


	return matRet;
}

matrix::row & matrix::operator[](int index)
{
	return m_vecData[index]; // index번째 행을 반환한다.
}

bool matrix::operator==(matrix & mat)
{
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			if ((*this)[i][j] - EPSILON > mat[i][j])
				return false;
			if ((*this)[i][j] + EPSILON < mat[i][j])
				return false;
		}
	}
	return false;
}

bool matrix::operator!=(matrix & mat)
{
	return !((*this) == mat);
}

matrix matrix::operator+(matrix & mat)
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] += mat[i][j];
		}
	}

	return matRet;
}

matrix matrix::operator-(matrix & mat)
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] -= mat[i][j];
		}
	}

	return matRet;
}

matrix matrix::operator*(matrix & mat)
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = 0.0f; // 일단 초기화

			for (int k = 0; k < Dimension(); ++k)
			{
				mat[i][j] = (*this)[i][k] * mat[k][j]; // 행렬간의 곱에서는 행과 열을 곱해야한다.
			}
		}
	}

	return matRet;
}

matrix matrix::operator*(float f)
{
	matrix matRet(Dimension());
	
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] *= f;
		}
	}



	return matRet;
}

matrix matrix::Transpose()
{
	matrix matRet(Dimension());
	
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}

	return matRet;
}

matrix matrix::Inverse(OUT float & determinent)
{
	matrix matRet = matrix::Identity(Dimension());
	determinent = Determinent();

	return matrix();
}

float matrix::Determinent()
{
	if (Dimension() == 2)
	{
		return ( (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0] );
	}

	float det = 0.0f;
	for (int i = 0; i < Dimension(); ++i)
	{
		det += (*this)[i][0];
	}

	return det;
}

matrix matrix::Adjoint()
{
	return matrix();
}

float matrix::getCofactor(int row, int col)
{
	return 0.0f;
}

float matrix::getMinor(int row, int col)
{
	// row, col 제외하고 한 차수 낮은 행렬로 변환
	// 변환된 행렬의 Determinent 리턴

	int dimension = Dimension();
	matrix matMinor(dimension - 1);

	int rowMinor = 0;
	int colMinor = 0;
	
	for (int i = 0; i < dimension; ++i)
	{
		if (i == row)
			continue;

		colMinor = 0;
		for (int j = 0; j < dimension; ++j)
		{
			if (j == col)
				continue;

			matMinor[rowMinor][colMinor] = (*this)[i][j];
			colMinor++;
		}
		rowMinor++;
	}

	return matMinor.Determinent(); // Dimension이 2가 될떄까지 계속 호출되겠지...
}

void matrix::Print()
{
}
