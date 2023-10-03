#pragma once

#include "pch.h";
#include "EnumData.h";
#include <iostream>

class GameObject
{
protected: 
	DirectX::SimpleMath::Vector2 gObj_position = { 0, 0 };
	float gObj_scale = 1.f;
	GameObject* gObj_parentObj = nullptr;
	bool gObj_display = false;
	float gObj_originalSize = 1.f;

public: 
	GameObject();

	GameObject(float inp_x, float inp_y, float inp_size);

	virtual DirectX::SimpleMath::Vector2 GetPosition() const;

	virtual float GetScale() const;

	virtual bool GetDisplay() const;

	virtual void SetPosition(float x = 0, float y = 0);

	virtual void SetScale(float inp_size);

	virtual void CalcScale(float inp_size);

	virtual void SetDisplay(bool inp_show);
};