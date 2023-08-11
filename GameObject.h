#pragma once

#include "pch.h"
#include <iostream>

class GameObject
{
protected: 
	DirectX::SimpleMath::Vector2 m_position = { 0, 0 };
	float m_scale = 1.f;
	GameObject* m_parentObj = nullptr;
	bool m_display = false;
	float m_originalSize = 1.f;

public: 
	GameObject();

	GameObject(float inp_x, float inp_y, float inp_size);

	virtual DirectX::SimpleMath::Vector2 GetPosition();

	virtual float GetScale();

	virtual bool GetDisplay();

	virtual void SetPosition(float x = 0, float y = 0);

	virtual void SetScale(float inp_size);

	virtual void CalcScale(float inp_size);

	virtual void SetDisplay(bool inp_show);
};