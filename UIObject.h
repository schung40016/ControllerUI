#pragma once

#include "pch.h"
#include "GameObject.h"

class UIObject : public GameObject
{
protected:
	DirectX::XMVECTOR m_color = DirectX::Colors::White;

public:
	virtual GameObject* GetParentObj();

	virtual DirectX::XMVECTOR GetColor();

	virtual float GetScale() override;

	virtual void SetParentObj(GameObject& inp_DirXObject);

	virtual void SetColor(DirectX::XMVECTOR inp_color);
};
