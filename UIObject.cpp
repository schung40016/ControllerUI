#include "pch.h"
#include "UIObject.h"

std::shared_ptr<GameObject> UIObject::GetParentObj()
{
	return std::shared_ptr<GameObject>(gObj_parentObj);
}

DirectX::XMVECTOR UIObject::GetColor()
{
	return uiObj_color;
}

float UIObject::GetScale() const 
{
	if (gObj_parentObj)
	{
		return gObj_parentObj->GetScale();
	}
	else
	{
		return gObj_scale;
	}
}

void UIObject::SetParentObj(GameObject& inp_UIObject)
{
	this->gObj_parentObj = &inp_UIObject;
}

void UIObject::SetColor(DirectX::XMVECTOR inp_color)
{
	uiObj_color = inp_color;
}