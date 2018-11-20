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
{ // 4 x 4 ����� �����Ͽ� 4�� ���ٰ� ����
	row::m_vecData.resize(dimension); // float�� ������ 4�� ���� ���Ͱ� �����������
} 


// �ּҰ��� �ѱ��.
float & Matrix::row::operator[](int index)
{
	return row::m_vecData[index]; // float& �̴ϱ� ���۷����� �Ѱ��شٴ� ��. �޴� ������ �̰��� ��Ī���� �� �� �ִ�.
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
	//����ƽ �Լ��� Ŭ������ �Լ� ��ü�� ȣ���ϸ�ȴ�. ex)
	//// main()
	//{
	//	matrix mat;
	//	mat.indentity; < -�̰��� �Ϲ����� �Լ�ȣ��
	//	matrix::identity; �䷸�� �ؾ��Ѵ�

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

	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
}

bool Matrix::operator==(Matrix & mat)
{
	// ������ ���ƾ��ϸ� ������ ���� ���ƾ��Ѵ�. ���⼭ ������ ������ 4�̹Ƿ� �н�

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

Matrix Matrix::TransPose() // ��ġ���
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
	Matrix matRet = Matrix::Identity(Dimension());
	determinant = Determinent();
	
	if (-EPSILON < determinant && determinant < EPSILON)
		return matRet;

	Matrix matAdj = Adjoint();
	matRet = matAdj * (1 / determinant);

	return matRet;

}

float Matrix::Determinent()
{
	// ad -bc

	
	if (Dimension() == 2)
	{
		return ((*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0]);
	}

	float det = 0.0f;
	for (int i = 0; i < Dimension(); ++i)
	{
		det += ((*this)[i][0] * getCofactor(i, 0));
	}
	
	return det;
}

Matrix Matrix::Adjoint()
{


	int dimension = Dimension();
	Matrix matRet = Matrix::Identity(Dimension());

	for (int i = 0; i < dimension; ++i)
	{
		for (int j = 0; j < dimension; ++j) // ���簢 ����̹Ƿ�
		{
			matRet[i][j] = getCofactor(i, j);
		}
	}


	return Matrix();
}

float Matrix::getCofactor(int row, int col)
{
	// - 1^(i + j ) * Minor(i, j )
	int sign = 1;
	if ((row + col) % 2 != 0)
		sign = -1;

	return sign * getMinor(row, col);




	return 0.0f;
}

float Matrix::getMinor(int row, int col) // 4 x 4 ����̶�� �����Ѵ�.
{
	// row , col �����ϰ� �� ���� ���� ��ķ� ��ȯ�Ѵ�.
	// ��ȯ�� ����� Determinent() ����

	int dimension = Dimension();
	Matrix metMinor(Dimension() - 1);
	
	int rowMinor = 0;
	int colMinor = 0;

	for (int i = 0; i < dimension; ++i)
	{
		if (i == row)
			continue;

		for (int j = 0; j < dimension; ++j)
		{
			if (j == col)
				continue;

			metMinor[rowMinor][colMinor] = (*this)[i][j];
			colMinor++;
		}
		rowMinor++;
	}


	return 0.0f;
}


void Matrix::Print()
{







}

