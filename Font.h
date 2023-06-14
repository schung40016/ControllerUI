#pragma once

#include "pch.h"

class Font 
{
private: 
	const wchar_t* text;
	DirectX::XMVECTOR textColor;
	DirectX::SimpleMath::Vector2 textOrigin;

public:
	Font(const wchar_t* text, DirectX::XMVECTOR textColor);

	// Set Origin.
	void SetTextOrigin();

	// Set font position.
	void SetFontPosition(DirectX::SimpleMath::Vector2& vectorInput, RECT size, float x, float y);
};