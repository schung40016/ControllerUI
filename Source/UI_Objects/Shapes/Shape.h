#pragma once

#include "pch.h"
#include "Source/UI_Objects/UIObject.h"

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
};