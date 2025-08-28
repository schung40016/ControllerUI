#include "pch.h"
#include "Shape.h"

void Shape::Draw(const std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>& inp_batch, const DirectX::SimpleMath::Vector2& camOffset) const
{
}

float Shape::GetLength() const
{
	return length;
}

float Shape::GetWidth() const 
{
	return width;
}

void Shape::SetLength(float inp_len)
{
	length = inp_len;
}

void Shape::SetWidth(float inp_wid)
{
	width = inp_wid;
}