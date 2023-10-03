#pragma once

#include "pch.h"
#include "UIObject.h"

using namespace DirectX;

class Image : public UIObject
{
private:
	DirectX::SimpleMath::Vector2 m_origin = {0, 0};
	std::string imgLocation = "";
	EnumData::Descriptors currEnum;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture = {};	// used for origin.

public:
	Image();

	Image(DirectX::XMVECTOR inp_color, std::string inp_imgLocation, EnumData::Descriptors inp_enum, GameObject& inp_parentObj, float inp_x, float inp_y, float inp_scale);

	void RenderImage(std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch, std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors);

	void PrepareImageResources(ID3D12Device* device, DirectX::ResourceUploadBatch& resourceUpload,
		std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors);

	void ResetTexture();

	// Getters & Setters
	void SetImageOrigin();

	DirectX::SimpleMath::Vector2 GetOrigin();

	Microsoft::WRL::ComPtr<ID3D12Resource>& GetTexture();

	std::string GetImgLocation();

	std::wstring GetWStringImgLocation();

	EnumData::Descriptors GetImgEnum();
};
