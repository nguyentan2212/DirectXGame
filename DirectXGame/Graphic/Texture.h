#pragma once
#include <d3d10.h>
#include <D3DX10.h>
#include "../Utils/Property.h"

class Texture
{
public:
	Texture();
	Texture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* srv);
	~Texture();

#pragma region Properties
	R_PROPERTY(ID3D10ShaderResourceView*, shaderRsView);
	GET(shaderRsView) { return this->_shaderRsView; }

	R_PROPERTY(int, width);
	GET(width) { return this->_width; }

	R_PROPERTY(int, height);
	GET(height) { return this->_height; }
#pragma endregion

private:
	ID3D10Texture2D* _tex;
	ID3D10ShaderResourceView* _shaderRsView;
	int _width;
	int _height;
};

