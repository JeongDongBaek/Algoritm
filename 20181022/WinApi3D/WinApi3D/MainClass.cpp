#include "stdafx.h"
#include "MainClass.h"
#include "image.h"


void MainClass::setBackBufffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

MainClass::MainClass()
{
}


MainClass::~MainClass()
{
}
