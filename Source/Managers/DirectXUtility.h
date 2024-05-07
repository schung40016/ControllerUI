#pragma once

#include "pch.h"
#include "DeviceResources.h"
#include "Source/Game/GameObject.h"
#include "Source/UI_Objects/Image.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Line.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/UI_Objects/Shapes/Triangle.h"
#include "Source/UI_Objects/UIObject.h"

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

    void AwakeGameObjects();

    void UpdateGameObjects(float elapsedTime);

    void CleanScreen(const std::unique_ptr<DX::DeviceResources>& m_deviceResources);

    void RenderAllGameObjects(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Text>& txtObjects,
        std::unordered_map<std::string, Image>& imgObjects, std::unordered_map<std::string, Triangle>& triObjects, std::unordered_map<std::string, Line>& lnObjects, std::unordered_map<std::string, Quad>& quadObjects);

    void RenderSpriteBatchObjects(ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Text>& txtObjects, std::unordered_map<std::string, Image>& imgObjects);

    void RenderShapeObjects(ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Triangle>& shpObjects);

    void RenderShapeObjects(ID3D12GraphicsCommandList* commandList, const std::unordered_map<std::string, Quad>& quadObjects);

    void RenderLineObjects(ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Line>& lnObjects);

    void PrepareDeviceDependentResources(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12Device* device, std::unordered_map<std::string, Image>& imgObjects);

    void PrepareWindowDependentResources(RECT size, const D3D12_VIEWPORT& viewport);

    void CheckInputs(const std::unordered_map<std::string, Triangle>& shpObjects);

    void ResetAssets(std::unordered_map<std::string, Image>& imgObjects);

    void SetButtonDisplays(std::unordered_map<std::string, Triangle>& shpObjects);

    void UpdateCollisions();

    // Getters & Setters,
    bool GetControllerConnected();

    void SetControllerConnected(bool inp_isControllerConnected);
};