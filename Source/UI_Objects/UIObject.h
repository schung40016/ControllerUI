#pragma once

#include "Source/pch.h"
#include "Source/Game/GameObject.h"

class UIObject : public GameObject
{
private:
	DirectX::XMVECTOR uiObj_color = DirectX::Colors::White;

public:
	virtual const DirectX::XMVECTOR GetColor() const;

	virtual void SetColor(DirectX::XMVECTOR inp_color);
};
