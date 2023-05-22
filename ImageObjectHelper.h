#pragma once

#include "pch.h"

class ImageObjectHelper
{
public: 
	ImageObjectHelper();

	void SetImagePosition(DirectX::SimpleMath::Vector2& vectorInput, RECT size, float x, float y);

	void SetImagePivot(DirectX::SimpleMath::Vector2& vectorInput, DirectX::XMUINT2& image);
};