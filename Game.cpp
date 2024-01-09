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

    directXUtility = DirectXUtility();

    float horizontal = float(size.right);
    float vertical = float(size.bottom);

    resourceManager = GameObjectManager(horizontal, vertical);

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
    inputManager = InputManager::GetInstance();
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

    inputManager = InputManager::GetInstance();
    // TODO: Add your game logic here.
    inputManager->UpdateButtons();

    std::unordered_map<std::string, Triangle>& triangles = resourceManager.GetTriObjBank();

    triangles["A"].SetDisplay(inputManager->a);
    triangles["B"].SetDisplay(inputManager->b);
    triangles["X"].SetDisplay(inputManager->x);
    triangles["Y"].SetDisplay(inputManager->y);
    triangles["Start"].SetDisplay(inputManager->start);
    triangles["View"].SetDisplay(inputManager->view);

    triangles["DPadUp"].SetDisplay(inputManager->dPadUp);
    triangles["DPadDown"].SetDisplay(inputManager->dPadDown);
    triangles["DPadLeft"].SetDisplay(inputManager->dPadLeft);
    triangles["DPadRight"].SetDisplay(inputManager->dPadRight);

    triangles["LeftShoulder"].SetDisplay(inputManager->leftShoulder);
    triangles["RightShoulder"].SetDisplay(inputManager->rightShoulder);
    triangles["LeftTrigger"].SetDisplay(inputManager->leftTrigger);
    triangles["RightTrigger"].SetDisplay(inputManager->rightTrigger);

    triangles["leftStick"].SetDisplay(inputManager->leftStick);
    triangles["rightStick"].SetDisplay(inputManager->rightStick);

    std::unordered_map<std::string, Line>& lines = resourceManager.GetLnObjBank();

    lines["LeftStick"].SetPoint2(inputManager->leftStickPos.x, inputManager->leftStickPos.y);
    lines["RightStick"].SetPoint2(inputManager->rightStickPos.x, inputManager->rightStickPos.y);

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

    Text& controllerIndicator = resourceManager.GetTxtObjBank()["Status"];

    if (directXUtility.GetControllerConnected())
    {
        controllerIndicator.SetText("On");
    }
    else
    {
        controllerIndicator.SetText("Off");
    }

    auto commandList = m_deviceResources->GetCommandList();
    directXUtility.RenderAllGameObjects(m_deviceResources, commandList, resourceManager.GetTxtObjBank(), resourceManager.GetImgObjBank(), resourceManager.GetTriObjBank(), resourceManager.GetLnObjBank(), resourceManager.GetShpObjBank());
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
    directXUtility.SetControllerConnected(true);
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
    directXUtility.SetControllerConnected(false);
    inputManager->SuspendGamepad();
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
    directXUtility.SetControllerConnected(false);
    inputManager->SuspendGamepad();
}

void Game::OnResuming()
{
    directXUtility.SetControllerConnected(true);
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

    // TODO: Initialize device dependent objects here (independent of window size).
    directXUtility.PrepareDeviceDependentResources(m_deviceResources, device, resourceManager.GetImgObjBank());
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
    auto viewport = m_deviceResources->GetScreenViewport();

    auto size = m_deviceResources->GetOutputSize();

    float horizontal = float(size.right);
    float vertical = float(size.bottom);

    GameObject& controller = resourceManager.GetGameObjBank()["Controller"];

    controller.SetPosition({(horizontal / 10.f), (vertical / 9.0f)});
    controller.CalcScale(std::min(horizontal, vertical));

    directXUtility.PrepareWindowDependentResources(size, viewport);
}

void Game::OnDeviceLost()
{
    // Resets Assets
    directXUtility.ResetAssets(resourceManager.GetImgObjBank());
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}

#pragma endregion