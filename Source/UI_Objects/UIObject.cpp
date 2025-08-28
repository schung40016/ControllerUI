#include "pch.h"
#include "UIObject.h"

const DirectX::XMVECTOR UIObject::GetColor() const 
{
	return uiObj_color;
}

bool UIObject::GetIsStatic() const
{
	return isStatic;
}

void UIObject::SetColor(DirectX::XMVECTOR inp_color)
{
	uiObj_color = inp_color;
}

void UIObject::SetIsStatic(bool inp_isStatic)
{
	isStatic = inp_isStatic;
}