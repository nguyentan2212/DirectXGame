#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include "Texture.h"
#include "../Utils/Property.h"

#define BACKGROUND_COLOR D3DXCOLOR(175.0f/255, 249.0f/255, 240.0f/255, 0.0f)

struct vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR4 color;

	vertex(D3DXVECTOR3 p, D3DXVECTOR4 c)
	{
		pos = p;
		color = c;
	}
};

class Graphic
{
public:
	static Graphic* GetInstance();
	void Init(HWND hwnd, int fps);
	Texture* CreateTexture(LPCWSTR texturePath);
	void Begin();
	void BeginSprite();
	void EndSprite();
	void End();

	void DrawBox(float x, float y, float w, float h);

#pragma region Properties
	R_PROPERTY(int, backBufferWidth);
	GET(backBufferWidth) { return this->_backBufferWidth; }

	R_PROPERTY(int, backBufferHeight);
	GET(backBufferHeight) { return this->_backBufferHeight; }

	R_PROPERTY(LPD3DX10SPRITE, spriteHandler);
	GET(spriteHandler) { return this->_spriteObject; }

	PROPERTY(D3DXVECTOR2, cameraPosition);
	GET(cameraPosition) { return this->_cameraPosition; }
	SET(cameraPosition) { this->_cameraPosition = value; }
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
	ID3D10RasterizerState* _pRS;

	//input layout and vertex buffer
	ID3D10Buffer* _pVertexBuffer;
	ID3D10InputLayout* _pVertexLayout;
	ID3D10Buffer* _pIndexBuffer;

	//effects and techniques
	ID3D10Effect* _pBasicEffect;
	ID3D10EffectTechnique* _pBasicTechnique;

	//technique desc
	D3D10_TECHNIQUE_DESC _techDesc;

	D3DXMATRIX _matProjection;
	D3DXVECTOR2 _cameraPosition;

	void CreateSwapChain(HWND hwnd, int fps);
	void CreateRenderTarget();
	void CreateViewPortAndSpriteObject();
	void CreateRasterizerState();
	void CreateBlendState();
	void CreateVertexAndIndexBuffer();

	Graphic();
	~Graphic();
	static Graphic* _instance;
};

