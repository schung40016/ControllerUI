#include "pch.h"
#include "IDirXObject.h"

IDirXObject* IDirXObject::GetParentObj()
{
	return this->m_parentObj;
}

DirectX::XMVECTOR IDirXObject::GetColor()
{
	return m_color;
}

DirectX::SimpleMath::Vector2 IDirXObject::GetOffsetPos()
{
	return m_offsetPos;
}

DirectX::SimpleMath::Vector2 IDirXObject::GetPosition()
{
	return m_position;
}

float IDirXObject::GetScale()
{
	return m_scale;
}

void IDirXObject::SetParentObj(IDirXObject& inp_DirXObject)
{
	this->m_parentObj = &inp_DirXObject;
}

void IDirXObject::SetColor(DirectX::XMVECTOR inp_color)
{
	m_color = inp_color;
}

void IDirXObject::SetOffsetPos(float x, float y)
{
	m_offsetPos.x = x;
	m_offsetPos.y = y;
}

void IDirXObject::SetPosition(float x, float y)
{
	if (m_parentObj)
	{
		m_position.x = m_parentObj->GetPosition().x + m_offsetPos.x;
		m_position.y = m_parentObj->GetPosition().y + m_offsetPos.y;
	}
	else
	{
		m_position.x = x;
		m_position.y = y;
	}
}

void IDirXObject::SetScale(float inp_size = 0)
{
	if (m_parentObj)
	{
		m_scale = m_parentObj->GetScale();
	}
	else
	{
		m_scale = inp_size;
	}
}