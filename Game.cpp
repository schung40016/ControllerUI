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

    auto size = m_deviceResources->GetOutputSize();

    float horizontal = float(size.right);
    float vertical = float(size.bottom);

    controller = GameObject((horizontal / 2.f), (vertical / 2.f), std::min(horizontal, vertical));

    tTitle = Text(Colors::Black, "ControllerUI", controller, 0, -250.f);
    tConnect = Text(Colors::Black, "Controller Connection: ", controller, -50.f, 250.f);
    tStatus = Text(Colors::Black, "Connected", controller, 300.f, 250.f);

    // Create a higher tier object to act as the parent for all these objects.
    controllerImg = Image(Colors::White, ".\\Images\\gamepad.png", controller, 0.f, 0.f, 1.f);
    leftTrigger = Image(Colors::White, ".\\Images\\LeftTrigger.png", controller, -290.f, -140.f, 1.f);
    rightTrigger = Image(Colors::White, ".\\Images\\RightTrigger.png", controller, 290.f, -140.f, 1.f);

    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, 108.f, -78.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, 148.f, -120.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, 68.f, -120.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, 108.f, -160.f));

    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, 0.f, -120.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, -90.f, -120.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, -123.f, -60.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, -123.f, 10.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, -160.f, -25.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, -80.f, -25.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, -200.f, -220.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, 100.f, -220.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, leftTrigger, 1.f, -50.f, -30.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, rightTrigger, 1.f, -50.f, -30.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, -198.f, -120.f));
    buttonIndBank.push_back(Triangle(Colors::HotPink, controllerImg, 1.f, 32.f, -25.f));

    leftStick = Line(Colors::HotPink, controllerImg, -148.f, -78.f, 1.f);
    rightStick = Line(Colors::HotPink, controllerImg, 80.f, 15.f, 1.f);


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

        buttonIndBank[0].SetDisplay(pad.IsAPressed());
        buttonIndBank[1].SetDisplay(pad.IsBPressed());
        buttonIndBank[2].SetDisplay(pad.IsXPressed());
        buttonIndBank[3].SetDisplay(pad.IsYPressed());
        buttonIndBank[4].SetDisplay(pad.IsStartPressed());
        buttonIndBank[5].SetDisplay(pad.IsViewPressed());

        // Dpad
        buttonIndBank[6].SetDisplay(pad.IsDPadUpPressed());
        buttonIndBank[7].SetDisplay(pad.IsDPadDownPressed());
        buttonIndBank[8].SetDisplay(pad.IsDPadLeftPressed());
        buttonIndBank[9].SetDisplay(pad.IsDPadRightPressed());

        // Front Controller
        buttonIndBank[10].SetDisplay(pad.IsLeftShoulderPressed());
        buttonIndBank[11].SetDisplay(pad.IsRightShoulderPressed());
        buttonIndBank[12].SetDisplay(pad.IsLeftTriggerPressed());
        buttonIndBank[13].SetDisplay(pad.IsRightTriggerPressed());

        // Sticks
        SetTriggerPosition(pad);
        buttonIndBank[14].SetDisplay(pad.IsLeftStickPressed());
        buttonIndBank[15].SetDisplay(pad.IsRightStickPressed());
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
    controllerImg.RenderImage(m_spriteBatch, m_resourceDescriptors, Descriptors::Controller);
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
    controllerImg.PrepareImageResources(device, resourceUpload, m_resourceDescriptors, Descriptors::Controller);
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
    controllerImg.SetImageOrigin();
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

    controller.SetPosition((horizontal / 2.f), (vertical / 2.f));
    controller.CalcScale(std::min(horizontal, vertical));

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

    controllerImg.ResetTexture();
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
    // Iterate through UI button class so that we can basically have a single for loop and call the set position and draw triangle once.

    for (Triangle& currObject : buttonIndBank)
    {
        if (currObject.GetDisplay())
        {
            currObject.Draw(m_batch);
        }
    }
}
#pragma endregion