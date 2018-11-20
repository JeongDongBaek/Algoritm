#include "stdafx.h"
#include "vector3.h"
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
	return matrix();
}

float matrix::Determinent()
{
	return 0.0f;
}

matrix matrix::Adjoint()
{
	return matrix();
}

float matrix::Cofactor(int row, int col)
{
	return 0.0f;
}

float matrix::Minor(int row, int col)
{
	return 0.0f;
}

matrix matrix::Translation(float x, float y, float z)
{
	return matrix();
}

matrix matrix::Translation(vector3 & v)
{
	return matrix();
}

matrix matrix::RotationX(float angle)
{
	return matrix();
}

matrix matrix::RotationY(float angle)
{
	return matrix();
}

matrix matrix::RotationZ(float angle)
{
	return matrix();
}

matrix matrix::View(vector3 & eye, vector3 & lookAt, vector3 & up)
{
	vector3 zAxis = (lookAt - eye).Normalize();
	vector3 xAxis = vector3::Cross(up, zAxis).Normalize();
	vector3 yAxis = vector3::Cross(zAxis, xAxis).Normalize();

	matrix matRet = matrix::Identity(4);
	matRet[0][0] = xAxis.x; matRet[0][1] = yAxis.x; matRet[0][2] = zAxis.x;
	matRet[1][0] = xAxis.y; matRet[1][1] = yAxis.y; matRet[1][2] = zAxis.y;
	matRet[2][0] = xAxis.z; matRet[2][1] = yAxis.z; matRet[2][2] = zAxis.z;

	matRet[3][0] = -vector3::Dot(xAxis, eye);
	matRet[3][1] = -vector3::Dot(yAxis, eye);
	matRet[3][2] = -vector3::Dot(zAxis, eye);

	return matRet;
}

matrix matrix::Projection(float fovY, float aspect, float nearZ, float farZ)
{
	return matrix();
}

matrix matrix::Viewport(float x, float y, float width, float height, float minZ, float maxZ)
{
	return matrix();
}
