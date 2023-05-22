//
// Game.cpp
//
#include "pch.h"
#include "Game.h"

Game::Game() noexcept(false)
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
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

    // Set up gamepad
    m_gamePad = std::make_unique<GamePad>();
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

    // TODO: Add your game logic here.

    // Checks whether user pressed a button
    auto pad = m_gamePad->GetState(0);

    if (pad.IsConnected())
    {
        m_buttons.Update(pad);

        isConnected = pad.IsConnected() ? true : false;

        pressA = pad.IsAPressed() ? true : false;
        pressB = pad.IsBPressed() ? true : false;
        pressX = pad.IsXPressed() ? true : false;
        pressY = pad.IsYPressed() ? true : false;
        pressStart = pad.IsStartPressed() ? true : false;
        pressView = pad.IsViewPressed() ? true : false;

        // DPad
        pressDPadUp = pad.IsDPadUpPressed() ? true : false;
        pressDPadDown = pad.IsDPadDownPressed() ? true : false;
        pressDPadLeft = pad.IsDPadLeftPressed() ? true : false;
        pressDPadRight = pad.IsDPadRightPressed() ? true : false;
        
        // Triggers and Bumpers
        pressLeftShoulder = pad.IsLeftShoulderPressed() ? true : false;
        pressLeftTrigger = pad.IsLeftTriggerPressed() ? true : false;
        pressRightShoulder = pad.IsRightShoulderPressed() ? true : false;
        pressRightTrigger = pad.IsRightTriggerPressed() ? true : false;

        // Thumbsticks.
        SetTriggerPosition(pad);
        pressLeftStick = pad.IsLeftStickPressed() ? true : false;
        pressRightStick = pad.IsRightStickPressed() ? true : false;
    }
    else
    {
        m_buttons.Reset();
    }

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
    Clear();

    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Render");

    // TODO: Add your rendering code here.

    ID3D12DescriptorHeap* heaps[] = { m_resourceDescriptors->Heap() };
    commandList->SetDescriptorHeaps(static_cast<UINT>(std::size(heaps)), heaps);

    m_spriteBatch->Begin(commandList);
    // -- RENDER TEXT --
    // Prepare the text.
    Vector2 titleOrigin = m_font->MeasureString(t_title) / 2.f;
    Vector2 connectOrigin = m_font->MeasureString(t_connection) / 2.f;

    // Draws the font.
    m_font->DrawString(m_spriteBatch.get(), t_title,
        m_titlePos, textColor, 0.f, titleOrigin);

    m_font->DrawString(m_spriteBatch.get(), t_connection,
        m_connectPos, textColor, 0.f, titleOrigin);
    if (isConnected)
    {
        m_font->DrawString(m_spriteBatch.get(), L"On",
            m_statusPos, textColor, 0.f, titleOrigin);
    }
    else
    {
        m_font->DrawString(m_spriteBatch.get(), L"Off",
            m_statusPos, textColor, 0.f, titleOrigin);
    }
    //------------------

    // -- RENDER IMAGE --
    m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(Descriptors::Controller),
        GetTextureSize(m_controllerTexture.Get()),
        m_controllerPos, nullptr, Colors::White, 0.f, m_controllerOrigin);

    m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(Descriptors::LeftTrigger),
        GetTextureSize(m_leftTriggerTexture.Get()),
        m_leftTriggerPos, nullptr, Colors::White, 0.f, m_leftTriggerOrigin);

    m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(Descriptors::RightTrigger),
        GetTextureSize(m_rightTriggerTexture.Get()),
        m_rightTriggerPos, nullptr, Colors::White, 0.f, m_rightTriggerOrigin);
    // ------------------
    m_spriteBatch->End();

    // -- RENDER SHAPE --
    m_effect->Apply(commandList);

    m_batch->Begin(commandList);

    CheckInputs();

    m_batch->End();
    //-------------------

    // -- Render Line --
    m_lineEffect->Apply(commandList);

    m_batch->Begin(commandList);

    DrawStickOrientation(-.37f, 0.255f, leftTriggPos.x, leftTriggPos.y);
    DrawStickOrientation(.2025f, -.05f, rightTriggPos.x, rightTriggPos.y);

    m_batch->End();
    // -----------------

    PIXEndEvent(commandList);

    // Show the new frame.
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
    m_deviceResources->Present();
    m_graphicsMemory->Commit(m_deviceResources->GetCommandQueue());

    PIXEndEvent();
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
    m_gamePad->Resume();
    m_buttons.Reset();
    isConnected = true;
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
    isConnected = false;
    m_gamePad->Suspend();
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
    isConnected = false;
    m_gamePad->Suspend();
}

void Game::OnResuming()
{
    isConnected = true;
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
    m_gamePad->Resume();
    m_buttons.Reset();
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
    width = 800;
    height = 600;
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

    // TODO: Initialize device dependent objects here (independent of window size).
    m_graphicsMemory = std::make_unique<GraphicsMemory>(device);

    m_resourceDescriptors = std::make_unique<DescriptorHeap>(device,
        Descriptors::Count);

    ResourceUploadBatch resourceUpload(device);

    resourceUpload.Begin();

    // ----- TEXT STUFF -----
    // Allocate resources for bitmap.
    m_font = std::make_unique<SpriteFont>(device, resourceUpload,
        L"myfile.spritefont",
        m_resourceDescriptors->GetCpuHandle(Descriptors::MyFont),
        m_resourceDescriptors->GetGpuHandle(Descriptors::MyFont));
    //----------------------

    // ----- CONTROLLER IMAGE -----
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(device, resourceUpload, L".\\Images\\gamepad.png",
            m_controllerTexture.ReleaseAndGetAddressOf()));

    CreateShaderResourceView(device, m_controllerTexture.Get(),
        m_resourceDescriptors->GetCpuHandle(Descriptors::Controller));

    DX::ThrowIfFailed(
        CreateWICTextureFromFile(device, resourceUpload, L".\\Images\\LeftTrigger.png",
            m_leftTriggerTexture.ReleaseAndGetAddressOf()));

    CreateShaderResourceView(device, m_leftTriggerTexture.Get(),
        m_resourceDescriptors->GetCpuHandle(Descriptors::LeftTrigger));

    DX::ThrowIfFailed(
        CreateWICTextureFromFile(device, resourceUpload, L".\\Images\\RightTrigger.png",
            m_rightTriggerTexture.ReleaseAndGetAddressOf()));

    CreateShaderResourceView(device, m_rightTriggerTexture.Get(),
        m_resourceDescriptors->GetCpuHandle(Descriptors::RightTrigger));
    //-----------------------------

    // Draw Resources
    RenderTargetState rtState(m_deviceResources->GetBackBufferFormat(),
        m_deviceResources->GetDepthBufferFormat());

    SpriteBatchPipelineStateDescription pd(rtState);
    m_spriteBatch = std::make_unique<SpriteBatch>(device, resourceUpload, pd);
    // --------------

    // SET CENTER
    XMUINT2 controllerSize = GetTextureSize(m_controllerTexture.Get());
    XMUINT2 leftTriggerSize = GetTextureSize(m_leftTriggerTexture.Get());
    XMUINT2 rightTriggerSize = GetTextureSize(m_rightTriggerTexture.Get());

    imageHelper.SetImagePivot(m_controllerOrigin, controllerSize);
    imageHelper.SetImagePivot(m_leftTriggerOrigin, leftTriggerSize);
    imageHelper.SetImagePivot(m_rightTriggerOrigin, rightTriggerSize);
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

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
    auto viewport = m_deviceResources->GetScreenViewport();
    m_spriteBatch->SetViewport(viewport);

    auto size = m_deviceResources->GetOutputSize();

    imageHelper.SetImagePosition(m_titlePos, size, 2.f, 10.f);
    imageHelper.SetImagePosition(m_connectPos, size, 4.f, 1.1f);
    imageHelper.SetImagePosition(m_statusPos, size, 1.f, 1.1f);
    imageHelper.SetImagePosition(m_controllerPos, size, 2.f, 2.f);
    imageHelper.SetImagePosition(m_leftTriggerPos, size, 7.f, 4.f);
    imageHelper.SetImagePosition(m_rightTriggerPos, size, 1.17f, 4.f);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    m_graphicsMemory.reset();

    // Resets Assets
    ResetAssets();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}

// Custom functions to make things cleaner.
void Game::ResetAssets()
{
    m_spriteBatch.reset();
    m_font.reset();
    m_controllerTexture.Reset();
    m_leftTriggerTexture.Reset();
    m_rightTriggerTexture.Reset();
    m_resourceDescriptors.reset();
    m_effect.reset();
    m_lineEffect.reset();
    m_batch.reset();
}

void Game::SetTriggerPosition(DirectX::GamePad::State pad)
{
    leftTriggPos.x = pad.thumbSticks.leftX;
    leftTriggPos.y = pad.thumbSticks.leftY;
    rightTriggPos.x = pad.thumbSticks.rightX;
    rightTriggPos.y = pad.thumbSticks.rightY;
}

void Game::CheckInputs()
{
    if (pressA)
    {
        DrawTriangle(0.3955f, .13f);
    }
    if (pressB)
    {
        DrawTriangle(0.495f, .27f);
    }
    if (pressX)
    {
        DrawTriangle(0.295f, .27f);
    }
    if (pressY)
    {
        DrawTriangle(0.3955f, .4f);
    }
    if (pressStart)
    {
        DrawTriangle(.12f, .27f);
    }
    if (pressView)
    {
        DrawTriangle(-.105f, .27f);
    }
    if (pressDPadUp)
    {
        DrawTriangle(-.1825f, .05f);
    }
    if (pressDPadDown)
    {
        DrawTriangle(-.1825f, -.14f);
    }
    if (pressDPadLeft)
    {
        DrawTriangle(-.26f, -.045f);
    }
    if (pressDPadRight)
    {
        DrawTriangle(-.105f, -.045f);
    }
    if (pressLeftShoulder)
    {
        DrawTriangle(-.35f, .63f);
    }
    if (pressRightShoulder)
    {
        DrawTriangle(.35f, .63f);
    }
    if (pressLeftTrigger)
    {
        DrawTriangle(-.68f, .52f);
    }
    if (pressRightTrigger)
    {
        DrawTriangle(.68f, .52f);
    }
    if (pressLeftStick)
    {
        DrawTriangle(-.37f, .265f);
    }
    if (pressRightStick)
    {
        DrawTriangle(.205f, -.04f);
    }
}

void Game::DrawTriangle(float x, float y)
{
    VertexPositionColor v1(Vector3(x, y + 0.05f, 0.5f), Colors::LightPink);
    VertexPositionColor v2(Vector3(x + 0.05f, y - 0.05f, 0.5f), Colors::LightPink);
    VertexPositionColor v3(Vector3(x - 0.05f, y - 0.05f, 0.5f), Colors::LightPink);

    m_batch->DrawTriangle(v1, v2, v3);
}

void Game::DrawStickOrientation(float ox, float oy, float p1, float p2)
{
    float calcX = p1 * .08f + ox;
    float calcY = p2 * .11f + oy;

    VertexPositionColor v1(Vector3(ox, oy, 0.5f), Colors::HotPink);
    VertexPositionColor v2(Vector3(calcX, calcY, 0.5f), Colors::HotPink);
    m_batch->DrawLine(v1, v2);
}
#pragma endregion
