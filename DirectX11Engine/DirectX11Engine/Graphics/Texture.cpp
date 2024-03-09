#include "Texture.h"

Texture::Texture(ID3D11Device* device, const Color& color, aiTextureType type)
{
	Initialize1x1ColorTexture(device, color, type);
}

Texture::Texture(ID3D11Device* device, const Color* colorData, UINT width, UINT height, aiTextureType type)
{
	InitializeColorTexture(device, colorData, width, height, type);
}

Texture::Texture(ID3D11Device* device, const std::string& filePath, aiTextureType type)
{
	mType = type;
	HRESULT hr = S_OK;
	if (StringHelper::GetFileExtension(filePath) == ".dds") {
		hr = DirectX::CreateDDSTextureFromFile(device, StringHelper::StringToWideString(filePath).c_str(), mTexture.GetAddressOf(), mTextureView.GetAddressOf());
	}
	else {
		hr = DirectX::CreateWICTextureFromFile(device, StringHelper::StringToWideString(filePath).c_str(), mTexture.GetAddressOf(), mTextureView.GetAddressOf());
	}
	if (FAILED(hr)) {
		Initialize1x1ColorTexture(device, colors::UnloadedTextureColor, type);
	}
}

Texture::Texture(ID3D11Device* device, const uint8_t* pData, size_t size, aiTextureType type)
{
	mType = type;
	HRESULT hr = DirectX::CreateWICTextureFromMemory(device, pData, size, mTexture.GetAddressOf(), mTextureView.GetAddressOf());
	HR(hr, "create wic texture from memory failed");
}

aiTextureType Texture::GetType()
{
	return mType;
}

ID3D11ShaderResourceView* Texture::GetShaderResourceView()
{
	return mTextureView.Get();
}

ID3D11ShaderResourceView** Texture::GetAddressOfShaderResourceView()
{
	return mTextureView.GetAddressOf();
}

void Texture::Initialize1x1ColorTexture(ID3D11Device* device, const Color& colorData, aiTextureType type)
{
	InitializeColorTexture(device, &colorData, 1, 1, type);
}

void Texture::InitializeColorTexture(ID3D11Device* device, const Color* colorData, UINT width, UINT height, aiTextureType type)
{
	mType = type;
	CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);
	ID3D11Texture2D* p2DTexture = nullptr;
	D3D11_SUBRESOURCE_DATA initialData{};
	initialData.pSysMem = colorData;
	initialData.SysMemPitch = width * sizeof(Color);
	HRESULT hr = device->CreateTexture2D(&textureDesc, &initialData, &p2DTexture);
	HR(hr, "Create Texture 2d from color data failed");

	mTexture = static_cast<ID3D11Texture2D*>(p2DTexture);
	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);

	hr = device->CreateShaderResourceView(mTexture.Get(), &srvDesc, mTextureView.GetAddressOf());
	HR(hr, "Shader resrouce view from texture generated from color data failed");
}
