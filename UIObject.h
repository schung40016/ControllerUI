#pragma once

#include "pch.h"
#include "GameObject.h"

class UIObject : public GameObject
{
protected:
	DirectX::XMVECTOR uiObj_color = DirectX::Colors::White;

public:
	virtual std::shared_ptr<GameObject> GetParentObj();

	virtual DirectX::XMVECTOR GetColor();

	virtual float GetScale() const override;

	virtual void SetParentObj(GameObject& inp_DirXObject);

	virtual void SetColor(DirectX::XMVECTOR inp_color);
};
