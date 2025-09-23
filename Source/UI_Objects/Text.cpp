#include "pch.h"
#include "Text.h"  
#include "Source/Managers/GameObjectManager.h"

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

Text::Text(std::string id, DirectX::XMVECTOR inp_color, std::string inp_text, GameObject& inp_parentObj, float inp_x, float inp_y, bool inp_isStatic = false)
	: text(inp_text)
{
	SetName(id);
	SetColor(inp_color);
	SetParent(inp_parentObj);
	SetPosition({ inp_x, inp_y });
	SetIsStatic(inp_isStatic);
	resourceManager->AddTxtObj(id, *this);
}

void Text::Draw(const std::unique_ptr<DirectX::SpriteFont>& m_font, const std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch, const DirectX::SimpleMath::Vector2& camOffset)
{
	SetDimensions(m_font->MeasureString(GetWStringText().c_str()));

	if (GetDisplay() == false)
	{
		return;
	}

	DirectX::SimpleMath::Vector2 pos = GetRenderPosition();

	if (!GetIsStatic())
	{
		pos += camOffset;		// Apply camera off set.
	}

	m_font->DrawString(m_spriteBatch.get(), GetWStringText().c_str(), pos, GetColor(), 0.f, m_origin, GetScale());
}

// Getters & Setters
std::wstring Text::GetWStringText()
{
	return std::wstring(text.begin(), text.end());
}

DirectX::SimpleMath::Vector2 Text::GetDimensions() const
{
	return dimensions;
}

void Text::SetDimensions(DirectX::SimpleMath::Vector2 dimensionsInput)
{
	dimensions = { dimensionsInput.x * GetScale(), dimensionsInput.y * GetScale() };
}

void Text::SetOrigin(const std::unique_ptr<DirectX::SpriteFont>& m_font)
{
	m_origin = m_font->MeasureString(GetWStringText().c_str());
	m_origin /= 2.f;
}

void Text::SetText(std::string inp_string)
{
	text = inp_string;
}

// Destructor
Text::~Text()
{
}

