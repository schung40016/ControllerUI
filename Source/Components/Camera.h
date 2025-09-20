#pragma once

#include "pch.h"
#include "Component.h"

class Camera : public Component 
{
private:
	std::shared_ptr<class GameObject> parentObj = nullptr;

    DirectX::XMVECTORF32 ROOM_BOUNDS = { 8.f, 6.f, 12.f, 0.f };
    float ROTATION_GAIN = 0.1f;

    DirectX::SimpleMath::Matrix mView;
    DirectX::SimpleMath::Matrix mProj;
    DirectX::SimpleMath::Vector3 v3CameraPos;

    std::shared_ptr<DirectX::GeometricPrimitive> ptrRoom;
    DirectX::SimpleMath::Color colRoomColor;
    Microsoft::WRL::ComPtr<ID3D12Resource> ptrRoomTex;
    std::shared_ptr<DirectX::CommonStates> ptrStates;
    std::shared_ptr<DirectX::BasicEffect> ptrRoomEffect;

    DirectX::SimpleMath::Matrix camView2D;
    DirectX::SimpleMath::Vector2 camOffset = { 0, 0 };
    DirectX::SimpleMath::Vector4 screenEdgePoints = { 0, 0, 0, 0 };     // Up, Right, Down, Left

    float fPitch = 1.0f;
    float fYaw = 1.0f;
    bool bFocus = false;    // Determines if the screen should focus on this particular camera.

public:
    Camera();

    Camera(class GameObject& inp_parentObj, bool inp_focus);

    void Awake() override;

    void Update(float deltaTime) override;

    void ResetResources();

    void PrepareProjection(DirectX::SimpleMath::Vector2 focusPosition, DirectX::SimpleMath::Vector2 viewPort);

    void PrepareResources(ID3D12Device* device);

    /// <summary>
    /// Renders all items within the camera view.
    /// </summary>
    /// <param name="commandList"></param>
    void Render(ID3D12GraphicsCommandList* commandList);

    /// <summary>
    /// Determines if an object is within a camera's render view.
    /// </summary>
    /// <param name="objectPosition"></param>
    /// <param name="objectDimensions"></param>
    /// <returns></returns>
    bool CanRender(DirectX::SimpleMath::Vector2 objectPosition, DirectX::SimpleMath::Vector2 objectDimensions);

    // Getters & Setters.
    std::shared_ptr<GameObject> GetParent() const;

    std::shared_ptr<DirectX::CommonStates>& GetPtrStates();

    Microsoft::WRL::ComPtr<ID3D12Resource>& GetPtrRoomTex();

    std::shared_ptr<DirectX::BasicEffect>& GetPtrRoomEffect();

    DirectX::SimpleMath::Matrix GetView();

    DirectX::SimpleMath::Matrix GetProjection();

    DirectX::SimpleMath::Vector2 GetOffset();

    /// <summary>
    /// Determines if camera is focused (current display).
    /// </summary>
    /// <returns></returns>
    bool GetFocus();

    void SetPtrRoomEffect(const std::shared_ptr<DirectX::DX12::BasicEffect>& inp_basicEffectPtr);

    /// <summary>
    /// Sets the distance of screen edges according to the camera's position.
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    void SetScreenSizeHalved(float width, float height);
};