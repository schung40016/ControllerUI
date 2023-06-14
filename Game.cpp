//
// Game.cpp
//
#include "pch.h"
#include "Game.h"
#include <iostream>

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

    auto size = m_deviceResources->GetOutputSize();

    //controller = Image(Colors::White, 2.f, 2.f, ".\\Images\\gamepad.png", size);
    //leftTrigger = Image(Colors::White, 7.f, 4.f, ".\\Images\\LeftTrigger.png", size);
    //rightTrigger = Image(Colors::White, 1.17f, 4.f, ".\\Images\\RightTrigger.png", size);
    leftStick = Line();
    leftStick.SetColor(Colors::HotPink);
    rightStick = Line();
    rightStick.SetColor(Colors::HotPink);

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

        indA.SetDisplay(pad.IsAPressed());
        indB.SetDisplay(pad.IsBPressed());
        indX.SetDisplay(pad.IsXPressed());
        indY.SetDisplay(pad.IsYPressed());
        indStart.SetDisplay(pad.IsStartPressed());
        indView.SetDisplay(pad.IsViewPressed());

        // Dpad
        indDPadUp.SetDisplay(pad.IsDPadUpPressed());
        indDPadDown.SetDisplay(pad.IsDPadDownPressed());
        indDPadLeft.SetDisplay(pad.IsDPadLeftPressed());
        indDPadRight.SetDisplay(pad.IsDPadRightPressed());

        // Front Controller
        indLeftShoulder.SetDisplay(pad.IsLeftShoulderPressed());
        indRightShoulder.SetDisplay(pad.IsRightShoulderPressed());
        indLeftTrigger.SetDisplay(pad.IsLeftTriggerPressed());
        indRightTrigger.SetDisplay(pad.IsRightTriggerPressed());

        // Sticks
        SetTriggerPosition(pad);
        indLeftStick.SetDisplay(pad.IsLeftStickPressed());
        indRightStick.SetDisplay(pad.IsRightStickPressed());
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

    leftStick.SetVec1(m_controllerPos.x - 148.f, m_controllerPos.y - 78.f);
    rightStick.SetVec1(m_controllerPos.x + 80.f, m_controllerPos.y + 15.f);
    leftStick.DrawStickOrientation(m_batch);
    rightStick.DrawStickOrientation(m_batch);

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

    //controller.SetOrigin(controllerSize);
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

    std::cout << size.right << ", " << size.bottom << std::endl;

    imageHelper.SetImagePosition(m_titlePos, size, 2.f, 10.f);
    imageHelper.SetImagePosition(m_connectPos, size, 4.f, 1.1f);
    imageHelper.SetImagePosition(m_statusPos, size, 1.f, 1.1f);
    imageHelper.SetImagePosition(m_controllerPos, size, 2.f, 2.f);
    imageHelper.SetImagePosition(m_leftTriggerPos, size, 7.f, 4.f);
    imageHelper.SetImagePosition(m_rightTriggerPos, size, 1.17f, 4.f);


    Matrix proj = Matrix::CreateScale(2.f / float(size.right), -2.f / float(size.bottom), 1.f) * Matrix::CreateTranslation(-1.f, 1.f, 0.f);

    m_effect->SetProjection(proj);
    m_lineEffect->SetProjection(proj);
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
    leftStick.SetVec2(pad.thumbSticks.leftX, pad.thumbSticks.leftY);
    rightStick.SetVec2(pad.thumbSticks.rightX, pad.thumbSticks.rightY);
}

void Game::CheckInputs()
{
    // All the triangle's position have to be relative to the image positions.

    if (indA.GetDisplay())
    {
        indA.SetPos(m_controllerPos.x + 108.f, m_controllerPos.y - 78.f);
        indA.DrawTriangle(m_batch);
    }
    if (indB.GetDisplay())
    {
        indB.SetPos(m_controllerPos.x + 148.f, m_controllerPos.y - 120.f);
        indB.DrawTriangle(m_batch);
    }
    if (indX.GetDisplay())
    {
        indX.SetPos(m_controllerPos.x + 68.f, m_controllerPos.y - 120.f);
        indX.DrawTriangle(m_batch);
    }
    if (indY.GetDisplay())
    {
        indY.SetPos(m_controllerPos.x + 108.f, m_controllerPos.y - 160.f);
        indY.DrawTriangle(m_batch);
    }
    if (indStart.GetDisplay())
    {
        indStart.SetPos(m_controllerPos.x + 0.f, m_controllerPos.y - 120.f);
        indStart.DrawTriangle(m_batch);
    }
    if (indView.GetDisplay())
    {
        indView.SetPos(m_controllerPos.x - 90.f, m_controllerPos.y - 120.f);
        indView.DrawTriangle(m_batch);
    }
    if (indDPadUp.GetDisplay())
    {
        indDPadUp.SetPos(m_controllerPos.x - 123.f, m_controllerPos.y - 60.f);
        indDPadUp.DrawTriangle(m_batch);
    }
    if (indDPadDown.GetDisplay())
    {
        indDPadDown.SetPos(m_controllerPos.x - 123.f, m_controllerPos.y + 10.f);
        indDPadDown.DrawTriangle(m_batch);
    }
    if (indDPadLeft.GetDisplay())
    {
        indDPadLeft.SetPos(m_controllerPos.x - 160.f, m_controllerPos.y - 25.f);
        indDPadLeft.DrawTriangle(m_batch);
    }
    if (indDPadRight.GetDisplay())
    {
        indDPadRight.SetPos(m_controllerPos.x - 80.f, m_controllerPos.y - 25.f);
        indDPadRight.DrawTriangle(m_batch);
    }
    if (indLeftShoulder.GetDisplay())
    {
        indLeftShoulder.SetPos(m_controllerPos.x - 200.f, m_controllerPos.y - 220.f);
        indLeftShoulder.DrawTriangle(m_batch);
    }
    if (indRightShoulder.GetDisplay())
    {
        indRightShoulder.SetPos(m_controllerPos.x + 100.f, m_controllerPos.y - 220.f);
        indRightShoulder.DrawTriangle(m_batch);
    }
    if (indLeftTrigger.GetDisplay())
    {     
        indLeftTrigger.SetPos(m_leftTriggerPos.x - 50.f, m_leftTriggerPos.y - 30.f);
        indLeftTrigger.DrawTriangle(m_batch);
    }
    if (indRightTrigger.GetDisplay())
    {
        indRightTrigger.SetPos(m_rightTriggerPos.x - 50.f, m_rightTriggerPos.y - 30.f);
        indRightTrigger.DrawTriangle(m_batch);
    }
    if (indLeftStick.GetDisplay())
    {
        indLeftStick.SetPos(m_controllerPos.x - 198.f, m_controllerPos.y - 120.f);
        indLeftStick.DrawTriangle(m_batch);
    }
    if (indRightStick.GetDisplay())
    {
        indRightStick.SetPos(m_controllerPos.x + 32.f, m_controllerPos.y - 25.f);
        indRightStick.DrawTriangle(m_batch);
    }
}
#pragma endregion

/*
Font:
const wchar* text
Vector2 pos
color

Sprite:
Vector2 pos
Vector2 origin
color
XMUIINT32 size
texture

Triangle:
color
v1 
v2
v3

Line
color
v1 // based on gamepad input.
v2 (origin)
*/