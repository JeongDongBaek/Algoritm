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
		HDC		hMemDC;	// ȭ�鿡 ��, ��, ���� ���� �׸� �� �ʿ��� ������ �����ϴ� ��ü
						// �׸��� �׸� �� �ʿ��� �޸� ���� �Ҵ�(��ȭ�� ����)
		HBITMAP	hBitmap;	// �̹������� �ε忡 ���Ǵ� ��ü
		HBITMAP hOldBitmap;
		int		nWidth;		// �̹��� �ʺ�
		int		nHeight;	// �̹��� ����

		// �ִϸ��̼��� ���� �߰�����
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


	// Local Space ��ǥ
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

	// Camera �⺻ ����
	vector3 m_vEye;
	vector3 m_vLookAt;
	vector3 m_vUp;

public:

	void Setup();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

