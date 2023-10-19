#pragma once

#include "pch.h"
#include "Shape.h"

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