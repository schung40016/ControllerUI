#pragma once

#include "pch.h"
#include "DeviceResources.h"
#include "Source/Game/GameObject.h"
#include "Source/UI_Objects/Image.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Line.h"
#include "Source/Components/Camera.h"
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
    Camera* focusedCamera = nullptr;

    // Identifies which batch/effect a renderable needs, so the sorted draw
    // pass knows when it must close one batch and open another.
    enum class RenderBatchType
    {
        None,
        Sprite,
        Shape,
        Line
    };

    // A single renderable resolved into "what to draw" plus "how deep it is".
    // Exactly one of the object pointers is non-null.
    struct RenderEntry
    {
        float depth = DefaultValues::Z_DEFAULT;
        RenderBatchType batchType = RenderBatchType::None;
        Text* text = nullptr;
        Image* image = nullptr;
        const Shape* shape = nullptr;
        const Line* line = nullptr;
    };

    // Reused between frames so the per-frame sort does not reallocate.
    std::vector<RenderEntry> renderQueue;

    int frameCount = 0;
    float width = 0.f;
    float height = 0.f;

public: 
    DirectXUtility();

    void AwakeGameObjects();

    void UpdateGameObjects(float elapsedTime);

    void CleanScreen(const std::unique_ptr<DX::DeviceResources>& m_deviceResources);

    void RenderAllGameObjects(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Text>& txtObjects,
        std::unordered_map<std::string, Image>& imgObjects, std::unordered_map<std::string, Triangle>& triObjects, std::unordered_map<std::string, Line>& lnObjects, std::unordered_map<std::string, Quad>& quadObjects, std::unordered_map<std::string, Camera>& camObjects);

    void BuildRenderQueue(std::unordered_map<std::string, Text>& txtObjects, std::unordered_map<std::string, Image>& imgObjects,
        std::unordered_map<std::string, Triangle>& triObjects, std::unordered_map<std::string, Line>& lnObjects, std::unordered_map<std::string, Quad>& quadObjects);

    void FlushRenderQueue(ID3D12GraphicsCommandList* commandList);

    void BeginBatch(RenderBatchType batchType, ID3D12GraphicsCommandList* commandList);

    void EndBatch(RenderBatchType batchType);

    void RenderCameraComponents(ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Camera>& camObjects);

    void PrepareDeviceDependentResources(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12Device* device, std::unordered_map<std::string, Image>& imgObjects, std::unordered_map<std::string, Camera>& camObjects);

    void PrepareWindowDependentResources(RECT size, const D3D12_VIEWPORT& viewport, std::unordered_map<std::string, Camera>& camObjects);

    void ResetAssets(std::unordered_map<std::string, Image>& imgObjects, std::unordered_map<std::string, Camera>& camObjects);

    void UpdateCollisions();

    void PrepareCameraObjects(Camera& camObject, ID3D12Device* device, ResourceUploadBatch& resourceUpload, std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors, const std::unique_ptr<DX::DeviceResources>& m_deviceResources);

    // Getters & Setters.
    Camera* GetFocusedCamera();
};