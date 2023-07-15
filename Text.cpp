#pragma once

#include "pch.h"
#include "Text.h"  

Text::Text()
{
}

Text::Text(DirectX::XMVECTOR inp_color, std::string inp_text)
	: text(inp_text)
{
	m_color = inp_color;
}

Text::Text(DirectX::XMVECTOR inp_color, IDirXObject& inp_parentObj, std::string inp_text)
	: text(inp_text)
{
	m_color = inp_color;
	m_parentObj = &inp_parentObj;
}

void Text::DrawText(const std::unique_ptr<DirectX::SpriteFont>& m_font, const std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch)
{
	m_font->DrawString(m_spriteBatch.get(), GetWStringText().c_str(), m_position, m_color, 0.f, m_origin, m_scale);
}

// Getters & Setters
void Text::SetOrigin(const std::unique_ptr<DirectX::SpriteFont>& m_font)
{
	m_origin = m_font->MeasureString(GetWStringText().c_str());
	m_origin /= 2.f;
}

void Text::SetText(std::string inp_string)
{
	text = inp_string;
}

std::wstring Text::GetWStringText()
{
	return std::wstring(text.begin(), text.end());
}