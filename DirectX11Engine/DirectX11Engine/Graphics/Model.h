#pragma once
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <DirectXMath.h>
#include <WICTextureLoader.h>

#include <string>
#include <vector>

#include "Mesh.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"

using namespace DirectX;

class Model {
public:
	bool Initialize(const std::string& filePath, ID3D11Device* device, ID3D11DeviceContext* deviceContext, ConstantBuffer<CB_VS_matrix>& constantBuffer);
	void Draw(XMMATRIX& worldMatrix, XMMATRIX viewProjectionMatrix);

private:
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext = nullptr;

	std::string mFileDirectory = "";
	std::vector<Mesh> mMeshes;
	ConstantBuffer<CB_VS_matrix>* mConstantBuffer = nullptr;

	bool LoadModel(const std::string& filePath);
	void ProcessNode(aiNode* node, const aiScene* scene, const XMMATRIX& parentTransformMatrix);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const XMMATRIX& transformMatrix);
	TextureStorageType DetermineTextureStorageType(const aiScene* pScene, aiMaterial* pMaterial, UINT index, aiTextureType textureType);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textureType, const aiScene* pScene);
	int GetTextureIndex(aiString* pStr);
};