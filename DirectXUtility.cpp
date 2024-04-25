#pragma once

#include "pch.h"
#include "DirectXUtility.h"
#include "GameObjectManager.h"

DirectXUtility::DirectXUtility()
{   
    resourceManager = GameObjectManager::GetInstance();
}

void DirectXUtility::AwakeGameObjects()
{
    std::unordered_map<std::string, GameObject>& gameObjs = resourceManager->GetGameObjBank();

    for (auto& curr : gameObjs)
    {
        curr.second.Awake();
    }
}

void DirectXUtility::UpdateGameObjects(float elapsedTime)
{
    std::unordered_map<std::string, GameObject>& gameObjs = resourceManager->GetGameObjBank();
    std::unordered_map<int, std::unordered_map<std::string, BoxCollider>>& colliderLayers = resourceManager->GetColliderObjBank();

    for (auto& curr : gameObjs)
    {
        curr.second.Update(elapsedTime);
    }

    // CHeck for any collisions.
    for (auto& curr_layer : colliderLayers)
    {
        for (auto& curr_child : curr_layer.second)
        {
            for (auto& curr_child2 : curr_layer.second)
            {
                if (curr_child.first != curr_child2.first)
                {
                    curr_child.second.IsColliding_DIAG_STATIC(curr_child2.second);
                }
            }
        }
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
    std::unordered_map<std::string, Image>& imgObjects, std::unordered_map<std::string, Triangle>& triObjects, std::unordered_map<std::string, Line>& lnObjects, std::unordered_map<std::string, Quad>& quadObjects)
{
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Render");

    ID3D12DescriptorHeap* heaps[] = { m_resourceDescriptors->Heap() };
    commandList->SetDescriptorHeaps(static_cast<UINT>(std::size(heaps)), heaps);

    // --- Controller ---
    // Render Text and Image objects
    RenderSpriteBatchObjects(commandList, txtObjects, imgObjects);

    // Render Triangles
    RenderShapeObjects(commandList, triObjects);

    // Render all shape objects
    RenderShapeObjects(commandList, quadObjects);

    // Render Lines
    RenderLineObjects(commandList, lnObjects);
    // ------------------

    PIXEndEvent(commandList);

    // Show the new frame.
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
    m_deviceResources->Present();
    m_graphicsMemory->Commit(m_deviceResources->GetCommandQueue());

    PIXEndEvent();
}

void DirectXUtility::RenderSpriteBatchObjects(ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Text>& txtObjects, std::unordered_map<std::string, Image>& imgObjects)
{
    m_spriteBatch->Begin(commandList);
    // -- RENDER TEXT --
    // Prepare the text.

    for (auto& current : txtObjects)
    {
        current.second.SetOrigin(m_font);
        current.second.DrawText(m_font, m_spriteBatch);
    }
    //------------------

    // -- RENDER IMAGE --
    for (auto& current : imgObjects)
    {
        current.second.RenderImage(m_spriteBatch, m_resourceDescriptors);
    }
    // ------------------

    m_spriteBatch->End();
}

void DirectXUtility::RenderShapeObjects(ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Triangle>& shpObjects)
{
    m_effect->Apply(commandList);

    m_batch->Begin(commandList);

    CheckInputs(shpObjects);

    m_batch->End();
}

void DirectXUtility::RenderShapeObjects(ID3D12GraphicsCommandList* commandList, const std::unordered_map<std::string, Quad>& quadObjects)
{
    m_effect->Apply(commandList);

    m_batch->Begin(commandList);

    for (const auto& currObject : quadObjects)
    {
        currObject.second.Draw(m_batch);
    }

    m_batch->End();
}

void DirectXUtility::RenderLineObjects(ID3D12GraphicsCommandList* commandList, std::unordered_map<std::string, Line>& lnObjects)
{
    m_lineEffect->Apply(commandList);

    m_batch->Begin(commandList);

    for (auto& current : lnObjects)
    {
        current.second.DrawStickOrientation(m_batch);
    }

    m_batch->End();
}

void DirectXUtility::PrepareDeviceDependentResources(const std::unique_ptr<DX::DeviceResources>& m_deviceResources, ID3D12Device* device, std::unordered_map<std::string, Image>& imgObjects)
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

    // ----- PREPARE SPRITE -----
    for (auto& current : imgObjects)
    {
        current.second.PrepareImageResources(device, resourceUpload, m_resourceDescriptors);
    }
    //-----------------------------

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
}

void DirectXUtility::PrepareWindowDependentResources(RECT size, const D3D12_VIEWPORT& viewport)
{
    m_spriteBatch->SetViewport(viewport);

    Matrix proj = Matrix::CreateScale(2.f / float(size.right), -2.f / float(size.bottom), 1.f) * Matrix::CreateTranslation(-1.f, 1.f, 0.f);

    m_effect->SetProjection(proj);
    m_lineEffect->SetProjection(proj);
}

void DirectXUtility::CheckInputs(const std::unordered_map<std::string, Triangle>& shpObjects)
{
    // All the triangle's position have to be relative to the image positions.
    // Iterate through UI button class so that we can basically have a single for loop and call the set position and draw triangle once.

    for (const auto& currObject : shpObjects)
    {
        currObject.second.Draw(m_batch);
    }
}

void DirectXUtility::ResetAssets(std::unordered_map<std::string, Image>& imgObjects)
{
    m_graphicsMemory.reset();
    m_spriteBatch.reset();
    m_font.reset();

    for (auto& current : imgObjects)
    {
        current.second.ResetTexture();
    }

    m_resourceDescriptors.reset();
    m_effect.reset();
    m_lineEffect.reset();
    m_batch.reset();
}