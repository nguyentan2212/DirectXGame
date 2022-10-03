#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include "Texture.h"
#include "../Utils/Property.h"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)

class Graphic
{
public:
	static Graphic* GetInstance();
	void Init(HWND hwnd, int fps);
	Texture* CreateTexture(LPCWSTR texturePath);
	void BeginRender();
	void EndRender();

#pragma region Properties
	R_PROPERTY(int, backBufferWidth);
	GET(backBufferWidth) { return this->_backBufferWidth; }

	R_PROPERTY(int, backBufferHeight);
	GET(backBufferHeight) { return this->_backBufferHeight; }

	R_PROPERTY(LPD3DX10SPRITE, spriteHandler);
	GET(spriteHandler) { return this->_spriteObject; }
#pragma endregion

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
	LPD3DX10SPRITE _spriteObject = NULL;

	Graphic();
	~Graphic();
	static Graphic* _instance;
};

