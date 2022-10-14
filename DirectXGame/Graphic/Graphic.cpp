#include "Graphic.h"
#include "../Utils/Debug.h"

Graphic* Graphic::_instance = nullptr;

void Graphic::CreateSwapChain(HWND hwnd, int fps)
{
	// retrieve client area width & height so that we can create backbuffer height & width accordingly 
	RECT r;
	GetClientRect(hwnd, &r);

	this->_backBufferWidth = r.right + 1;
	this->_backBufferHeight = r.bottom + 1;

	// Create & clear the DXGI_SWAP_CHAIN_DESC structure
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Fill in the needed values
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = this->_backBufferWidth;
	swapChainDesc.BufferDesc.Height = this->_backBufferHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = fps;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// Create the D3D device and the swap chain
	HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL,
		D3D10_DRIVER_TYPE_REFERENCE,
		NULL,
		0,
		D3D10_SDK_VERSION,
		&swapChainDesc,
		&this->_pSwapChain,
		&this->_pD3DDevice);

	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] D3D10CreateDeviceAndSwapChain has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}
}

void Graphic::CreateRenderTarget()
{
	// Get the back buffer from the swapchain
	ID3D10Texture2D* pBackBuffer;
	HRESULT hr = this->_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] pSwapChain->GetBuffer has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	// create the render target view
	hr = this->_pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &this->_pRenderTargetView);

	pBackBuffer->Release();
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] CreateRenderTargetView has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	// set the render target
	this->_pD3DDevice->OMSetRenderTargets(1, &this->_pRenderTargetView, NULL);
}

void Graphic::CreateViewPortAndSpriteObject()
{
	// create and set the viewport
	D3D10_VIEWPORT viewPort;
	viewPort.Width = this->_backBufferWidth;
	viewPort.Height = this->_backBufferHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	this->_pD3DDevice->RSSetViewports(1, &viewPort);

	// Create the projection matrix using the values in the viewport
	
	D3DXMatrixOrthoOffCenterLH(&this->_matProjection,
		(float)viewPort.TopLeftX,
		(float)viewPort.Width,
		(float)viewPort.TopLeftY,
		(float)viewPort.Height,
		0.1f,
		10);

	// create the sprite object to handle sprite drawing 
	HRESULT hr = D3DX10CreateSprite(this->_pD3DDevice, 0, &this->_spriteObject);

	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] D3DX10CreateSprite has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}
	hr = this->_spriteObject->SetProjectionTransform(&this->_matProjection);
	
}

void Graphic::CreateRasterizerState()
{
	D3D10_RASTERIZER_DESC rasterizerState;

	rasterizerState.CullMode = D3D10_CULL_NONE;
	rasterizerState.FillMode = D3D10_FILL_SOLID;
	rasterizerState.FrontCounterClockwise = false;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = false;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = true;

	this->_pD3DDevice->CreateRasterizerState(&rasterizerState, &this->_pRS);
	this->_pD3DDevice->RSSetState(this->_pRS);
}

void Graphic::CreateBlendState()
{
	// Initialize the blend state for alpha drawing
	D3D10_BLEND_DESC StateDesc;
	ZeroMemory(&StateDesc, sizeof(D3D10_BLEND_DESC));
	StateDesc.AlphaToCoverageEnable = FALSE;
	StateDesc.BlendEnable[0] = TRUE;
	StateDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	StateDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	StateDesc.BlendOp = D3D10_BLEND_OP_ADD;
	StateDesc.SrcBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	StateDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	this->_pD3DDevice->CreateBlendState(&StateDesc, &this->_pBlendStateAlpha);
}

void Graphic::CreateVertexAndIndexBuffer()
{
	//Load Basic Effect and Technique 
	//--------------------------------------------------------------
	HRESULT hr = D3DX10CreateEffectFromFile(L"basic.fx",
		NULL, NULL,
		"fx_4_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		this->_pD3DDevice,
		NULL,
		NULL,
		&this->_pBasicEffect,
		NULL,
		NULL);
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] D3DX10CreateEffectFromFile has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	this->_pBasicTechnique = this->_pBasicEffect->GetTechniqueByName("Render");
	
	this->_pBasicTechnique->GetDesc(&_techDesc);
	//Create Input Layout
	//--------------------------------------------------------------	

	D3D10_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = 2;

	D3D10_PASS_DESC PassDesc;
	this->_pBasicTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
	hr = this->_pD3DDevice->CreateInputLayout(layout,
		numElements,
		PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize,
		&this->_pVertexLayout);

	// Set the input layout
	this->_pD3DDevice->IASetInputLayout(this->_pVertexLayout);

	//create vertex buffer (space for 100 vertices)
	//---------------------------------------------------------------------------------
	UINT numVertices = 100;

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(vertex) * numVertices;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	hr = this->_pD3DDevice->CreateBuffer(&bd, NULL, &this->_pVertexBuffer);
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] Create Vertex Buffer has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	bd.ByteWidth = sizeof(unsigned int) * numVertices;
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	hr = this->_pD3DDevice->CreateBuffer(&bd, NULL, &this->_pIndexBuffer);
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] Create Index Buffer has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	// Set vertex buffer
	UINT stride = sizeof(vertex);
	UINT offset = 0;
	this->_pD3DDevice->IASetVertexBuffers(0, 1, &this->_pVertexBuffer, &stride, &offset);
	this->_pD3DDevice->IASetIndexBuffer(this->_pIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
}

Graphic::Graphic()
{

}

Graphic* Graphic::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Graphic();
    }
    return _instance;
}

void Graphic::Init(HWND hwnd, int fps)
{
	CreateSwapChain(hwnd, fps);
	CreateRenderTarget();
	CreateViewPortAndSpriteObject();
	CreateRasterizerState();
	CreateBlendState();
	CreateVertexAndIndexBuffer();

	DebugOut((wchar_t*)L"[INFO] InitDirectX has been successful\n");
	return;
}

Texture* Graphic::CreateTexture(LPCWSTR texturePath)
{
	ID3D10Resource* pD3D10Resource = nullptr;
	ID3D10Texture2D* tex = nullptr;

	// Retrieve image information first 
	D3DX10_IMAGE_INFO imageInfo;
	HRESULT hr = D3DX10GetImageInfoFromFile(texturePath, NULL, &imageInfo, NULL);
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] D3DX10GetImageInfoFromFile failed for  file: %s with error: %d\n", texturePath, hr);
		return nullptr;
	}

	D3DX10_IMAGE_LOAD_INFO info;
	ZeroMemory(&info, sizeof(D3DX10_IMAGE_LOAD_INFO));
	info.Width = imageInfo.Width;
	info.Height = imageInfo.Height;
	info.Depth = imageInfo.Depth;
	info.FirstMipLevel = 0;
	info.MipLevels = 1;
	info.Usage = D3D10_USAGE_DEFAULT;
	info.BindFlags = D3DX10_DEFAULT;
	info.CpuAccessFlags = D3DX10_DEFAULT;
	info.MiscFlags = D3DX10_DEFAULT;
	info.Format = imageInfo.Format;
	info.Filter = D3DX10_FILTER_NONE;
	info.MipFilter = D3DX10_DEFAULT;
	info.pSrcInfo = &imageInfo;

	// Loads the texture into a temporary ID3D10Resource object
	hr = D3DX10CreateTextureFromFile(this->_pD3DDevice,
		texturePath,
		&info,
		NULL,
		&pD3D10Resource,
		NULL);

	// Make sure the texture was loaded successfully
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] Failed to load texture file: %s with error: %d\n", texturePath, hr);
		return nullptr;
	}

	// Translates the ID3D10Resource object into a ID3D10Texture2D object
	pD3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID*)&tex);
	pD3D10Resource->Release();

	if (!tex) {
		DebugOut((wchar_t*)L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
		return nullptr;
	}

	//
	// Create the Share Resource View for this texture 
	// 	   
	// Get the texture details
	D3D10_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	// Create a shader resource view of the texture
	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;

	// Clear out the shader resource view description structure
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));

	// Set the texture format
	SRVDesc.Format = desc.Format;

	// Set the type of resource
	SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;

	ID3D10ShaderResourceView* gSpriteTextureRV = nullptr;

	this->_pD3DDevice->CreateShaderResourceView(tex, &SRVDesc, &gSpriteTextureRV);

	DebugOut(L"[INFO] Texture loaded Ok from file: %s \n", texturePath);

	return new Texture(tex, gSpriteTextureRV);
}

void Graphic::Begin()
{
	this->_pD3DDevice->ClearRenderTargetView(this->_pRenderTargetView, BACKGROUND_COLOR);
	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	this->_pD3DDevice->OMSetBlendState(this->_pBlendStateAlpha, NewBlendFactor, 0xffffffff);
}

void Graphic::BeginSprite()
{
	this->_spriteObject->Begin(D3DX10_SPRITE_SORT_TEXTURE | D3DX10_SPRITE_SAVE_STATE);
}

void Graphic::EndSprite()
{
	this->_spriteObject->End();
}

void Graphic::End()
{
	this->_pSwapChain->Present(0, 0);
}

void Graphic::DrawBox(float x, float y, float w, float h)
{
	D3DXVECTOR2 topLeft(x, y);
	D3DXVECTOR2 pTopLeft;
	D3DXVec2TransformCoord(&pTopLeft, &topLeft, &this->_matProjection);

	D3DXVECTOR2 bottomRight(x + w, y + h);
	D3DXVECTOR2 pBottomRight;
	D3DXVec2TransformCoord(&pBottomRight, &bottomRight, &this->_matProjection);

	//fill vertex buffer with vertices
	UINT numVertices = 4;
	vertex* v = NULL;

	//lock vertex buffer for CPU use
	this->_pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&v);

	v[0] = vertex(D3DXVECTOR3(pTopLeft.x, pTopLeft.y, 0), D3DXVECTOR4(1, 0, 0, 1));
	v[1] = vertex(D3DXVECTOR3(pBottomRight.x, pTopLeft.y, 0), D3DXVECTOR4(1, 1, 0, 1));
	v[2] = vertex(D3DXVECTOR3(pBottomRight.x, pBottomRight.y, 0), D3DXVECTOR4(0, 1, 0, 1));
	v[3] = vertex(D3DXVECTOR3(pTopLeft.x, pBottomRight.y, 0), D3DXVECTOR4(0, 0, 1, 1));

	this->_pVertexBuffer->Unmap();

	//create indexes for a box 
	unsigned int* indexes = NULL;

	this->_pIndexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&indexes);

	indexes[0] = 0;
	indexes[1] = 1;
	indexes[2] = 2;
	indexes[3] = 3;
	indexes[4] = 0;

	this->_pIndexBuffer->Unmap();

	// Set primitive topology 
	this->_pD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

	for (UINT p = 0; p < this->_techDesc.Passes; ++p)
	{
		//apply technique
		this->_pBasicTechnique->GetPassByIndex(p)->Apply(0);

		//draw
		this->_pD3DDevice->DrawIndexed(5, 0, 0);
	}
}

Graphic::~Graphic()
{
	if (this->_pRenderTargetView) this->_pRenderTargetView->Release();
	if (this->_pSwapChain) this->_pSwapChain->Release();
	if (this->_pD3DDevice) this->_pD3DDevice->Release();
	if (this->_pVertexBuffer) this->_pVertexBuffer->Release();
	if (this->_pVertexLayout) this->_pVertexLayout->Release();
	if (this->_pIndexBuffer) this->_pIndexBuffer->Release();
	if (this->_pRS) this->_pRS->Release();
	if (this->_pBasicEffect) this->_pBasicEffect->Release();
}
