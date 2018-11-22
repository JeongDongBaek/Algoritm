#pragma once
#include "vector3.h"
#include "matrix.h"

struct tagVertex
{
	vector3 v1;
	vector3 v2;
	vector3 v3;
};

struct MyStruct
{

};


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

	// Local Space
	matrix m_matLocal;

	// World Space
	matrix	m_matWorld;
	// View Space
	matrix	m_matView;
	// Projection
	matrix	m_matProj;
	// Viewport
	matrix	m_matViewport;

	tagVertex vertex;


	// Camera 기본 정보
	vector3 m_vEye;
	vector3 m_vLookAt;
	vector3 m_vUp;




	// Vector3 Grid////////////
	vector<vector3>		m_vecGridX;
	vector<DWORD>		m_vecGridXIndex;

	vector<vector3>		m_vecGridY;
	vector<DWORD>		m_vecGridYIndex;

	vector<vector3>		m_vecGridZ;
	vector<DWORD>		m_vecGridZIndex;

	///////////
	vector<vector3>		m_vecGrid;




	// 이동 회전 관련//////////////
	float CurrX = 0.0f, CurrY = 0.0f, CurrZ = 0.0f;
	float RotCurrX = 0.0f, RotCurrY = 0.0f, RotCurrZ = 0.0f;

	float m_fSpeed = 0.1f;

	vector3 m_vPos;
	vector3 m_vDir;

public:
	void Setup();

	void Update();
	bool KeyInput(int key);

	void Render(HDC hdc);

	void SetGrid();
	void RenderGrid(HDC hdc);


	void CameraCheck(vector3 v1, vector3 v2);
	void CrossOrDot(bool isThanRight);
};

