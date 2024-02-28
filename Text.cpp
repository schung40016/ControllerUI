#pragma once

#include "pch.h"
#include "Text.h"  
#include "GameObjectManager.h"

Text::Text()
{
	resourceManager = GameObjectManager::GetInstance();
}

Text::Text(std::string id, DirectX::XMVECTOR inp_color, std::string inp_text)
	: text(inp_text)
{
	SetName(id);
	SetColor(inp_color);
	resourceManager->AddTxtObj(id, *this);
}

Text::Text(std::string id, DirectX::XMVECTOR inp_color, std::string inp_text, GameObject& inp_parentObj, float inp_x, float inp_y)
	: text(inp_text)
{
	SetColor(inp_color);
	SetParent(inp_parentObj);
	SetPosition({ inp_x, inp_y });
	resourceManager->AddTxtObj(id, *this);
}

void Text::DrawText(const std::unique_ptr<DirectX::SpriteFont>& m_font, const std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch)
{
	m_font->DrawString(m_spriteBatch.get(), GetWStringText().c_str(), GetPosition(), GetColor(), 0.f, m_origin, GetScale());
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