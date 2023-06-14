//
// Game.h
//

#pragma once

#include "pch.h"
#include "DeviceResources.h"
#include "StepTimer.h"
#include "ImageObjectHelper.h"
#include "Triangle.h"
#include "Image.h"
#include "Line.h"

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
    
    // For Drawing triangles.
    void DrawTriangle(float x, float y);

    // Draw Line.
    void DrawStickOrientation(float ox, float oy, float p1, float p2);

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Custom functions:
    void CheckInputs();
    void ResetAssets();
    void SetTriggerPosition(DirectX::GamePad::State pad);

    // Device resources.
    std::unique_ptr<DX::DeviceResources>        m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                               m_timer;

    // If using the DirectX Tool Kit for DX12, uncomment this line:
    // std::unique_ptr<DirectX::GraphicsMemory> m_graphicsMemory;
    std::unique_ptr<DirectX::GraphicsMemory> m_graphicsMemory;

    ImageObjectHelper imageHelper;

    // -- TEXT Attributes --
    const wchar_t* t_title = L"Controller UI";
    DirectX::SimpleMath::Vector2 m_titlePos;

    const wchar_t* t_connection = L"Controller Connection: ";
    DirectX::SimpleMath::Vector2 m_connectPos;
    DirectX::SimpleMath::Vector2 m_statusPos;

    DirectX::XMVECTOR textColor = Colors::Black;
    float textXRatio = 2.f;
    float textYRatio = 10.f;
    //----------------------

    // -- IMAGE Attributes --
    //

    // Prepares bitfont for sprite texts.
    std::unique_ptr<DirectX::DescriptorHeap> m_resourceDescriptors;
    std::unique_ptr<DirectX::SpriteFont> m_font;
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

    // Prepare the drawing of png.
    Microsoft::WRL::ComPtr<ID3D12Resource> m_controllerTexture;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_leftTriggerTexture;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_rightTriggerTexture;

    // Controller Image Render 
    DirectX::SimpleMath::Vector2 m_controllerPos;
    DirectX::SimpleMath::Vector2 m_controllerOrigin;
    DirectX::SimpleMath::Vector2 m_leftTriggerPos;
    DirectX::SimpleMath::Vector2 m_leftTriggerOrigin;
    DirectX::SimpleMath::Vector2 m_rightTriggerPos;
    DirectX::SimpleMath::Vector2 m_rightTriggerOrigin;
    // ----------------------

    Image controller;
    Image leftTrigger;
    Image rightTrigger;

    enum Descriptors
    {
        MyFont,
        Controller,
        LeftTrigger,
        RightTrigger,
        Count
    };

    // -- GAMEPAD Attributes --
    std::unique_ptr<DirectX::GamePad> m_gamePad;
    DirectX::GamePad::ButtonStateTracker m_buttons;
    // ------------------------

    bool isConnected = false;

    Triangle indA;
    Triangle indB;
    Triangle indX;
    Triangle indY;
    Triangle indView;
    Triangle indStart;
    Triangle indDPadUp;
    Triangle indDPadDown;
    Triangle indDPadLeft;
    Triangle indDPadRight;
    Triangle indLeftShoulder;
    Triangle indRightShoulder;
    Triangle indLeftTrigger;
    Triangle indRightTrigger;
    Triangle indLeftStick;
    Triangle indRightStick;

    Line leftStick;
    Line rightStick;

    // -- SHAPE Attributes --
    using VertexType = DirectX::VertexPositionColor;

    std::unique_ptr<DirectX::BasicEffect> m_effect;
    std::unique_ptr<DirectX::BasicEffect> m_lineEffect;
    std::unique_ptr<DirectX::PrimitiveBatch<VertexType>> m_batch;
    // ----------------------
};
