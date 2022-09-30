#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include "Texture.h"

class Graphic
{
public:
	static Graphic* GetInstance();
	void Init(HWND hwnd, int fps);
	Texture* CreateTexture(LPCWSTR texturePath);

private:
	// Backbuffer width & height, will be set during Direct3D initialization
	int _backBufferWidth = 0;					
	int _backBufferHeight = 0;

	ID3D10Device* _pD3DDevice = NULL;
	IDXGISwapChain* _pSwapChain = NULL;
	ID3D10RenderTargetView* _pRenderTargetView = NULL;
	// To store alpha blending state
	ID3D10BlendState* _pBlendStateAlpha = NULL;			

	// Sprite handling object 
	ID3DX10Sprite* _spriteObject = NULL;	

	Graphic();
	~Graphic();
	static Graphic* _instance;
};

