#include "Texture.h"

Texture::Texture()
{
	this->_tex = nullptr;
	this->_shaderRsView = nullptr;
	this->_width = 0;
	this->_height = 0;
}

Texture::Texture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* srv)
{
	this->_tex = tex;
	this->_shaderRsView = srv;

	CD3D10_TEXTURE2D_DESC desc;
	this->_tex->GetDesc(&desc);
	this->_width = desc.Width;
	this->_height = desc.Height;
}

Texture::~Texture()
{
	if (this->_tex != nullptr)
	{
		this->_tex->Release();
	}
	if (this->_shaderRsView != nullptr)
	{
		this->_shaderRsView->Release();
	}
}