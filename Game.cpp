//
// Game.cpp
//
#include "pch.h"
#include "Game.h"
#include <iostream>

namespace
{
    const XMVECTORF32 START_POSITION = { 0.f, -1.5f, 0.f, 0.f };
    const XMVECTORF32 ROOM_BOUNDS = { 8.f, 6.f, 12.f, 0.f };
    constexpr float ROTATION_GAIN = 0.1f;
}

Game::Game() noexcept(false) :
    m_pitch(0),
    m_yaw(0),
    m_cameraPos(START_POSITION),
    m_roomColor(Colors::White)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
    if (m_deviceResources)
    {
        m_deviceResources->WaitForGpu();
    }
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{   
    const char* message = "Hello, Output window!";
    OutputDebugStringA(message);

    m_deviceResources->SetWindow(window, width, height);

    auto size = m_deviceResources->GetOutputSize();

    directXUtility = DirectXUtility();

    float horizontal = float(size.right);
    float vertical = float(size.bottom);

    m_deviceResources->CreateDeviceResources();

    m_deviceResources->CreateWindowSizeDependentResources();

    gameWorld.Initialize();

    directXUtility.AwakeGameObjects();
    CreateDeviceDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");

    float elapsedTime = float(timer.GetElapsedSeconds());

    // -- TEST CODE FOR MOVING CAMERA --
    DirectX::SimpleMath::Vector2 input = inputManager->leftStickPos;
    if (inputManager->isConnected)
    {
        if (inputManager->leftStick)
        {
            m_yaw = m_pitch = 0.f;
        }
        else
        {
            m_yaw += -inputManager->leftStickPos.x * ROTATION_GAIN;
            m_pitch += inputManager->leftStickPos.y * ROTATION_GAIN;
            m_cameraPos.x += inputManager->leftStickPos.x;
        }
    }

    // TODO: Add your game logic here.
    inputManager->UpdateButtons();

    // Camera relevent logic.
    constexpr float limit = XM_PIDIV2 - 0.01f;
    m_pitch = std::max(-limit, m_pitch);
    m_pitch = std::min(+limit, m_pitch);

    if (m_yaw > XM_PI)
    {
        m_yaw -= XM_2PI;
    }
    else if (m_yaw < -XM_PI)
    {
        m_yaw += XM_2PI;
    }

    float y = sinf(m_pitch);
    float r = cosf(m_pitch);
    float z = r * cosf(m_yaw);
    float x = r * sinf(m_yaw);

    XMVECTOR lookAt = m_cameraPos + Vector3(x, y, z);

    m_view = XMMatrixLookAtRH(m_cameraPos, lookAt, Vector3::Up);

    directXUtility.UpdateGameObjects(elapsedTime);

    elapsedTime;

    PIXEndEvent();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    // Prepare the command list to render a new frame.
    m_deviceResources->Prepare();
    directXUtility.CleanScreen(m_deviceResources);

    auto commandList = m_deviceResources->GetCommandList();
    directXUtility.RenderAllGameObjects(m_deviceResources, commandList, resourceManager->GetTxtObjBank(), resourceManager->GetImgObjBank(), resourceManager->GetTriObjBank(), resourceManager->GetLnObjBank(), resourceManager->GetQuadObjBank());

    ID3D12DescriptorHeap* heaps[] = {
        m_resourceDescriptors->Heap(), m_states->Heap()
    };
    commandList->SetDescriptorHeaps(static_cast<UINT>(std::size(heaps)),
        heaps);

    m_roomEffect->SetMatrices(Matrix::Identity, m_view, m_proj);
    m_roomEffect->SetDiffuseColor(m_roomColor);
    m_roomEffect->Apply(commandList);
    m_room->Draw(commandList);
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Clear");

    // Clear the views.
    auto const rtvDescriptor = m_deviceResources->GetRenderTargetView();
    auto const dsvDescriptor = m_deviceResources->GetDepthStencilView();

    commandList->OMSetRenderTargets(1, &rtvDescriptor, FALSE, &dsvDescriptor);
    commandList->ClearRenderTargetView(rtvDescriptor, Colors::AliceBlue, 0, nullptr);
    commandList->ClearDepthStencilView(dsvDescriptor, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    // Set the viewport and scissor rect.
    auto const viewport = m_deviceResources->GetScreenViewport();
    auto const scissorRect = m_deviceResources->GetScissorRect();
    commandList->RSSetViewports(1, &viewport);
    commandList->RSSetScissorRects(1, &scissorRect);

    PIXEndEvent(commandList);
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
    inputManager->ResumeGamepad();
    inputManager->ResetButtons();
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
    inputManager->SuspendGamepad();
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
    inputManager->SuspendGamepad();
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
    inputManager->ResumeGamepad();
    inputManager->ResetButtons();
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1300;
    height = 975;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // Check Shader Model 6 support
    D3D12_FEATURE_DATA_SHADER_MODEL shaderModel = { D3D_SHADER_MODEL_6_0 };
    if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel)))
        || (shaderModel.HighestShaderModel < D3D_SHADER_MODEL_6_0))
    {
#ifdef _DEBUG
        OutputDebugStringA("ERROR: Shader Model 6.0 is not supported!\n");
#endif
        throw std::runtime_error("Shader Model 6.0 is not supported!");
    }

    directXUtility.PrepareDeviceDependentResources(m_deviceResources, device, resourceManager->GetImgObjBank());

    m_resourceDescriptors = std::make_unique<DescriptorHeap>(device, 1);

    m_states = std::make_unique<CommonStates>(device);

    m_room = GeometricPrimitive::CreateBox(
        XMFLOAT3(ROOM_BOUNDS[0], ROOM_BOUNDS[1], ROOM_BOUNDS[2]),
        false, true);

    RenderTargetState rtState(m_deviceResources->GetBackBufferFormat(),
        m_deviceResources->GetDepthBufferFormat());

    {
        EffectPipelineStateDescription pd(
            &GeometricPrimitive::VertexType::InputLayout,
            CommonStates::Opaque,
            CommonStates::DepthDefault,
            CommonStates::CullCounterClockwise,
            rtState);

        m_roomEffect = std::make_unique<BasicEffect>(device,
            EffectFlags::Lighting | EffectFlags::Texture, pd);
        m_roomEffect->EnableDefaultLighting();
    }

    ResourceUploadBatch resourceUpload(device);

    resourceUpload.Begin();

    DX::ThrowIfFailed(CreateDDSTextureFromFile(device, resourceUpload,
        L"roomtexture.dds",
        m_roomTex.ReleaseAndGetAddressOf()));

    CreateShaderResourceView(device, m_roomTex.Get(),
        m_resourceDescriptors->GetFirstCpuHandle());

    m_roomEffect->SetTexture(m_resourceDescriptors->GetFirstGpuHandle(),
        m_states->LinearClamp());

    auto uploadResourcesFinished = resourceUpload.End(
        m_deviceResources->GetCommandQueue());
    uploadResourcesFinished.wait();

    m_deviceResources->WaitForGpu();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
    auto viewport = m_deviceResources->GetScreenViewport();

    auto size = m_deviceResources->GetOutputSize();

    float horizontal = float(size.right);
    float vertical = float(size.bottom);

    m_proj = Matrix::CreatePerspectiveFieldOfView(
        XMConvertToRadians(70.f),
        float(size.right) / float(size.bottom), 0.01f, 100.f);

    std::unordered_map<std::string, GameObject>& gameObjs = resourceManager->GetGameObjBank();

    for (auto &curr : gameObjs)
    {
        //curr.second.SetPosition({horizontal, vertical});
        curr.second.CalcScale(std::min(horizontal, vertical));
    }

    directXUtility.PrepareWindowDependentResources(size, viewport);
}

void Game::OnDeviceLost()
{
    // Resets Assets
    directXUtility.ResetAssets(resourceManager->GetImgObjBank());
    m_room.reset();
    m_roomTex.Reset();
    m_resourceDescriptors.reset();
    m_states.reset();
    m_roomEffect.reset();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}

#pragma endregion