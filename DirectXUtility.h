#pragma once

#include "pch.h"
#include <DeviceResources.h>
#include "GameObject.h"
#include "Image.h"
#include "Text.h"
#include "Line.h"
#include "Quad.h"
#include "Triangle.h"
#include "UIObject.h"

class DirectXUtility {
private: 
    // If using the DirectX Tool Kit for DX12, uncomment this line:
	std::unique_ptr<DirectX::GraphicsMemory> m_graphicsMemory;

    // Prepares bitfont for sprites.
    std::unique_ptr<DirectX::DescriptorHeap> m_resourceDescriptors;
    std::unique_ptr<DirectX::SpriteFont> m_font;
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

    // Shape Resources.
    using VertexType = DirectX::VertexPositionColor;
    std::unique_ptr<DirectX::BasicEffect> m_effect;
    std::unique_ptr<DirectX::BasicEffect> m_lineEffect;
    std::unique_ptr<DirectX::PrimitiveBatch<VertexType>> m_batch;

    GameObjectManager* resourceManager;
    
public: 
    DirectXUtility();

    void CleanScreen(const std::unique_ptr<DX::DeviceResources>& m_deviceResources);

    void RenderAllGameObjects(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12GraphicsCommandList* commandList, std::vector<Text>& txtObjects, std::vector<Image>& imgObjects,
        std::vector<Triangle>& triObjects, std::vector<Line>& lnObjects, std::vector<Quad>& shpObjects);

    void RenderSpriteBatchObjects(ID3D12GraphicsCommandList* commandList, std::vector<Text>& txtObjects, std::vector<Image>& imgObjects);

    void RenderShapeObjects(ID3D12GraphicsCommandList* commandList, std::vector<Triangle>& shpObjects);

    void RenderShapeObjects(ID3D12GraphicsCommandList* commandList, const std::vector<Quad>& quadObjects);

    void RenderLineObjects(ID3D12GraphicsCommandList* commandList, std::vector<Line>& lnObjects);

    void PrepareDeviceDependentResources(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12Device* device, std::vector<Image>& imgObjects);

    void PrepareWindowDependentResources(RECT size, const D3D12_VIEWPORT& viewport);

    void CheckInputs(const std::vector<Triangle>& shpObjects);

    void ResetAssets(std::vector<Image>& imgObjects);

    void SetButtonDisplays(const std::vector<Triangle>& shpObjects);

    // Getters & Setters,
    bool GetControllerConnected();

    void SetControllerConnected(bool inp_isControllerConnected);
};