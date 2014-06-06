
#include "stdafx.h"
#include "Renderer.h"
#include "../base/DxInit.h"
#include "resourcemanager.h"

using namespace graphic;


// ������ �ʱ�ȭ.
bool graphic::InitRenderer(HWND hWnd, const int width, const int height)
{
	if (!cRenderer::Get()->CreateDirectX(hWnd, width, height))
		return false;

	return true;
}

void graphic::ReleaseRenderer()
{
	cRenderer::Release();
	cResourceManager::Release();
}



////////////////////////////////////////////////////////////////////////////////////////////////
// Renderer

cRenderer::cRenderer()
{

}

cRenderer::~cRenderer()
{

}


// DirectX Device ��ü ����.
bool cRenderer::CreateDirectX(HWND hWnd, const int width, const int height)
{
	if (!InitDirectX(hWnd, width, height, m_pDevice))
		return false;

	return true;
}

