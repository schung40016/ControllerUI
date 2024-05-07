#pragma once

#include "pch.h"
#include "Image.h"
#include "Source/Managers/GameObjectManager.h"

Image::Image() {
	resourceManager = GameObjectManager::GetInstance();
}

Image::Image(std::string id, DirectX::XMVECTOR inp_color, std::string inp_imgLocation, EnumData::Descriptors inp_enum, GameObject& inp_parentObj, float inp_x, float inp_y, float inp_scale)
	: imgLocation(inp_imgLocation), currEnum(inp_enum)
{
	SetName(id);
	SetColor(inp_color);
	SetParent(inp_parentObj);
	SetPosition({ inp_x, inp_y });
	SetScale(inp_scale);
	resourceManager->AddImgObj(id, *this);
}

void Image::RenderImage(std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch, std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors)
{
	DirectX::SimpleMath::Vector2 parentObj = GetPosition();


	m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(currEnum), GetTextureSize(m_texture.Get()),
		GetPosition(), nullptr, Colors::White, 0.f, m_origin, GetScale());
}

void Image::PrepareImageResources(ID3D12Device* device, DirectX::ResourceUploadBatch& resourceUpload, 
	std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors)
{
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(device, resourceUpload, GetWStringImgLocation().c_str(),
			m_texture.ReleaseAndGetAddressOf()));
	// Encapsulation != giving reference. 

	CreateShaderResourceView(device, m_texture.Get(),
		m_resourceDescriptors->GetCpuHandle(currEnum));
}

void Image::ResetTexture()
{
	m_texture.Reset();
}

// Getters & Setters
void Image::SetImageOrigin()
{
	XMUINT2 imageSize = GetTextureSize(m_texture.Get());

	m_origin.x = float(imageSize.x / 2);
	m_origin.y = float(imageSize.y / 2);
}

DirectX::SimpleMath::Vector2 Image::GetOrigin()
{
	return m_origin;
}

Microsoft::WRL::ComPtr<ID3D12Resource>& Image::GetTexture()
{
	return m_texture;
}

std::string Image::GetImgLocation()
{
	return imgLocation;
}

std::wstring Image::GetWStringImgLocation()
{
	return std::wstring(imgLocation.begin(), imgLocation.end());
}

EnumData::Descriptors Image::GetImgEnum()
{
	return currEnum;
}