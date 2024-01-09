#pragma once

#include "pch.h"
#include "UIObject.h"

class Shape : public UIObject
{
private:
	float length = 1.f;
	float width = 1.f;

public:
	virtual void Draw(const std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>& inp_batch) const;

	float GetLength() const;

	float GetWidth() const;

	void SetLength(float inp_len);
	 
	void SetWidth(float inp_wid);

	// TO-DO:
	// Create a physics controller/rigidbody that can be attached to gameobject.
	// - will use Standard axis theorem to calculate collission detectin
};