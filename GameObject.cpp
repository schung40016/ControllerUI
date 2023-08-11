#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(float inp_x, float inp_y, float inp_size)
{
	m_position = { inp_x, inp_y };
	m_originalSize = inp_size;
}

DirectX::SimpleMath::Vector2 GameObject::GetPosition()
{
	if (m_parentObj)
	{
		DirectX::SimpleMath::Vector2 temp = { (m_position.x * GetScale()) + m_parentObj->GetPosition().x, (m_position.y * GetScale()) + m_parentObj->GetPosition().y };
		return temp;
	}

	return m_position;
}

float GameObject::GetScale()
{
	if (m_parentObj)
	{
		return m_parentObj->GetScale();
	}

	return m_scale;
}

bool GameObject::GetDisplay()
{
	return m_display;
}

void GameObject::SetPosition(float inp_x, float inp_y)
{
	m_position = { inp_x, inp_y };
}

void GameObject::SetScale(float inp_size)
{
	m_scale = inp_size;
}

void GameObject::CalcScale(float inp_size)
{
	m_scale = inp_size / m_originalSize;
}

void GameObject::SetDisplay(bool inp_display)
{
	m_display = inp_display;
}