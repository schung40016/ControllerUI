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
    tTitle = Text(Colors::Black, "ControllerUI");
    tConnect = Text(Colors::Black, "Controller Connection: ");
    tStatus = Text(Colors::Black, "Connected");

    controller = Image(Colors::White, ".\\Images\\gamepad.png", 1.f);
    leftTrigger = Image(Colors::White, ".\\Images\\LeftTrigger.png", 1.f);
    rightTrigger = Image(Colors::White, ".\\Images\\RightTrigger.png", 1.f);

    indA = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, 108.f, -78.f);
    indB = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, 148.f, -120.f);
    indX = Triangle(Colors::HotPink, controller,1.f, 0.f, 0.f, 68.f, -120.f);
    indY = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, 108.f, -160.f);
    indView = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, 0.f, -120.f);
    indStart = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, -90.f, -120.f);
    indStart = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, -90.f, -120.f);
    indDPadUp = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, -123.f, -60.f);
    indDPadDown = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, -123.f, 10.f);
    indDPadLeft = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, -160.f, -25.f);
    indDPadRight = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, -80.f, -25.f);
    indLeftShoulder = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, -200.f, -220.f);
    indRightShoulder = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, 100.f, -220.f);
    indLeftTrigger = Triangle(Colors::HotPink, leftTrigger, 1.f, 0.f, 0.f, -50.f, -30.f);
    indRightTrigger = Triangle(Colors::HotPink, rightTrigger, 1.f, 0.f, 0.f, -50.f, -30.f);
    indLeftStick = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, -198.f, -120.f);
    indRightStick = Triangle(Colors::HotPink, controller, 1.f, 0.f, 0.f, 32.f, -25.f);

    leftStick = Line(Colors::HotPink, controller, -148.f, -78.f, 30.f);
    rightStick = Line(Colors::HotPink, controller, 80.f, 15.f, 30.f);

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
    tTitle.SetOrigin(m_font);
    tConnect.SetOrigin(m_font);

    tTitle.DrawText(m_font, m_spriteBatch);
    tConnect.DrawText(m_font, m_spriteBatch);

    // Draws the font.

    if (isConnected)
    {
        tStatus.SetText("On");
    }
    else
    {
        tStatus.SetText("Off");
    }

    tStatus.SetOrigin(m_font);
    tStatus.DrawText(m_font, m_spriteBatch);

    //------------------

    // -- RENDER IMAGE --
    controller.RenderImage(m_spriteBatch, m_resourceDescriptors, Descriptors::Controller);
    leftTrigger.RenderImage(m_spriteBatch, m_resourceDescriptors, Descriptors::LeftTrigger);
    rightTrigger.RenderImage(m_spriteBatch, m_resourceDescriptors, Descriptors::RightTrigger);
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

    leftStick.SetPosition();
    rightStick.SetPosition();
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

    // ----- PREPARE SPRITE -----
        // Encapsulation != giving reference. - Charles 2023
    controller.PrepareImageResources(device, resourceUpload, m_resourceDescriptors, Descriptors::Controller);
    leftTrigger.PrepareImageResources(device, resourceUpload, m_resourceDescriptors, Descriptors::LeftTrigger);
    rightTrigger.PrepareImageResources(device, resourceUpload, m_resourceDescriptors, Descriptors::RightTrigger);
    //-----------------------------

    // Draw Resources
    RenderTargetState rtState(m_deviceResources->GetBackBufferFormat(),
        m_deviceResources->GetDepthBufferFormat());

    SpriteBatchPipelineStateDescription pd(rtState);
    m_spriteBatch = std::make_unique<SpriteBatch>(device, resourceUpload, pd);
    // --------------

    // SET IMAGE PIVOT
    controller.SetImageOrigin();
    leftTrigger.SetImageOrigin();
    rightTrigger.SetImageOrigin();
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

    float horizontal = float(size.right);
    float vertical = float(size.bottom);

    tTitle.SetPosition((horizontal / 2.f), (vertical / 10.f));
    tConnect.SetPosition((horizontal / 2.5f), (vertical / 1.1f));
    tStatus.SetPosition((horizontal / 1.2f), (vertical / 1.1f));

    controller.SetPosition((horizontal / 2.f), (vertical / 2.f));
    leftTrigger.SetPosition((horizontal / 7.f), (vertical / 4.f));
    rightTrigger.SetPosition((horizontal /1.17f), (vertical / 4.f));

    Matrix proj = Matrix::CreateScale(2.f / float(size.right), -2.f / float(size.bottom), 1.f) * Matrix::CreateTranslation(-1.f, 1.f, 0.f);

    m_effect->SetProjection( proj);
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

    controller.ResetTexture();
    leftTrigger.ResetTexture();
    rightTrigger.ResetTexture();

    m_resourceDescriptors.reset();
    m_effect.reset();
    m_lineEffect.reset();
    m_batch.reset();
}

void Game::SetTriggerPosition(DirectX::GamePad::State pad)
{
    leftStick.SetPoint2(pad.thumbSticks.leftX, pad.thumbSticks.leftY);
    rightStick.SetPoint2(pad.thumbSticks.rightX, pad.thumbSticks.rightY);
}

void Game::CheckInputs()
{
    // All the triangle's position have to be relative to the image positions.
    DirectX::SimpleMath::Vector2 pos = controller.GetPosition();

    if (indA.GetDisplay())
    {
        indA.SetPosition();
        indA.DrawTriangle(m_batch);
    }
    if (indB.GetDisplay())
    {
        indB.SetPosition();
        indB.DrawTriangle(m_batch);
    }
    if (indX.GetDisplay())
    {
        indX.SetPosition();
        indX.DrawTriangle(m_batch);
    }
    if (indY.GetDisplay())
    {
        indY.SetPosition();
        indY.DrawTriangle(m_batch);
    }
    if (indStart.GetDisplay())
    {
        indStart.SetPosition();
        indStart.DrawTriangle(m_batch);
    }
    if (indView.GetDisplay())
    {
        indView.SetPosition();
        indView.DrawTriangle(m_batch);
    }
    if (indDPadUp.GetDisplay())
    {
        indDPadUp.SetPosition();
        indDPadUp.DrawTriangle(m_batch);
    }
    if (indDPadDown.GetDisplay())
    {
        indDPadDown.SetPosition();
        indDPadDown.DrawTriangle(m_batch);
    }
    if (indDPadLeft.GetDisplay())
    {
        indDPadLeft.SetPosition();
        indDPadLeft.DrawTriangle(m_batch);
    }
    if (indDPadRight.GetDisplay())
    {
        indDPadRight.SetPosition();
        indDPadRight.DrawTriangle(m_batch);
    }
    if (indLeftShoulder.GetDisplay())
    {
        indLeftShoulder.SetPosition();
        indLeftShoulder.DrawTriangle(m_batch);
    }
    if (indRightShoulder.GetDisplay())
    {
        indRightShoulder.SetPosition();
        indRightShoulder.DrawTriangle(m_batch);
    }
    if (indLeftTrigger.GetDisplay())
    {     
        indLeftTrigger.SetPosition();
        indLeftTrigger.DrawTriangle(m_batch);
    }
    if (indRightTrigger.GetDisplay())
    {
        indRightTrigger.SetPosition();
        indRightTrigger.DrawTriangle(m_batch);
    }
    if (indLeftStick.GetDisplay())
    {
        indLeftStick.SetPosition();
        indLeftStick.DrawTriangle(m_batch);
    }
    if (indRightStick.GetDisplay())
    {
        indRightStick.SetPosition();
        indRightStick.DrawTriangle(m_batch);
    }
}
#pragma endregion