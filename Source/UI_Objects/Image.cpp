#include "pch.h"
#include "Image.h"
#include "Source/Managers/GameObjectManager.h"

Image::Image() 
{
	resourceManager = GameObjectManager::GetInstance();
}

Image::Image(std::string id, DirectX::XMVECTOR inp_color, std::string inp_imgLocation, EnumData::Descriptors inp_enum, GameObject& inp_parentObj, float inp_x, float inp_y, float inp_scale, bool inp_isStatic = false)
	: imgLocation(inp_imgLocation), currEnum(inp_enum)
{
	SetName(id);
	SetColor(inp_color);
	SetParent(inp_parentObj);
	SetPosition({ inp_x, inp_y });
	SetScale(inp_scale);
	SetIsStatic(inp_isStatic);
	resourceManager->AddImgObj(id, *this);
}

Image::Image(std::string id, DirectX::XMVECTOR inp_color, std::string inp_imgLocation, EnumData::Descriptors inp_enum, GameObject& inp_parentObj, float inp_x, float inp_y, float inp_scale, DirectX::SimpleMath::Vector2 inp_originPos, RECT inp_renderingRect)
	: imgLocation(inp_imgLocation), currEnum(inp_enum), m_origin(inp_originPos), renderingEdges(inp_renderingRect)
{
	SetName(id);
	SetColor(inp_color);
	SetParent(inp_parentObj);
	SetPosition({ inp_x, inp_y });
	SetScale(inp_scale);
	resourceManager->AddImgObj(id, *this);
}


void Image::Render(std::unique_ptr<DirectX::SpriteBatch>& m_spriteBatch, std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors, const Vector2& camOffset)
{
	Vector2 renderPosition = GetRenderPosition();

	if (!GetIsStatic())
	{
		renderPosition += camOffset;
	}

	if (bFlip)
	{
		m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(currEnum), GetTextureSize(m_texture.Get()),
			renderPosition, &renderingEdges, GetColor(), 0.f, m_origin, GetScale(), SpriteEffects_FlipHorizontally);
	} 
	else 
	{
		m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(currEnum), GetTextureSize(m_texture.Get()),
			renderPosition, &renderingEdges, GetColor(), 0.f, m_origin, GetScale());
	}
}
// Frustrum calling.
// Before rendering, figure out what objects should be rendered (i.e. the stuff we only want to show in the camera). 
// Future: Map arhcitecture. 

void Image::PrepareResources(ID3D12Device* device, DirectX::ResourceUploadBatch& resourceUpload, 
	std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors)
{
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(device, resourceUpload, GetWStringImgLocation().c_str(),
			m_texture.ReleaseAndGetAddressOf())); 

	CreateShaderResourceView(device, m_texture.Get(),
		m_resourceDescriptors->GetCpuHandle(currEnum));

	// If no rendering edges were provided, default to display full image.
	if (renderingEdges.right == 0 && renderingEdges.left == 0 && renderingEdges.bottom == 0 && renderingEdges.top == 0)
	{
		auto textureSize = GetTextureSize(m_texture.Get());
		renderingEdges = { 0, 0, static_cast<LONG>(textureSize.x), static_cast<LONG>(textureSize.y) };
	}
}

void Image::ResetTexture()
{
	m_texture.Reset();
}

// Getters & Setters
void Image::SetImageOrigin()
{
	XMUINT2 imageSize = GetTextureSize(m_texture.Get());

	m_origin.x = float(imageSize.x / 2);
	m_origin.y = float(imageSize.y / 2);
}

void Image::flipImage(bool input)
{
	bFlip = input;
}

DirectX::SimpleMath::Vector2 Image::GetOrigin()
{
	return m_origin;
}

Microsoft::WRL::ComPtr<ID3D12Resource>& Image::GetTexture()
{
	return m_texture;
}

std::string Image::GetImgLocation()
{
	return imgLocation;
}

std::wstring Image::GetWStringImgLocation()
{
	return std::wstring(imgLocation.begin(), imgLocation.end());
}

DirectX::SimpleMath::Vector2 Image::GetDimensions() const
{
	return {(float)(renderingEdges.right - renderingEdges.left), (float)(renderingEdges.bottom - renderingEdges.top)};
}

void Image::SetSpriteRender(const DirectX::SimpleMath::Vector2 origin, const RECT sprite_rect)
{
	m_origin = origin;
	renderingEdges = sprite_rect;
}