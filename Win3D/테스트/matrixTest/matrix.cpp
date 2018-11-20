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



void matrix::Resize(int dimension) // ���� ���� �Ҵ��ϸ� �� �ȿ��� ���� ũ�⸸ŭ �� ���� �Ҵ��Ѵ�. 
{
	m_vecData.resize(dimension); // ���� �ִ�ũ�⸦ dimension��ŭ ����. �������� 0���� �Ҵ�
	for (int i = 0; i < dimension; ++i)
	{
		m_vecData[i].Resize(dimension); // 4x4 ���簢 ����� ��� �� ���� 4���� �ݺ��Ͽ� Resize�� �Ұ��
		// 16���� �Ǽ��� ������ �� �� �ִ� ���Ͱ����� �Ҵ�ȴ�.
	}
}

int matrix::Dimension()
{
	return m_vecData.size(); // ���� �ִ�ũ�⸦ ��ȯ�Ѵ�.
}

matrix matrix::Identity(int dimension) //(0,0), (1,1), (2,2), (3,3) �ν��Ͽ� �ʱ�ȭ
{
	matrix matRet(dimension); // dimension x dimension ��ŭ�� ����� �Ҵ��Ͽ���.

	for (int i = 0; i < dimension; ++i)
	{
		for (int j = 0; j < dimension; ++j)
		{
			matRet[i][j] = (i == j) ? 1 : 0; // 4 x 4 �������� (0,0), (1,1), (2,2), (3,3)�� 1�� �Ҵ�ɰ��̴�.
		}
	}


	return matRet;
}

matrix::row & matrix::operator[](int index)
{
	return m_vecData[index]; // index��° ���� ��ȯ�Ѵ�.
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
			matRet[i][j] = 0.0f; // �ϴ� �ʱ�ȭ

			for (int k = 0; k < Dimension(); ++k)
			{
				mat[i][j] = (*this)[i][k] * mat[k][j]; // ��İ��� �������� ��� ���� ���ؾ��Ѵ�.
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
	// row, col �����ϰ� �� ���� ���� ��ķ� ��ȯ
	// ��ȯ�� ����� Determinent ����

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

	return matMinor.Determinent(); // Dimension�� 2�� �ɋ����� ��� ȣ��ǰ���...
}

void matrix::Print()
{
}
