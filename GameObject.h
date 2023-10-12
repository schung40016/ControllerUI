#pragma once

#include "pch.h";
#include "EnumData.h";
#include <iostream>

class GameObject
{
private: 
	DirectX::SimpleMath::Vector2 gObj_position = { 0, 0 };
	float gObj_scale = 1.f;
	GameObject* gObj_parentObj = nullptr;
	bool gObj_display = false;
	float gObj_originalSize = 1.f;

public: 
	GameObject();

	GameObject(float inp_x, float inp_y, float inp_size);

	virtual DirectX::SimpleMath::Vector2 GetPosition() const;

	virtual GameObject* GetParentObj() const;

	virtual float GetScale() const;

	virtual bool GetDisplay() const;

	virtual void CalcScale(float inp_size);

	virtual void SetPosition(const float x = 0, const float y = 0);

	virtual void SetScale(const float inp_size);

	virtual void SetParent(GameObject& inp_parentObj);

	virtual void SetDisplay(const bool inp_show);

	virtual void SetOriginalSize(const float inp_ogSize);
};