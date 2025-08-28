#pragma once

#include "pch.h"
#include "Source/Game/GameObject.h"

class UIObject : public GameObject
{
private:
	DirectX::XMVECTOR uiObj_color = DirectX::Colors::White;
	bool isStatic = false;

public:
	virtual const DirectX::XMVECTOR GetColor() const;

	virtual bool GetIsStatic() const;

	virtual void SetColor(DirectX::XMVECTOR inp_color);

	virtual void SetIsStatic(bool inp_isStatic);
};
