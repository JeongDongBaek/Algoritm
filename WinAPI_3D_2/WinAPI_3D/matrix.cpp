#include "stdafx.h"
#include "matrix.h"
#include "vector3.h"

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

matrix matrix::Inverse(OUT float& fDeterminant)
{
	matrix matRet = matrix::Identity(Dimension());

	fDeterminant = Determinent();
	if (-0.0001f < fDeterminant && fDeterminant < 0.0001f)
		return matRet; 

	matrix matAdj = Adjoint();
	matRet = matAdj * (1 / fDeterminant);
	return matRet;
}

float matrix::Determinent()
{
	if (Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
	}

	float fDeterminant = 0.0f;

	for (int i = 0; i < Dimension(); ++i)
	{
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));
	}

	return fDeterminant;
}

matrix matrix::Adjoint()
{
	matrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = Cofactor(j, i);
		}
	}
	return matRet;
}

float matrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;

	if ((nRow + nCol) % 2 != 0)
		nConst = -1;

	return nConst * Minor(nRow, nCol);
}

float matrix::Minor(int nRow, int nCol)
{
	matrix matMinor(Dimension() - 1);

	int nMinorRow = 0;
	int nMinorCol = 0;

	for (int i = 0; i < Dimension(); ++i)
	{
		if (nRow == i)
			continue;

		nMinorCol = 0;

		for (int j = 0; j < Dimension(); ++j)
		{
			if (nCol == j)
				continue;
			matMinor[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}

	return matMinor.Determinent();
}

matrix matrix::Translation(float x, float y, float z)
{
	matrix matRet = matrix::Identity(4);

	matRet[3][0] = x;
	matRet[3][1] = y;
	matRet[3][2] = z;

	return matRet;
}

matrix matrix::Translation(vector3 & v)
{
	matrix matRet = matrix::Identity(4);

	matRet[3][0] = v.x;
	matRet[3][1] = v.y;
	matRet[3][2] = v.z;

	return matRet;
}

matrix matrix::RotationX(float angle)
{
	matrix matRet = matrix::Identity(4);

	matRet[1][1] = cosf(angle);
	matRet[1][2] = sinf(angle);
	matRet[2][1] = -sinf(angle);
	matRet[2][2] = cosf(angle);

	return matRet;
}

matrix matrix::RotationY(float angle)
{
	matrix matRet = matrix::Identity(4);

	matRet[0][0] = cosf(angle);
	matRet[0][2] = -sinf(angle);
	matRet[2][0] = sinf(angle);
	matRet[2][2] = cosf(angle);

	return matRet;
}

matrix matrix::RotationZ(float angle)
{
	matrix matRet = matrix::Identity(4);

	matRet[0][0] = cosf(angle);
	matRet[0][1] = sinf(angle);
	matRet[1][0] = -sinf(angle);
	matRet[1][1] = cosf(angle);

	return matRet;
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
	matrix matRet = matrix::Identity(4);

	float scaleX = 1.0f / tanf(fovY / 2.0f);
	float scaleY = scaleX / aspect;

	matRet[0][0] = scaleX;
	matRet[1][1] = scaleY;
	matRet[2][2] = farZ / (farZ - nearZ);
	matRet[2][3] = 1.0f;
	matRet[3][2] = (-nearZ * farZ) / (farZ - nearZ);
	matRet[3][3] = 0.0f;

	return matRet;
}

matrix matrix::Viewport(float x, float y, float width, float height, float minZ, float maxZ)
{
	matrix matRet = matrix::Identity(4);

	matRet[0][0] = width / 2.0f;
	matRet[1][1] = -height / 2.0f;
	matRet[2][2] = maxZ - minZ;
	matRet[3][0] = x + width / 2.0f;
	matRet[3][1] = y + height / 2.0f;
	matRet[3][2] = minZ;

	return matRet;
}
