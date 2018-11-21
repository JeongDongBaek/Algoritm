#pragma once
#include "vector3.h"
#include "matrix.h"
#include "WinAPI_3D.h"

class mainGame
{
public:
	mainGame();
	~mainGame();

	typedef struct tagImageInfo
	{
		HDC		hMemDC;	// 화면에 점, 선, 도형 등을 그릴 때 필요한 정보를 저장하는 객체
						// 그림을 그릴 때 필요한 메모리 공간 할당(도화지 개념)
		HBITMAP	hBitmap;	// 이미지파일 로드에 사용되는 객체
		HBITMAP hOldBitmap;
		int		nWidth;		// 이미지 너비
		int		nHeight;	// 이미지 높이

		// 애니메이션을 위한 추가변수
		float	fX;
		float	fY;
		int		nCurrFrameX;
		int		nCurrFrameY;
		int		nMaxFrameX;
		int		nMaxFrameY;
		int		nFrameWidth;
		int		nFrameHeight;

		tagImageInfo()
		{
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBitmap = NULL;
			nWidth = 0;
			nHeight = 0;

			fX = 0;
			fY = 0;
			nCurrFrameX = 0;
			nCurrFrameY = 0;
			nMaxFrameX = 0;
			nMaxFrameY = 0;
			nFrameWidth = 0;
			nFrameHeight = 0;
		}

		//void init();

		//~tagImageInfo() {}
	} IMAGE_INFO, *LPIMAGE_INFO;
	LPIMAGE_INFO m_pBackBuffer;


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

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

