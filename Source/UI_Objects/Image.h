#pragma once

#include "pch.h"
#include "UIObject.h"

using namespace DirectX;

class Image : public UIObject
{
private:
	DirectX::SimpleMath::Vector2 m_origin = {0, 0};
	RECT renderingEdges = {};
	std::string imgLocation = "";
	EnumData::Descriptors currEnum;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture = {};	// used for origin.
	bool bFlip = false;

public:
	Image();

	// Renders entire image.
	Image(std::string id, DirectX::XMVECTOR inp_color, std::string inp_imgLocation, EnumData::Descriptors inp_enum, GameObject& inp_parentObj, float inp_x, float inp_y, float inp_scale, bool inp_isStatic);
	
	// Renders partial sprite.
	Image(std::string id, DirectX::XMVECTOR inp_color, std::string inp_imgLocation, EnumData::Descriptors inp_enum, GameObject& inp_parentObj, float inp_x, float inp_y, float inp_scale, DirectX::SimpleMath::Vector2 inp_originPos, RECT inp_renderingRect);

	void Render(std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch, std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors, const DirectX::SimpleMath::Vector2& camOffset);

	void PrepareResources(ID3D12Device* device, DirectX::ResourceUploadBatch& resourceUpload,
		std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors);

	void ResetTexture();

	// Getters & Setters
	void SetImageOrigin();

	void flipImage(bool input);

	DirectX::SimpleMath::Vector2 GetOrigin();

	Microsoft::WRL::ComPtr<ID3D12Resource>& GetTexture();

	std::string GetImgLocation();

	std::wstring GetWStringImgLocation();

	DirectX::SimpleMath::Vector2 GetDimensions() const override;

	void SetSpriteRender(DirectX::SimpleMath::Vector2 origin, RECT sprite_rect);
};
