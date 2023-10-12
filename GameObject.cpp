#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(float inp_x, float inp_y, float inp_size)
{
	gObj_position = { inp_x, inp_y };
	gObj_originalSize = inp_size;
}

DirectX::SimpleMath::Vector2 GameObject::GetPosition() const
{
	if (gObj_parentObj)
	{
		DirectX::SimpleMath::Vector2 temp = { (gObj_position.x * GetScale()) + gObj_parentObj->GetPosition().x, (gObj_position.y * GetScale()) + gObj_parentObj->GetPosition().y };
		return temp;
	}

	return gObj_position;
}

GameObject* GameObject::GetParentObj() const 
{
	return gObj_parentObj;
}

float GameObject::GetScale() const
{
	if (gObj_parentObj)
	{
		return gObj_parentObj->GetScale();
	}

	return gObj_scale;
}

bool GameObject::GetDisplay() const 
{
	return gObj_display;
}

void GameObject::CalcScale(float inp_size)
{
	gObj_scale = inp_size / gObj_originalSize;
}

void GameObject::SetPosition(const float inp_x, const float inp_y)
{
	gObj_position = { inp_x, inp_y };
}

void GameObject::SetScale(const float inp_size)
{
	gObj_scale = inp_size;
}

void GameObject::SetParent(GameObject& inp_parentObj)
{
	gObj_parentObj = &inp_parentObj;
}

void GameObject::SetDisplay(const bool inp_display)
{
	gObj_display = inp_display;
}

void GameObject::SetOriginalSize(const float inp_ogSize)
{
	gObj_originalSize = inp_ogSize;
}