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

float Matrix::getMinor(int row, int col) // 4 x 4 ����̶�� �����Ѵ�.
{
	Matrix temp;

	for (int i = 0; i < Determinent(); ++i)
	{
		for (int j = 0; j < Determinent(); ++j)
		{
			if (i == row || j == col) continue; // �ش�Ǵ� ��� ���� ���ܵȴ�.
			
			temp.m_vecData
		}
	}


	return 0.0f;
}


