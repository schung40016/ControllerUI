#pragma once

#include "pch.h"
#include "Image.h"

Image::Image()
{}

Image::Image(DirectX::XMVECTOR inp_color, std::string inp_imgLocation, GameObject& inp_parentObj, float inp_x, float inp_y, float inp_scale)
	: imgLocation(inp_imgLocation) 
{
	m_color = inp_color;
	m_parentObj = &inp_parentObj;
	m_position = {inp_x, inp_y};
	m_scale = inp_scale;
}

Image::Image(DirectX::XMVECTOR inp_color, UIObject& inp_parentObj, std::string inp_imgLocation, float inp_scale)
	: imgLocation(inp_imgLocation)
{
	m_color = inp_color;
	this->m_parentObj = &inp_parentObj;
	m_scale = inp_scale;
}

void Image::RenderImage(std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch, std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors,
	int imageID)
{
	m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(imageID), GetTextureSize(m_texture.Get()),
		GetPosition(), nullptr, Colors::White, 0.f, m_origin, GetScale());
}

void Image::PrepareImageResources(ID3D12Device* device, DirectX::ResourceUploadBatch& resourceUpload, 
	std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors, int imageID)
{
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(device, resourceUpload, GetWStringImgLocation().c_str(),
			m_texture.ReleaseAndGetAddressOf()));
	// Encapsulation != giving reference. 

	CreateShaderResourceView(device, m_texture.Get(),
		m_resourceDescriptors->GetCpuHandle(imageID));
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