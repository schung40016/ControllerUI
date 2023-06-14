#pragma once

#include "./pch.h"

using namespace DirectX;

class Image
{
private:
	DirectX::SimpleMath::Vector2 m_pos = {0, 0};
	DirectX::SimpleMath::Vector2 m_origin = {0, 0};
	DirectX::XMVECTOR shapeColor = DirectX::Colors::White;
	std::string imgLocation = "";
	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture = {};	// used for origin.

public: 
	Image();

	Image(DirectX::XMVECTOR inp_color, float x, float y, std::string inp_imgLocation, RECT size);

	// Getters & Setters
	void SetPosition(RECT size, float x, float y);

	void SetOrigin(XMUINT2 image);

	void SetColor(DirectX::XMVECTOR inp_color);

	DirectX::SimpleMath::Vector2 GetPosition();

	DirectX::SimpleMath::Vector2 GetOrigin();

	DirectX::XMVECTOR GetColor();

	Microsoft::WRL::ComPtr<ID3D12Resource> GetTexture();

	std::string GetImgLocation();

	const wchar_t* GetWCharTImgLocation();
};
