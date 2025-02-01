#include "pch.h"
#include "GameObject.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Components/Component.h"
#include "iostream"

GameObject::GameObject()
{
	name = "Not Initialized";
	resourceManager = GameObjectManager::GetInstance();
}

GameObject::GameObject(std::string id, DirectX::SimpleMath::Vector2 inp_position, float inp_size)
{
	name = id;
	resourceManager = GameObjectManager::GetInstance();
	gObj_position = inp_position;
	CalculatePositionActual(gObj_position);
	gObj_originalSize = inp_size;
	resourceManager->AddGameObj(id, *this);
}


GameObject::GameObject(std::string id, DirectX::SimpleMath::Vector2 inp_position, float inp_size, DirectX::SimpleMath::Vector2 inp_sizeDimensions) 
{
	name = id;
	resourceManager = GameObjectManager::GetInstance();
	gObj_size = inp_sizeDimensions;
	gObj_position = inp_position;
	CalculatePositionActual(gObj_position);
	gObj_originalSize = inp_size;
	resourceManager->AddGameObj(id, *this);
}

void GameObject::Awake()
{
	for (auto& comp : components)
	{
		comp->Awake();
	}
}

void GameObject::Update(float deltaTime)
{
	for (auto& comp : components)
	{
 		comp->Update(deltaTime);
	}
}

const std::string GameObject::GetName() const
{
	return name;
}

const DirectX::SimpleMath::Vector2 GameObject::GetPosition() const
{
	if (gObj_parentObj)
	{
		float scale = GetScale();
		DirectX::SimpleMath::Vector2 parent_pos = gObj_parentObj->GetPosition();
		float calcX = gObj_position.x * scale + parent_pos.x;
		float calcY = gObj_position.y * scale + parent_pos.y;
		DirectX::SimpleMath::Vector2 temp = { calcX, calcY };
		return temp;
	}

	return gObj_position;
}

const DirectX::SimpleMath::Vector2 GameObject::GetPositionActual() const 

{
	//if (gObj_parentObj)
	//{
	//	float scale = GetScale();
	//	DirectX::SimpleMath::Vector2 parent_pos = gObj_parentObj->GetPositionActual();
	//	float calcX = gObj_positionActual.x * scale + parent_pos.x;
	//	float calcY = gObj_positionActual.y * scale + parent_pos.y;
	//	DirectX::SimpleMath::Vector2 temp = { calcX, calcY };
	//	return temp;
	//}
	DirectX::SimpleMath::Vector2 temp = GetPosition();
	temp = DirectX::SimpleMath::Vector2(temp.x, 975.f - temp.y);

	return temp;
}

const std::shared_ptr<GameObject> GameObject::GetParentObj() const
{
	return gObj_parentObj;
}

const float GameObject::GetScale() const
{
	if (gObj_parentObj)
	{
		return gObj_scale * gObj_parentObj->GetScale();
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

const DirectX::SimpleMath::Vector2 GameObject::GetSize() const
{
	return gObj_size;
}

void GameObject::CalcScale(float inp_size)
{
	gObj_scale = inp_size / gObj_originalSize;
}

void GameObject::SetName(std::string inp_name)
{
	name = inp_name;
}

void GameObject::SetPosition(const DirectX::SimpleMath::Vector2 inp_position)
{
	gObj_position = inp_position;
	gObj_positionActual = { inp_position.x, 975.f - inp_position.y };
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

void GameObject::SetComponents(const std::vector<Component*>& inp_components)
{
	components = inp_components;
}

void GameObject::SetSize(const DirectX::SimpleMath::Vector2 inp_size)
{
	gObj_size = inp_size;
}

void GameObject::MovePosition(const DirectX::SimpleMath::Vector2 inp_position)
{
	gObj_position = gObj_position + inp_position;
	CalculatePositionActual(gObj_position);
}

void GameObject::CalculatePositionActual(DirectX::SimpleMath::Vector2 inp_position)
{
	gObj_positionActual = { inp_position.x, 975.f - inp_position.y };
}