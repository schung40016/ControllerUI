//
// Game.h
//

#pragma once

#include "pch.h"
#include "DeviceResources.h"
#include "StepTimer.h"
#include "Source/Game/GameObject.h"
#include "Source/Managers/DirectXUtility.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Managers/InputManager.h"
#include "Source/Game/Controller.h"
#include "Source/Game/World.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;


// A basic game implementation that creates a D3D12 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:
    Game() noexcept(false);
    ~Game();

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Custom functions:
    // void SetTriggerPosition(DirectX::GamePad::State pad);

    // Device resources.
    std::unique_ptr<DX::DeviceResources>        m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                               m_timer;

    // Instanstiate custom object.
    DirectXUtility directXUtility;

    // -- GAMEPAD Attributes --
    InputManager* inputManager = InputManager::GetInstance();
    // ------------------------

    // Keeps track of our resources.
    GameObjectManager* resourceManager = GameObjectManager::GetInstance();
    
    // Initialize all game objects here. 
    World gameWorld;
};
