#include "stdafx.h"
#include "mainGame.h"


char str[100];

mainGame::mainGame()
	: m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_vEye(0, 10, -10)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vDir(0, 0, 1)
	, m_vPos(0, 0, 0)
{
}


mainGame::~mainGame()
{
	// bitmap ����
	SelectObject(m_memDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);

	// memDC ����
	DeleteDC(m_memDC);
}

void mainGame::Setup()
{
	// Winapi�� �̿��� �׸��� ���� �غ�
	// memDC ����
	HDC hdc = GetDC(g_hWnd);
	m_memDC = CreateCompatibleDC(hdc);
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	
	// ��Ʈ�� ����
	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	m_hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBitmap);



	ReleaseDC(g_hWnd, hdc);

	// vertex ����
	m_vecVertex.resize(8);
	m_vecVertex[0] = vector3(-1.0f, -1.0f, -1.0f);
	m_vecVertex[1] = vector3(-1.0f, 1.0f, -1.0f);
	m_vecVertex[2] = vector3(1.0f, 1.0f, -1.0f);
	m_vecVertex[3] = vector3(1.0f, -1.0f, -1.0f);

	m_vecVertex[4] = vector3(-1.0f, -1.0f, 1.0f);
	m_vecVertex[5] = vector3(-1.0f, 1.0f, 1.0f);
	m_vecVertex[6] = vector3(1.0f, 1.0f, 1.0f);
	m_vecVertex[7] = vector3(1.0f, -1.0f, 1.0f);


	//////////////////////
	m_vecGridX.resize(10);
	
	m_vecGridX[0] = vector3(5.0f, 1.0f, 10.0f);
	m_vecGridX[1] = vector3(5.0f, 1.0f, -10.0f);
								  
	m_vecGridX[2] = vector3(4.0f, 1.0f, 10.0f);
	m_vecGridX[3] = vector3(4.0f, 1.0f, -10.0f);
								  
	m_vecGridX[4] = vector3(3.0f, 1.0f, 10.0f);
	m_vecGridX[5] = vector3(3.0f, 1.0f, -10.0f);
								  
	m_vecGridX[6] = vector3(2.0f, 1.0f, 10.0f);
	m_vecGridX[7] = vector3(2.0f, 1.0f, -10.0f);
								  
	m_vecGridX[8] = vector3(1.0f, 1.0f, 10.0f);
	m_vecGridX[9] = vector3(1.0f, 1.0f, -10.0f);
	///////////////////////////






	// index ���� // Ǫ������ ������ ����� ������? �ִ�
	m_vecIndex.reserve(36);
	// �ո�
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(0);

	// �޸� 
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);

	// ��
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);

	// ��
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);

	// ��
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);

	// ��
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);

	

	matrix matT = matrix::Translation(0.0f, 0.0f, 0.0f);
	matrix matRotx = matrix::RotationX(PI / 6);
	//m_matWorld = m_matWorld * matRotx;

	// View Space
	m_matView = matrix::View(m_vEye, m_vLookAt, m_vUp);

	// Projection Space
	m_matProj = matrix::Projection(PI / 4, rc.right / (float)rc.bottom,
		1.0f, 1000.0f);  // ī�޶� �������� �� ����ü�� �Ÿ��� ũ��

	// ViewPort
	m_matViewport = matrix::Viewport(0, 0, rc.right, rc.bottom, 0.0f, 1.0f); // ���� ���͸� ������� ������ �����Ұ��ΰ� : ���� ������ ���̴�. 

	SetGrid();
}
void mainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);


	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		CameCheck();

	}







	// 
	if (KeyInput('A'))
	{
		RotCurrY -= m_fSpeed;
	}
	else if (KeyInput('D'))
	{
		RotCurrY += m_fSpeed;
	}


	// ȸ����� ���� �ٶ󺸴� ���� ȸ��
	m_vDir = vector3(0, 0, 1);
	matrix matR = matrix::RotationY(RotCurrY);
	m_vDir = vector3::TransformNormal(m_vDir, matR);
	if (KeyInput('W'))
	{
		vector3 vMove = (m_vDir * m_fSpeed);
		m_vPos = m_vPos + vMove;
	}
	else if (KeyInput('S'))
	{
		vector3 vMove = (m_vDir * m_fSpeed);
		m_vPos = m_vPos - vMove;
	}



	// World Space
	// x�� �������� 5��ŭ �̵�, x�� �������� 30����ŭ ȸ��



	// World Space
	matrix matT = matrix::Translation(m_vPos);

	m_matWorld = matR * matT; // * matRotationY;

	m_vEye = vector3(0, 10, -10);
	m_vEye = vector3::TransformNormal(m_vEye, matR);
	m_vEye = m_vEye + m_vPos;
	m_vLookAt = m_vPos;



	// View Space
	m_matView = matrix::View(m_vEye, m_vLookAt, m_vUp);

	// Projection Space
	m_matProj = matrix::Projection(PI / 4, rc.right / (float)rc.bottom,
		1.0f, 1000.0f);  // ī�޶� �������� �� ����ü�� �Ÿ��� ũ��

	// ViewPort
	m_matViewport = matrix::Viewport(0, 0, rc.right, rc.bottom, 0.0f, 1.0f); // ���� ���͸� ������� ������ �����Ұ��ΰ� : ���� ������ ���̴�. 







}

bool mainGame::KeyInput(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;


	return false;

}

void mainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	PatBlt(m_memDC, 0, 0, rc.right, rc.bottom, WHITENESS);

	RenderGrid(m_memDC);



	for (int i = 0; i < m_vecIndex.size(); i += 3)
	{
		vertex.v1 = m_vecVertex[m_vecIndex[i]];
		vertex.v2 = m_vecVertex[m_vecIndex[i + 1]];
		vertex.v3 = m_vecVertex[m_vecIndex[i + 2]];


		matrix matWVPVP = m_matWorld * m_matView * m_matProj * m_matViewport;
		vertex.v1 = vector3::TransformCoord(vertex.v1, matWVPVP);
		vertex.v2 = vector3::TransformCoord(vertex.v2, matWVPVP);
		vertex.v3 = vector3::TransformCoord(vertex.v3, matWVPVP);

		MoveToEx(m_memDC, vertex.v1.x, vertex.v1.y, NULL);
		LineTo(m_memDC, vertex.v2.x, vertex.v2.y);
		LineTo(m_memDC, vertex.v3.x, vertex.v3.y);
		LineTo(m_memDC, vertex.v1.x, vertex.v1.y);


		sprintf_s(str, 18, "v1");
		TextOut(m_memDC, vertex.v1.x, vertex.v1.y, str, strlen(str));

		sprintf_s(str, 18, "v2");
		TextOut(m_memDC, vertex.v2.x, vertex.v2.y, str, strlen(str));

		sprintf_s(str, 18, "v3");
		TextOut(m_memDC, vertex.v3.x, vertex.v3.y, str, strlen(str));
	}
	
	


	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_memDC, 0, 0, SRCCOPY);
}

void mainGame::SetGrid()
{

	int nNum = 10;
	float m_fInterVal = 1.0f;
	float fMin = -nNum * m_fInterVal;
	float fMax =  nNum * m_fInterVal;
	for (int i = 1; i <= nNum; ++i)
	{
		m_vecGrid.push_back(vector3(fMin, 0.0f, i * m_fInterVal));
		m_vecGrid.push_back(vector3(fMax, 0.0f, i * m_fInterVal)); // height ����

		m_vecGrid.push_back(vector3(fMin, 0.0f, -i * m_fInterVal));
		m_vecGrid.push_back(vector3(fMax, 0.0f, -i * m_fInterVal)); // height ����



		m_vecGrid.push_back(vector3(i * m_fInterVal, 0.0f, fMin));
		m_vecGrid.push_back(vector3(i * m_fInterVal, 0.0f, fMax)); // height ����

		m_vecGrid.push_back(vector3(-i * m_fInterVal, 0.0f, fMin));
		m_vecGrid.push_back(vector3(-i * m_fInterVal, 0.0f, fMax)); // height ����
	}

	


	m_vecGrid.push_back(vector3(0.0f, 0.0f, fMin));
	m_vecGrid.push_back(vector3(0.0f, 0.0f, fMax));

	m_vecGrid.push_back(vector3(fMin, 0.0f, 0.0f));
	m_vecGrid.push_back(vector3(fMax, 0.0f, 0.0f));

}

void mainGame::RenderGrid(HDC hdc)
{

	matrix matVPVP = m_matView * m_matProj * m_matViewport;

	vector3 v1, v2;
	for (int i = 0; i < m_vecGrid.size(); i += 2)
	{
		v1 = m_vecGrid[i];
		v2 = m_vecGrid[i+1];

		v1 = vector3::TransformCoord(v1, matVPVP);
		v2 = vector3::TransformCoord(v2, matVPVP);

		MoveToEx(hdc, v1.x, v1.y, NULL);
		LineTo(hdc, v2.x, v2.y);
	}
}


void mainGame::CameraCheck(vector3 v1, vector3 v2)
{
	matrix temp = vector3::Dot(v1, v2);
	

}


void mainGame::CrossOrDot(bool isThanRight)
{

}
