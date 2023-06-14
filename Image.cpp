#include "pch.h"
#include "Image.h"

Image::Image()
{}

Image::Image(DirectX::XMVECTOR inp_color, float x, float y, std::string inp_imgLocation, RECT size)
	: shapeColor(inp_color), imgLocation(inp_imgLocation)
{
	SetPosition(size, x, y);
}

// Getters & Setters
void Image::SetPosition(RECT size, float x, float y)
{
	m_pos.x = float(size.right) / x;
	m_pos.y = float(size.bottom) / y;
}

void Image::SetOrigin(XMUINT2 image)
{
	m_origin.x = float(image.x / 2);
	m_origin.y = float(image.y / 2);
}

void Image::SetColor(DirectX::XMVECTOR inp_color)
{
	shapeColor = inp_color;
}

DirectX::SimpleMath::Vector2 Image::GetPosition()
{
	return m_pos;
}

DirectX::SimpleMath::Vector2 Image::GetOrigin()
{
	return m_origin;
}

DirectX::XMVECTOR Image::GetColor()
{
	return shapeColor;
}

Microsoft::WRL::ComPtr<ID3D12Resource> Image::GetTexture()
{
	return m_texture;
}

std::string Image::GetImgLocation()
{
	return imgLocation;
}

const wchar_t* Image::GetWCharTImgLocation()
{
	std::wstring widestr = std::wstring(imgLocation.begin(), imgLocation.end());
	return widestr.c_str();
}