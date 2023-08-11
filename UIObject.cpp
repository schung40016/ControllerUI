#include "pch.h"
#include "UIObject.h"

GameObject* UIObject::GetParentObj()
{
	return this->m_parentObj;
}

DirectX::XMVECTOR UIObject::GetColor()
{
	return m_color;
}

float UIObject::GetScale()
{
	if (m_parentObj)
	{
		return m_parentObj->GetScale();
	}
	else
	{
		return m_scale;
	}
}

void UIObject::SetParentObj(GameObject& inp_UIObject)
{
	this->m_parentObj = &inp_UIObject;
}

void UIObject::SetColor(DirectX::XMVECTOR inp_color)
{
	m_color = inp_color;
}