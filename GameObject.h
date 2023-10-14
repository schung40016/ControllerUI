#pragma once

#include "pch.h";
#include "EnumData.h";
#include <iostream>

class GameObject
{
private: 
	DirectX::SimpleMath::Vector2 gObj_position = { 0, 0 };
	float gObj_scale = 1.f;
	std::shared_ptr<GameObject> gObj_parentObj = nullptr;
	bool gObj_display = false;
	float gObj_originalSize = 1.f;

public: 
	GameObject();

	GameObject(float inp_x, float inp_y, float inp_size);

	const DirectX::SimpleMath::Vector2 GetPosition() const;

	const std::shared_ptr<GameObject> GetParentObj() const;

	const float GetScale() const;

	const bool GetDisplay() const;

	void CalcScale(float inp_size);

	void SetPosition(const float x = 0, const float y = 0);

	void SetScale(const float inp_size);

	void SetParent(GameObject& inp_parentObj);

	void SetDisplay(const bool inp_show);

	void SetOriginalSize(const float inp_ogSize);
};