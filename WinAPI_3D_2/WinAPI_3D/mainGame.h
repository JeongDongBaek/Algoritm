#pragma once
#include "vector3.h"
#include "matrix.h"

class mainGame
{
public:
	mainGame();
	~mainGame();

private:
	HDC		m_memDC;
	HBITMAP	m_hOldBitmap, m_hBitmap;

	// Local Space 좌표
	vector<vector3>		m_vecVertex;
	vector<DWORD>		m_vecIndex;

	// World Space
	matrix	m_matWorld;
	// View Space
	matrix	m_matView;
	// Projection
	matrix	m_matProj;
	// Viewport
	matrix	m_matViewport;

	// Camera 기본 정보
	vector3 m_vEye;
	vector3 m_vLookAt;
	vector3 m_vUp;

public:
	void Setup();
	void Update();
	void Render(HDC hdc);
};

