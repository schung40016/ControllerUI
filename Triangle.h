#pragma once

#include "pch.h"
#include "IDirXObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Triangle : public IDirXObject
{
protected: 
	bool display = false;

public:
	// Constructor
	Triangle();

	Triangle(DirectX::XMVECTOR colorInput, IDirXObject& inp_parentObj, float input_scale, float x, float y, float offsetX, float offsetY);

	// Draw Triangle.
	void DrawTriangle(const std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch);

	bool GetDisplay();

	// Set Size.
	void SetSize(float input_scale);

	// Set Color.
	void SetColor(const DirectX::XMVECTOR& inp_color);

	void SetDisplay(bool inp_show);

	~Triangle();
};