#include "Source/pch.h"
#include "UIObject.h"

const DirectX::XMVECTOR UIObject::GetColor() const 
{
	return uiObj_color;
}

void UIObject::SetColor(DirectX::XMVECTOR inp_color)
{
	uiObj_color = inp_color;
}