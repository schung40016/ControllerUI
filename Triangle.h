#pragma once

#include "./pch.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Triangle
{
private: 
	DirectX::XMVECTOR shapeColor = DirectX::Colors::Black;
	float size = 1.f;
	float x = 0.f;
	float y = 0.f;
	bool display = false;

public:
	// Constructor
	Triangle();

	Triangle(DirectX::XMVECTOR colorInput, float input_size, float x, float y, bool inp_show);

	// Draw Triangle.
	void DrawTriangle(std::unique_ptr<DirectX::PrimitiveBatch<VertexPositionColor>>& m_batch);

	bool GetDisplay();

	// Set Size.
	void SetSize(float input_size);

	// Set Position.
	void SetPos(float x, float y);

	// Set Color.
	void SetColor(DirectX::XMVECTOR inp_color);

	void SetDisplay(bool inp_show);

	~Triangle();
};