#include "Model.h"

bool Model::Initialize(const std::string& filePath, ID3D11Device* device, ID3D11DeviceContext* deviceContext, ConstantBuffer<CB_VS_matrix>& constantBuffer)
{
	mDevice = device;
	mDeviceContext = deviceContext;
	mConstantBuffer = &constantBuffer;

	if (!LoadModel(filePath)) {
		OutputDebugString("load model from file failed");
		exit(-1);
	}

	return true;
}

void Model::Draw(XMMATRIX& worldMatrix, XMMATRIX viewProjectionMatrix)
{

	mDeviceContext->VSSetConstantBuffers(0, 1, mConstantBuffer->GetAddressOf());

	for (Mesh& mesh : mMeshes) {
		mConstantBuffer->data.wvpMatrix = XMMatrixTranspose(mesh.GetTransformMatrix() * worldMatrix * viewProjectionMatrix);
		mConstantBuffer->data.worldMatrix = XMMatrixTranspose(mesh.GetTransformMatrix() * worldMatrix);
		mConstantBuffer->ApplyChange();
		mesh.Draw();
	}
}

bool Model::LoadModel(const std::string& filePath)
{
	mFileDirectory = StringHelper::GetDirectoryFromPath(filePath);
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	if (pScene == nullptr) {
		return false;
	}

	ProcessNode(pScene->mRootNode, pScene, XMMatrixIdentity());
	return true;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, const XMMATRIX& parentTransformMatrix)
{
	XMMATRIX nodeTranformMatrix = XMMatrixTranspose(XMMATRIX(&node->mTransformation.a1)) * parentTransformMatrix;

	for (UINT i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		mMeshes.push_back(ProcessMesh(mesh, scene, nodeTranformMatrix));
	}

	for (UINT i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene, nodeTranformMatrix);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const XMMATRIX& transformMatrix)
{
	std::vector<Vertex3D> vertices;
	std::vector<UINT> indices;

	for (UINT i = 0; i < mesh->mNumVertices; i++) {
		Vertex3D vertex;

		vertex.pos.x = mesh->mVertices[i].x;
		vertex.pos.y = mesh->mVertices[i].y;
		vertex.pos.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0]) {
			vertex.coord.x = static_cast<float>(mesh->mTextureCoords[0][i].x);
			vertex.coord.y = static_cast<float>(mesh->mTextureCoords[0][i].y);
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	std::vector<Texture> textures;
	aiMaterial* pMaterial = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<Texture> diffuseTextures = LoadMaterialTextures(pMaterial, aiTextureType::aiTextureType_DIFFUSE, scene);
	textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());

	return Mesh(mDevice.Get(), mDeviceContext.Get(), vertices, indices, textures, transformMatrix);
}

TextureStorageType Model::DetermineTextureStorageType(const aiScene* pScene, aiMaterial* pMaterial, UINT index, aiTextureType textureType)
{
	if (pMaterial->GetTextureCount(textureType) == 0) {
		return TextureStorageType::None;
	}

	aiString path;
	pMaterial->GetTexture(textureType, index, &path);
	std::string texturePath = path.C_Str();

	if (texturePath[0] == '*') {
		if (pScene->mTextures[0]->mHeight == 0) {
			return TextureStorageType::EmbeddedIndexCompressed;
		}
		else {
			assert("SUPPORT DOES NOT EXIST YET FOR INDEXED NOT COMPRESSED TEXTURES!" && 0);
			return TextureStorageType::EmbeddedNonCompressed;
		}
	}

	if (const aiTexture* pTexture = pScene->GetEmbeddedTexture(texturePath.c_str())) {
		if (pTexture->mHeight == 0) {
			return TextureStorageType::EmbeddedCompressed;
		}
		else {
			assert("SUPPORT DOES NOT EXIST YET FOR EMBEDED NOT COMPRESSED TEXTURES!" && 0);
			return TextureStorageType::EmbeddedNonCompressed;
		}
	}

	if (texturePath.find('.') != std::string::npos) {
		return TextureStorageType::Disk;
	}

	return TextureStorageType::None;
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textureType, const aiScene* pScene)
{
	std::vector<Texture> materialTextures;
	TextureStorageType storeType = TextureStorageType::Invaild;
	unsigned int textureCount = pMaterial->GetTextureCount(textureType);

	if (textureCount == 0) {
		storeType = TextureStorageType::None;
		aiColor3D aiColor(0.0f, 0.0f, 0.0f);
		switch (textureType) {
		case aiTextureType_DIFFUSE:
			pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
			if (aiColor.IsBlack()) {
				materialTextures.push_back(Texture(mDevice.Get(), colors::UnloadedTextureColor, textureType));
			}
			else {
				materialTextures.push_back(Texture(mDevice.Get(), Color(aiColor.r * 255, aiColor.g * 255, aiColor.b * 255), textureType));
			}
		default:
			break;
		}
	}
	else {
		for (UINT i = 0; i < textureCount; i++) {
			aiString path;
			pMaterial->GetTexture(textureType, i, &path);
			TextureStorageType storeType = DetermineTextureStorageType(pScene, pMaterial, i, textureType);
			switch (storeType) {
			case TextureStorageType::EmbeddedIndexCompressed:
			{
				int index = GetTextureIndex(&path);
				Texture embeddedIndexedTexture(mDevice.Get(), reinterpret_cast<uint8_t*>(pScene->mTextures[index]->pcData), pScene->mTextures[index]->mWidth, textureType);
				materialTextures.push_back(embeddedIndexedTexture);
				break;
			}
			case TextureStorageType::EmbeddedCompressed:
			{
				const aiTexture* pTexture = pScene->GetEmbeddedTexture(path.C_Str());
				Texture embeddedTexture(mDevice.Get() , reinterpret_cast<uint8_t*>(pTexture->pcData), pTexture->mWidth, textureType);
				materialTextures.push_back(embeddedTexture);
				break;
			}
			case TextureStorageType::Disk:
			{
				std::string fileName = mFileDirectory + '/' + path.C_Str();
				Texture diskTexture(mDevice.Get(), fileName, textureType);
				materialTextures.push_back(diskTexture);
				break;
			}
			default:
				break;
			}
		}
	}

	if (materialTextures.empty()) {
		materialTextures.push_back(Texture(mDevice.Get(), colors::UnhandledTextureColor, aiTextureType::aiTextureType_DIFFUSE));
	}
	return materialTextures;
}

int Model::GetTextureIndex(aiString* pStr)
{
	assert(pStr->length >= 2);
	return atoi(&pStr->C_Str()[1]);
}
