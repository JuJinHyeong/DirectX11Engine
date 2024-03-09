#pragma once
#include <d3d11.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <wrl/client.h>

#include "Color.h"
#include "..//ErrorLogger.h"
#include "..//StringHelper.h"

#include <string>
#include <assimp/material.h>

enum class TextureStorageType {
	Invaild,
	None,
	EmbeddedIndexCompressed,
	EmbeddedIndexNonCompressed,
	EmbeddedCompressed,
	EmbeddedNonCompressed,
	Disk
};

class Texture {
public:
	Texture(ID3D11Device* device, const Color& color, aiTextureType type);
	Texture(ID3D11Device* device, const Color* colorData, UINT width, UINT height, aiTextureType type);
	Texture(ID3D11Device* device, const std::string& textureFilePath, aiTextureType type);
	Texture(ID3D11Device* device, const uint8_t* pData, size_t size, aiTextureType type);

	aiTextureType GetType();
	ID3D11ShaderResourceView* GetShaderResourceView();
	ID3D11ShaderResourceView** GetAddressOfShaderResourceView();
private:
	void Initialize1x1ColorTexture(ID3D11Device* device, const Color& colorData, aiTextureType type);
	void InitializeColorTexture(ID3D11Device* device, const Color* colorData, UINT width, UINT height, aiTextureType type);
	Microsoft::WRL::ComPtr<ID3D11Resource> mTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTextureView = nullptr;
	aiTextureType mType = aiTextureType::aiTextureType_UNKNOWN;
};