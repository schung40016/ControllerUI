#pragma once

#include "pch.h"
#include "Component.h"

class Camera : public Component 
{
private:
	std::shared_ptr<class GameObject> parentObj = nullptr;

    DirectX::XMVECTORF32 START_POSITION = { 0.f, -1.5f, 0.f, 0.f };
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

    float fPitch = 1.0f;
    float fYaw = 1.0f;
    bool bFocus = false;    // Determines if the screen should focus on this particular camera.

public:
    Camera();

    Camera(class GameObject& inp_parentObj, bool inp_focus);

    void Awake() override;

    void Update(float deltaTime) override;

    void ResetResources();

    void FetchConvertParentPosition();

    DirectX::SimpleMath::Matrix PrepareProjection(RECT size);

    void PrepareResources(ID3D12Device* device);

    void Render(ID3D12GraphicsCommandList* commandList);

    // Getters & Setters.
    std::shared_ptr<DirectX::CommonStates>& GetPtrStates();

    Microsoft::WRL::ComPtr<ID3D12Resource>& GetPtrRoomTex();

    std::shared_ptr<DirectX::BasicEffect>& GetPtrRoomEffect();

    DirectX::SimpleMath::Matrix GetView();

    DirectX::SimpleMath::Matrix GetProj();

    bool GetFocus();

    void SetPtrRoomEffect(const std::shared_ptr<DirectX::DX12::BasicEffect>& inp_basicEffectPtr);
    
};