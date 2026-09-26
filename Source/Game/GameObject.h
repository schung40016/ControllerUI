#pragma once

#include "pch.h"
#include "Source/Enum/EnumData.h"
#include "../Constants/DefaultValues.h"

class GameObjectManager;

class Component;

class GameObject
{
private: 
	std::string name = "";
	DirectX::SimpleMath::Vector3 gObj_position = { 0, 0, 0 };
	DirectX::SimpleMath::Vector3 gObj_positionActual = { 0, 0, 0 };
	DirectX::SimpleMath::Vector2 gObj_size = { 0, 0 };
	float gObj_scale = 1.f;
	std::shared_ptr<GameObject> gObj_parentObj = nullptr;
	bool gObj_display = false;
	float gObj_originalSize = 1.f;										// FOr calculating sizes relative to parent.
	int layerMask = 0;
	std::vector<Component*> components = {};
	std::unordered_map<std::string, Component*> colliderObjBank = {};
	float fRenderOffset = DefaultValues::Y_OFFSET;

protected:
	GameObjectManager* resourceManager;

public: 
	GameObject();
	
	GameObject(std::string id, DirectX::SimpleMath::Vector2 inp_position, float inp_size, float inp_z = DefaultValues::Z_DEFAULT);

	GameObject(std::string id, DirectX::SimpleMath::Vector2 inp_position, float inp_size, DirectX::SimpleMath::Vector2 inp_sizeDimensions, float inp_z = DefaultValues::Z_DEFAULT);

	void Awake();

	void Update(float deltaTime);

	const std::string GetName() const;

	/// <summary>
	/// World position including depth. The z axis is the render depth:
	/// LOWER z draws on top of higher z, following Unity's convention.
	/// </summary>
	const DirectX::SimpleMath::Vector3 GetPosition() const;

	/// <summary>
	/// World position with the depth component dropped, for 2D maths
	/// such as collision and raycasting.
	/// </summary>
	const DirectX::SimpleMath::Vector2 GetPosition2D() const;

	/// <summary>
	/// Render depth of this object, including any depth inherited from parents.
	/// </summary>
	const float GetZ() const;
	
	const DirectX::SimpleMath::Vector2 GetRenderPosition() const;

	const std::shared_ptr<GameObject> GetParentObj() const;

	const float GetScale() const;

	const bool GetDisplay() const;

	const int GetLayerMask() const;

	const DirectX::SimpleMath::Vector2 GetSize() const;

	void CalcScale(float inp_size);

	void SetName(std::string inp_name);

	void SetPosition(DirectX::SimpleMath::Vector3 inp_position);

	/// <summary>
	/// Sets the x/y position while preserving the existing render depth.
	/// </summary>
	void SetPosition(DirectX::SimpleMath::Vector2 inp_position);

	/// <summary>
	/// Sets the render depth. Lower values draw on top.
	/// </summary>
	void SetZ(float inp_z);

	void SetScale(const float inp_size);

	void SetParent(GameObject& inp_parentObj);

	void SetDisplay(const bool inp_show);

	void SetOriginalSize(const float inp_ogSize);

	void SetComponents(const std::vector<Component*>& inp_components);

	void SetSize(const DirectX::SimpleMath::Vector2 inp_size);

	void MovePosition(const DirectX::SimpleMath::Vector2 inp_position);

	void CalculatePositionActual(DirectX::SimpleMath::Vector3 inp_position);

	template <typename T> 
	inline T* GetComponent()
	{
		for (Component* ptr : components)
		{
			std::string typeName = typeid(*ptr).name();
			std::string typeName2 = typeid(T).name();

			if (typeName.compare(typeName2) == 0)
			{
				return dynamic_cast<T*>(ptr);
			}
		}
		return nullptr;
	}
};