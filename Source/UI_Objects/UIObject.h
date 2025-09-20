#pragma once

#include "pch.h"
#include "Source/Game/GameObject.h"

class UIObject : public GameObject
{
private:
	DirectX::XMVECTOR uiObj_color = DirectX::Colors::White;
	bool isStatic = false;

public:
	virtual bool CanRender() const;

	virtual const DirectX::XMVECTOR GetColor() const;

	/// <summary>
	/// Checks if object is static.
	/// </summary>
	/// <returns></returns>
	virtual bool GetIsStatic() const;

	/// <summary>
	/// Returns UI object's dimensions: width and height.
	/// </summary>
	virtual DirectX::SimpleMath::Vector2 GetDimensions() const;

	virtual void SetColor(DirectX::XMVECTOR inp_color);

	/// <summary>
	/// Determine if UI object is static.
	/// </summary>
	/// <returns></returns>
	virtual void SetIsStatic(bool inp_isStatic);
};
