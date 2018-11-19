#pragma once

class image;

class MainClass
{
	HDC hdc;
	
	image * m_pBackBuffer;
	void setBackBufffer();
	
	char m_szText[128];



public:
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


	MainClass();
	~MainClass();
};

