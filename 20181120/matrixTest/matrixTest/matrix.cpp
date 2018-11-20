#include "stdafx.h"
#include "matrix.h"


matrix::row::row()
{
}

matrix::row::~row()
{
}

void matrix::row::Resize(int dimension)
{
	m_vecData.resize(dimension);
}

float& matrix::row::operator[](int index)
{
	return m_vecData[index];
}


matrix::matrix()
{
}

matrix::matrix(int dimension)
{
	Resize(dimension);
}


matrix::~matrix()
{
}

void matrix::Resize(int dimension)
{
	m_vecData.resize(dimension);
	for (int i = 0; i < dimension; i++)
	{
		m_vecData[i].Resize(dimension);
	}
}

int matrix::Dimension()
{
	return (int)m_vecData.size();
}

//main()
//{
//	matrix mat;
//	mat.identity();
//
//	matrix::identity();
//}

matrix matrix::Identity(int dimension)
{
	matrix matRet(dimension);
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			//if (i == j)
			//	matRet[i][j] = 1;
			//else
			//	matRet[i][j] = 0;

			matRet[i][j] = (i == j) ? 1 : 0;
		}
	}

	return matRet;
}

matrix::row & matrix::operator[](int index)
{
	return m_vecData[index];
}

bool matrix::operator==(matrix & mat)
{
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			if ((*this)[i][j] - EPSILON > mat[i][j])
				return false;
			if ((*this)[i][j] + EPSILON < mat[i][j])
				return false;
		}
	}

	return true;
}

bool matrix::operator!=(matrix & mat)
{
	return !((*this) == mat);
}

matrix matrix::operator+(matrix & mat)
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}

	return matRet;
}

matrix matrix::operator-(matrix & mat)
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}

	return matRet;
}

matrix matrix::operator*(matrix & mat)
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = 0.0f;

			for (int k = 0; k < Dimension(); k++)
			{
				matRet[i][j] += (*this)[i][k] * mat[k][j];
			}
		}
	}

	return matRet;
}

matrix matrix::operator*(float f)
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] * f;
		}
	}

	return matRet;
}

matrix matrix::Transpose()
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}

	return matRet;
}

matrix matrix::Inverse(OUT float & determinent)
{
	// mat-1 = 1/(Determinent()) * Adjoint();
	//determinent = Determinent();

	matrix matRet = matrix::Identity(Dimension());
	determinent = Determinent();
	if (-EPSILON < determinent && determinent < EPSILON)
		return matRet;

	matrix matAdj = Adjoint();
	matRet = matAdj * (1 / determinent);

	return matRet;
}

float matrix::Determinent()
{
	// 2x2 ad - bc
	// det += mat(i0) * cofactor(i0)

	if (Dimension() == 2)
	{
		return ( (*this)[0][0] * (*this)[1][1]
			- (*this)[0][1] * (*this)[1][0] );
	}
	
	float det = 0.0f;
	for (int i = 0; i < Dimension(); i++) // 하나의 행을 기준으로 검사
	{
		det += ((*this)[i][0] * Cofactor(i, 0));
	}

	return det;
}

matrix matrix::Adjoint()
{
	// Cofactor 값을 이용한 행렬계산
	// 계산된 행렬을 전치

	int dimension = Dimension();
	matrix matRet = matrix::Identity(dimension);

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			matRet[i][j] = Cofactor(j, i);
		}
	}

	return matRet;
}

float matrix::Cofactor(int row, int col)
{
	// -1^(i+j) * Minor(i, j)
	int sign = 1;
	if ((row + col) % 2 != 0) // 대각선 라인이 아닐경우
		sign = -1;

	return sign * Minor(row, col);
}

float matrix::Minor(int row, int col)
{
	// row, col 제외하고 한 차수 낮은 행렬로 변환
	// 변환된 행렬의 Determinet() 리턴

	int dimension = Dimension();
	matrix matMinor(dimension - 1);

	int rowMinor = 0;
	int colMinor = 0;

	for (int i = 0; i < dimension; i++)
	{
		if (i == row)
			continue;

		colMinor = 0;
		for (int j = 0; j < dimension; j++)
		{
			if (j == col)
				continue;

			matMinor[rowMinor][colMinor] = (*this)[i][j];
			colMinor++;
		}
		rowMinor++;
	}

	return matMinor.Determinent();
}

void matrix::Print()
{
	int dimension = Dimension();
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			//cout << (*this)[i][j] << " ";
			printf("%8.2f", (*this)[i][j]);			
		}
		cout << endl;
	}
	cout << endl;
}

