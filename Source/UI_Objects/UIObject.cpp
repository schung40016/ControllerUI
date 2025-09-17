#include "pch.h"
#include "UIObject.h"

bool UIObject::CanRender() const
{
	return false;
}

const DirectX::XMVECTOR UIObject::GetColor() const 
{
	return uiObj_color;
}

/// <inheritdoc/>
bool UIObject::GetIsStatic() const
{
	return isStatic;
}

void UIObject::SetColor(DirectX::XMVECTOR inp_color)
{
	uiObj_color = inp_color;
}

/// <inheritdoc/>
void UIObject::SetIsStatic(bool inp_isStatic)
{
	isStatic = inp_isStatic;
}