#pragma once

#include "pch.h"

class IDirXObject
{
protected:
	IDirXObject* m_parentObj = nullptr;
	DirectX::XMVECTOR m_color = DirectX::Colors::White;
	DirectX::SimpleMath::Vector2 m_offsetPos = { 0, 0 };
	DirectX::SimpleMath::Vector2 m_offsetSize = { 0, 0 };
	DirectX::SimpleMath::Vector2 m_position = { 0, 0 };
	float m_scale = 1.f;

public:
	virtual IDirXObject* GetParentObj();

	virtual DirectX::XMVECTOR GetColor();
	
	virtual DirectX::SimpleMath::Vector2 GetOffsetPos();

	virtual DirectX::SimpleMath::Vector2 GetPosition();

	virtual float GetScale();

	virtual void SetParentObj(IDirXObject& inp_DirXObject);

	virtual void SetColor(DirectX::XMVECTOR inp_color);

	virtual void SetOffsetPos(float x, float y);
	
	virtual void SetPosition(float x = 0, float y = 0);

	virtual void SetScale(float inp_size);
};
