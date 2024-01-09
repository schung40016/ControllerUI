#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(DirectX::SimpleMath::Vector2 inp_position, float inp_size)
{
	gObj_position = inp_position;
	gObj_originalSize = inp_size;
}

const DirectX::SimpleMath::Vector2 GameObject::GetPosition() const
{
	if (gObj_parentObj)
	{
		DirectX::SimpleMath::Vector2 temp = { (gObj_position.x * GetScale()) + gObj_parentObj->GetPosition().x, (gObj_position.y * GetScale()) + gObj_parentObj->GetPosition().y };
		return temp;
	}

	return gObj_position;
}

const std::shared_ptr<GameObject> GameObject::GetParentObj() const
{
	return gObj_parentObj;
}

const float GameObject::GetScale() const
{
	if (gObj_parentObj)
	{
		return gObj_parentObj->GetScale();
	}

	return gObj_scale;
}

const bool GameObject::GetDisplay() const
{
	return gObj_display;
}

const int GameObject::GetLayerMask() const
{
	return layerMask;
}

void GameObject::CalcScale(float inp_size)
{
	gObj_scale = inp_size / gObj_originalSize;
}

void GameObject::SetPosition(const DirectX::SimpleMath::Vector2 inp_position)
{
	gObj_position = inp_position;
}

void GameObject::SetScale(const float inp_size)
{
	gObj_scale = inp_size;
}

void GameObject::SetParent(GameObject& inp_parentObj)
{
	gObj_parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
}

void GameObject::SetDisplay(const bool inp_display)
{
	gObj_display = inp_display;
}

void GameObject::SetOriginalSize(const float inp_ogSize)
{
	gObj_originalSize = inp_ogSize;
}