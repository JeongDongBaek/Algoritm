#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
	: m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
{
}


mainGame::~mainGame()
{
	// bitmap 해제
	SelectObject(m_memDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);

	// memDC 해제
	DeleteDC(m_memDC);
}

void mainGame::Setup()
{
	// Winapi를 이용한 그리기 위한 준비
	// memDC 생성
	HDC hdc = GetDC(g_hWnd);
	m_memDC = CreateCompatibleDC(hdc);

	// 비트맵 셋팅
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	m_hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBitmap);

	ReleaseDC(g_hWnd, hdc);

	// vertex 설정
	m_vecVertex.resize(8);
	m_vecVertex[0] = vector3(-1.0f, -1.0f, -1.0f);
	m_vecVertex[1] = vector3(-1.0f,  1.0f, -1.0f);
	m_vecVertex[2] = vector3( 1.0f,  1.0f, -1.0f);
	m_vecVertex[3] = vector3( 1.0f, -1.0f, -1.0f);

	m_vecVertex[4] = vector3(-1.0f, -1.0f,  1.0f);
	m_vecVertex[5] = vector3(-1.0f,  1.0f,  1.0f);
	m_vecVertex[6] = vector3( 1.0f,  1.0f,  1.0f);
	m_vecVertex[7] = vector3( 1.0f, -1.0f,  1.0f);

	// index 설정
	m_vecIndex.reserve(36);
	// 앞면
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(0);

	// 뒷면
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(0);

	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(0);

	// 상


	// 하

	// 좌

	// 우
}

void mainGame::Update()
{
}

void mainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	PatBlt(m_memDC, 0, 0, rc.right, rc.bottom, WHITENESS);

	char str[100];
	sprintf_s(str, 100, "Hello, 3D World");
	TextOut(m_memDC, 100, 100, str, strlen(str));

	MoveToEx(m_memDC, 200, 150, NULL);
	LineTo(m_memDC, 300, 250);

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_memDC, 0, 0, SRCCOPY);
}
