#pragma once

#include "./pch.h"
#include "UIObject.h"

class Text : public UIObject
{
private:
	std::string text = "";
	DirectX::SimpleMath::Vector2 m_origin = { 0, 0 };

public:
	Text();
	
	Text(std::string id, DirectX::XMVECTOR inp_color, std::string inp_text);

	Text(std::string id, DirectX::XMVECTOR inp_color, std::string inp_text, GameObject& inp_parentObj, float inp_x, float inp_y, bool inp_isStatic);

	void Draw(const std::unique_ptr<DirectX::SpriteFont>& m_font, const std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch, const DirectX::SimpleMath::Vector2& camOffset);

	// Getters & Setters
	void SetOrigin(const std::unique_ptr<DirectX::SpriteFont>& m_font);

	void SetText(std::string inp_string);

	std::wstring GetWStringText();
};