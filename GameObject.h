#pragma once

#include "pch.h"
#include "EnumData.h"
#include "Component.h"
#include <iostream>

class GameObjectManager;

class GameObject
{
private: 
	std::string name = "";
	DirectX::SimpleMath::Vector2 gObj_position = { 0, 0 };
	float gObj_scale = 1.f;
	std::shared_ptr<GameObject> gObj_parentObj = nullptr;
	bool gObj_display = false;
	float gObj_originalSize = 1.f;
	int layerMask = 0;
	std::vector<Component*> components = {};
	float test = 0.f;

protected:
	GameObjectManager* resourceManager;

public: 
	GameObject();
	
	GameObject(std::string id, DirectX::SimpleMath::Vector2 inp_position, float inp_size);

	void UpdateComponents(float deltaTime);

	const std::string GetName();

	const DirectX::SimpleMath::Vector2 GetPosition() const;

	const std::shared_ptr<GameObject> GetParentObj() const;

	const float GetScale() const;

	const bool GetDisplay() const;

	const int GetLayerMask() const;

	void CalcScale(float inp_size);

	void SetName(std::string inp_name);

	void SetPosition(DirectX::SimpleMath::Vector2 inp_position);

	void SetScale(const float inp_size);

	void SetParent(GameObject& inp_parentObj);

	void SetDisplay(const bool inp_show);

	void SetOriginalSize(const float inp_ogSize);

	void SetLayerMask(const int inp_layerMask);

	void SetComponents(const std::vector<Component*>& inp_components);

	void MovePosition(const DirectX::SimpleMath::Vector2 inp_position);
};