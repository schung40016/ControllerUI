#pragma once

#include "./pch.h"
#include "IDirXObject.h"

class Text : public IDirXObject
{
private:
	std::string text = "";
	DirectX::SimpleMath::Vector2 m_origin = { 0, 0 };

public:
	Text();
	
	Text(DirectX::XMVECTOR inp_color, std::string inp_text);

	Text(DirectX::XMVECTOR inp_color, IDirXObject& inp_parentObj, std::string inp_text);

	void DrawText(const std::unique_ptr<DirectX::SpriteFont>& m_font, const std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch);

	// Getters & Setters
	void SetOrigin(const std::unique_ptr<DirectX::SpriteFont>& m_font);

	void SetText(std::string inp_string);

	std::wstring GetWStringText();
};