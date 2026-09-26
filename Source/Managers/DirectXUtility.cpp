#include "pch.h"
#include "DirectXUtility.h"
#include "GameObjectManager.h"

DirectXUtility::DirectXUtility()
{   
    resourceManager = GameObjectManager::GetInstance();
}

void DirectXUtility::AwakeGameObjects()
{
    std::unordered_map<std::string, GameObject>& gameObjs = resourceManager->GetBank<GameObject>();

    for (auto& curr : gameObjs)
    {
        curr.second.Awake();
    }
}

void DirectXUtility::UpdateGameObjects(float elapsedTime)
{
    frameCount++;

    std::unordered_map<std::string, GameObject>& gameObjs = resourceManager->GetBank<GameObject>();

    for (auto& curr : gameObjs)
    {
        curr.second.Update(elapsedTime);
    }
}

void DirectXUtility::CleanScreen(const std::unique_ptr<DX::DeviceResources>& m_deviceResources)
{
    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Clear");

    // Clear the views.
    auto const rtvDescriptor = m_deviceResources->GetRenderTargetView();
    auto const dsvDescriptor = m_deviceResources->GetDepthStencilView();

    commandList->OMSetRenderTargets(1, &rtvDescriptor, FALSE, &dsvDescriptor);
    commandList->ClearRenderTargetView(rtvDescriptor, DirectX::Colors::AliceBlue, 0, nullptr);
    commandList->ClearDepthStencilView(dsvDescriptor, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    // Set the viewport and scissor rect.
    auto const viewport = m_deviceResources->GetScreenViewport();
    auto const scissorRect = m_deviceResources->GetScissorRect();
    commandList->RSSetViewports(1, &viewport);
    commandList->RSSetScissorRects(1, &scissorRect);

    PIXEndEvent(commandList);
}

void DirectXUtility::RenderAllGameObjects(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Text>& txtObjects,
    std::unordered_map<std::string, Image>& imgObjects, std::unordered_map<std::string, Triangle>& triObjects, std::unordered_map<std::string, Line>& lnObjects, std::unordered_map<std::string, Quad>& quadObjects, std::unordered_map<std::string, Camera>& camObjects)
{
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Render");

    auto viewport = m_deviceResources->GetOutputSize();
    width = static_cast<float>(viewport.right - viewport.left);
    height = static_cast<float>(viewport.bottom - viewport.top);

    focusedCamera = GetFocusedCamera();
    focusedCamera->SetScreenSizeHalved(width, height);

    ID3D12DescriptorHeap* heaps[] =
    {
        m_resourceDescriptors->Heap(),
        focusedCamera->GetPtrStates()->Heap()
    };

    commandList->SetDescriptorHeaps(static_cast<UINT>(std::size(heaps)), heaps);

    DirectX::SimpleMath::Vector2 player = focusedCamera ? DirectX::SimpleMath::Vector2(focusedCamera->GetParent()->GetRenderPosition()) : Vector2::Zero;

    focusedCamera->PrepareProjection(player, {width, height});


    // Render Camera Objects
    RenderCameraComponents(commandList, camObjects);

    // Collect every visible renderable, sort it by depth, then draw.
    BuildRenderQueue(txtObjects, imgObjects, triObjects, lnObjects, quadObjects);
    FlushRenderQueue(commandList);

    PIXEndEvent(commandList);

    // Show the new frame.
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
    m_deviceResources->Present();
    m_graphicsMemory->Commit(m_deviceResources->GetCommandQueue());

    PIXEndEvent();
}

void DirectXUtility::BuildRenderQueue(std::unordered_map<std::string, Text>& txtObjects, std::unordered_map<std::string, Image>& imgObjects,
    std::unordered_map<std::string, Triangle>& triObjects, std::unordered_map<std::string, Line>& lnObjects, std::unordered_map<std::string, Quad>& quadObjects)
{
    renderQueue.clear();

    // Objects are collected in their historical draw order so that a stable
    // sort keeps the previous behaviour whenever two objects share a z value.
    for (auto& [_, txt] : txtObjects)
    {
        if (focusedCamera->CanRender(txt.GetRenderPosition(), txt.GetDimensions()))
        {
            RenderEntry entry;
            entry.depth = txt.GetZ();
            entry.batchType = RenderBatchType::Sprite;
            entry.text = &txt;
            renderQueue.push_back(entry);
        }
    }

    for (auto& [_, img] : imgObjects)
    {
        if (focusedCamera->CanRender(img.GetRenderPosition(), img.GetDimensions()))
        {
            RenderEntry entry;
            entry.depth = img.GetZ();
            entry.batchType = RenderBatchType::Sprite;
            entry.image = &img;
            renderQueue.push_back(entry);
        }
    }

    for (auto& [_, tri] : triObjects)
    {
        if (focusedCamera->CanRender(tri.GetRenderPosition(), tri.GetDimensions()))
        {
            RenderEntry entry;
            entry.depth = tri.GetZ();
            entry.batchType = RenderBatchType::Shape;
            entry.shape = &tri;
            renderQueue.push_back(entry);
        }
    }

    for (auto& [_, quad] : quadObjects)
    {
        if (focusedCamera->CanRender(quad.GetRenderPosition(), quad.GetDimensions()))
        {
            RenderEntry entry;
            entry.depth = quad.GetZ();
            entry.batchType = RenderBatchType::Shape;
            entry.shape = &quad;
            renderQueue.push_back(entry);
        }
    }

    for (auto& [_, line] : lnObjects)
    {
        if (focusedCamera->CanRender(line.GetRenderPosition(), line.GetDimensions()))
        {
            RenderEntry entry;
            entry.depth = line.GetZ();
            entry.batchType = RenderBatchType::Line;
            entry.line = &line;
            renderQueue.push_back(entry);
        }
    }

    // Painter's algorithm: draw the deepest objects first so that the lowest
    // z values end up on top, matching Unity's convention.
    std::stable_sort(renderQueue.begin(), renderQueue.end(),
        [](const RenderEntry& lhs, const RenderEntry& rhs)
        {
            return lhs.depth > rhs.depth;
        });
}

void DirectXUtility::BeginBatch(RenderBatchType batchType, ID3D12GraphicsCommandList* commandList)
{
    switch (batchType)
    {
    case RenderBatchType::Sprite:
        m_spriteBatch->Begin(commandList);
        break;

    case RenderBatchType::Shape:
        m_effect->Apply(commandList);
        m_batch->Begin(commandList);
        break;

    case RenderBatchType::Line:
        m_lineEffect->SetView(focusedCamera->GetProjection());
        m_lineEffect->Apply(commandList);
        m_batch->Begin(commandList);
        break;

    default:
        break;
    }
}

void DirectXUtility::EndBatch(RenderBatchType batchType)
{
    switch (batchType)
    {
    case RenderBatchType::Sprite:
        m_spriteBatch->End();
        break;

    case RenderBatchType::Shape:
    case RenderBatchType::Line:
        m_batch->End();
        break;

    default:
        break;
    }
}

void DirectXUtility::FlushRenderQueue(ID3D12GraphicsCommandList* commandList)
{
    RenderBatchType activeBatch = RenderBatchType::None;

    for (const RenderEntry& entry : renderQueue)
    {
        // Objects of different kinds need different batches/effects, so only
        // reopen a batch when the required one actually changes.
        if (entry.batchType != activeBatch)
        {
            EndBatch(activeBatch);
            BeginBatch(entry.batchType, commandList);
            activeBatch = entry.batchType;
        }

        const DirectX::SimpleMath::Vector2& camOffset = focusedCamera->GetOffset();

        if (entry.text != nullptr)
        {
            entry.text->SetOrigin(m_font);
            entry.text->Draw(m_font, m_spriteBatch, camOffset);
        }
        else if (entry.image != nullptr)
        {
            entry.image->Render(m_spriteBatch, m_resourceDescriptors, camOffset);
        }
        else if (entry.shape != nullptr)
        {
            entry.shape->Draw(m_batch, camOffset);
        }
        else if (entry.line != nullptr)
        {
            entry.line->DrawStickOrientation(m_batch, camOffset);
        }
    }

    EndBatch(activeBatch);
}

void DirectXUtility::PrepareDeviceDependentResources(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12Device* device, std::unordered_map<std::string, Image>& imgObjects, std::unordered_map<std::string, Camera>& camObjects)
{
    m_graphicsMemory = std::make_unique<GraphicsMemory>(device);

    m_resourceDescriptors = std::make_unique<DescriptorHeap>(device,
        EnumData::Descriptors::Count);

    ResourceUploadBatch resourceUpload(device);

    resourceUpload.Begin();

    m_font = std::make_unique<SpriteFont>(device, resourceUpload,
        L"myfile.spritefont",
        m_resourceDescriptors->GetCpuHandle(EnumData::Descriptors::MyFont),
        m_resourceDescriptors->GetGpuHandle(EnumData::Descriptors::MyFont));

    for (auto& current : imgObjects)
    {
        current.second.PrepareResources(device, resourceUpload, m_resourceDescriptors);
    }

    for (auto& current : camObjects)
    {
        PrepareCameraObjects(current.second, device, resourceUpload, m_resourceDescriptors, m_deviceResources);
    }

    // Draw Resources
    RenderTargetState rtState(m_deviceResources->GetBackBufferFormat(),
        m_deviceResources->GetDepthBufferFormat());

    SpriteBatchPipelineStateDescription pd(rtState);
    m_spriteBatch = std::make_unique<SpriteBatch>(device, resourceUpload, pd);
    // --------------

    // SET IMAGE PIVOT
    for (auto& current : imgObjects)
    {
        current.second.SetImageOrigin();
    }
    // ------------------

    auto uploadResourcesFinished = resourceUpload.End(
        m_deviceResources->GetCommandQueue());

    // -- Prepare SHAPE/LINE Render --
    m_batch = std::make_unique<PrimitiveBatch<VertexType>>(device);

    EffectPipelineStateDescription ed(
        &VertexType::InputLayout,
        CommonStates::Opaque,
        CommonStates::DepthDefault,
        CommonStates::CullNone,
        rtState);

    EffectPipelineStateDescription line_pd(
        &VertexPositionColor::InputLayout,
        CommonStates::Opaque,
        CommonStates::DepthDefault,
        CommonStates::CullNone,
        rtState,
        D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);

    m_effect = std::make_unique<BasicEffect>(device, EffectFlags::VertexColor, ed);
    m_lineEffect = std::make_unique<BasicEffect>(device, EffectFlags::VertexColor, line_pd);
    // --------------------------

    uploadResourcesFinished.wait();

    m_deviceResources->WaitForGpu();
}

void DirectXUtility::PrepareWindowDependentResources(RECT size, const D3D12_VIEWPORT& viewport, std::unordered_map<std::string, Camera>& camObjects)
{
    m_spriteBatch->SetViewport(viewport);

    Matrix proj;

    proj = Matrix::CreateScale(2.f / float(size.right), -2.f / float(size.bottom), 1.f) * Matrix::CreateTranslation(-1.f, 1.f, 0.f);

    m_effect->SetProjection(proj);
    m_lineEffect->SetProjection(proj);
}

void DirectXUtility::ResetAssets(std::unordered_map<std::string, Image>& imgObjects, std::unordered_map<std::string, Camera>& camObjects)
{
    m_graphicsMemory.reset();
    m_spriteBatch.reset();
    m_font.reset();

    for (auto& current : imgObjects)
    {
        current.second.ResetTexture();
    }

    for (auto& current : camObjects)
    {
        current.second.ResetResources();
    }

    m_resourceDescriptors.reset();
    m_effect.reset();
    m_lineEffect.reset();
    m_batch.reset();
}

void DirectXUtility::UpdateCollisions()
{
    std::unordered_map<int, std::unordered_map<std::string, BoxCollider>>& colliderLayers = resourceManager->GetColliderObjBank();
    std::vector<std::pair<int, int>>& colliderPairs = resourceManager->GetColliderLayerPairs();

    for (int i = 0; i < colliderPairs.size(); i++)
    {
        for (auto& curr_firstCollider : colliderLayers[colliderPairs[i].first])
        {
            for (auto& curr_SecCollider : colliderLayers[colliderPairs[i].second])
            {
                curr_firstCollider.second.IsColliding_SAT(curr_SecCollider.second);
            }
        }
    }
}

void DirectXUtility::RenderCameraComponents(ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Camera>& camObjects)
{
    for (auto& [_, current] : camObjects)
    {
        if (current.GetFocus())
        {
            current.Render(commandList);
        }
    }
}

void DirectXUtility::PrepareCameraObjects(Camera& camObject, ID3D12Device* device, ResourceUploadBatch& resourceUpload, 
    std::unique_ptr<DirectX::DescriptorHeap>& m_resourceDescriptors, const std::unique_ptr<DX::DeviceResources>& m_deviceResources)
{
    camObject.PrepareResources(device);

    RenderTargetState rtState(m_deviceResources->GetBackBufferFormat(),
        m_deviceResources->GetDepthBufferFormat());

    EffectPipelineStateDescription sd(
        &GeometricPrimitive::VertexType::InputLayout,
        CommonStates::Opaque,
        CommonStates::DepthDefault,
        CommonStates::CullCounterClockwise,
        rtState);

    camObject.GetPtrRoomEffect() = std::make_shared<BasicEffect>(device,
        EffectFlags::Lighting | EffectFlags::Texture, sd);
    camObject.GetPtrRoomEffect()->EnableDefaultLighting();

    DX::ThrowIfFailed(CreateDDSTextureFromFile(device, resourceUpload,
        L"roomtexture.dds",
        camObject.GetPtrRoomTex().ReleaseAndGetAddressOf()));

    camObject.GetPtrRoomEffect()->SetTexture(m_resourceDescriptors->GetFirstGpuHandle(),
        camObject.GetPtrStates()->LinearClamp());
}

Camera* DirectXUtility::GetFocusedCamera()
{
    for (auto& [name, cam] : resourceManager->GetBank<Camera>())
    {
        if (cam.GetFocus()) {
            return &cam;
        }
    }

    return nullptr;
}