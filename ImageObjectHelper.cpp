#include "pch.h"
#include "ImageObjectHelper.h"

ImageObjectHelper::ImageObjectHelper()
{

}

void ImageObjectHelper::SetImagePosition(DirectX::SimpleMath::Vector2& vectorInput, RECT size, float x, float y) 
{
	vectorInput.x = float(size.right) / x;
	vectorInput.y = float(size.bottom) / y;
}

void ImageObjectHelper::SetImagePivot(DirectX::SimpleMath::Vector2& vectorInput, DirectX::XMUINT2& image)
{
	vectorInput.x = float(image.x / 2);
	vectorInput.y = float(image.y / 2);
}