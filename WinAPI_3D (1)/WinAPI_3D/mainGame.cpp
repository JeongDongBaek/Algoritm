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

	HDC hdc = GetDC(g_hWnd);
	m_memDC = CreateCompatibleDC(hdc);

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


	// WinAPI를 이용한 그리기 위한 준비
	m_pBackBuffer = new IMAGE_INFO;

	// memDC 생성

	// 비트맵 생성
}

void mainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, false);
}

void mainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	PatBlt(m_memDC, 0, 0, rc.right, rc.bottom, WHITENESS);

	MoveToEx(m_memDC, 700.0f, 200.0f, NULL);
}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		//case WM_MOUSEHWHEEL:
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:	
		PAINTSTRUCT ps;
		m_memDC = BeginPaint(hWnd, &ps);
		this->Render(m_memDC);
		EndPaint(hWnd, &ps);
	break;
	}


	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
