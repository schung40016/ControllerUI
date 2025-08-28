#include "pch.h"
#include "Camera.h"
#include "Source/Game/GameObject.h"
#include "DeviceResources.h"


Camera::Camera()
{
}

Camera::Camera(GameObject& inp_parentObj, bool inp_focus) :
    fPitch(0),
    fYaw(0),
    colRoomColor(DirectX::Colors::White), 
    bFocus(inp_focus)
{
   parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
   DirectX::SimpleMath::Vector2 parentPos = parentObj->GetRenderPosition();
   FetchConvertParentPosition();
}

void Camera::Awake()
{

}

void Camera::Update(float deltaTime) 
{
    FetchConvertParentPosition();

    float y = sinf(fPitch);
    float r = cosf(fPitch);
    float z = r * cosf(fYaw);
    float x = r * sinf(fYaw);

    DirectX::XMVECTOR lookAt = v3CameraPos + DirectX::SimpleMath::Vector3(x, y, z);

    mView = XMMatrixLookAtRH(v3CameraPos, lookAt, DirectX::SimpleMath::Vector3::Up);
}

void Camera::FetchConvertParentPosition() 
{
    DirectX::SimpleMath::Vector2 parentPos = parentObj->GetRenderPosition();
    v3CameraPos = { parentPos.x, parentPos.y, 0 };
}

void Camera::ResetResources() 
{
    ptrRoom.reset();
    ptrRoomTex.Reset();
    ptrStates.reset();
    ptrRoomEffect.reset();
}

DirectX::SimpleMath::Matrix Camera::PrepareProjection(RECT size)
{
    return DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        DirectX::XMConvertToRadians(70.f),
        float(size.right) / float(size.bottom), 0.01f, 100.f);
}

void Camera::PrepareResources(ID3D12Device* device)
{
    ptrStates = std::make_shared<DirectX::DX12::CommonStates>(device);

    ptrRoom = DirectX::DX12::GeometricPrimitive::CreateBox(
        DirectX::XMFLOAT3(ROOM_BOUNDS[0], ROOM_BOUNDS[1], ROOM_BOUNDS[2]),
        false, true);
}

void Camera::Render(ID3D12GraphicsCommandList* commandList)
{
    // Check if mProj is initialized (all zeros means not set)
    if (mProj == DirectX::SimpleMath::Matrix::Identity ||
        (mProj.m[0][0] == 0 && mProj.m[1][1] == 0)) {
        OutputDebugStringA("mProj matrix not initialized!\n");
        // Set a default projection for testing
        mProj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
            DirectX::XMConvertToRadians(70.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    }

    ptrRoomEffect->SetMatrices(DirectX::SimpleMath::Matrix::Identity, mView, mProj);
    ptrRoomEffect->SetDiffuseColor(colRoomColor);
    ptrRoomEffect->Apply(commandList);
    ptrRoom->Draw(commandList);
}

// Getters & Setters.
std::shared_ptr<GameObject> Camera::GetParent() const
{
    return parentObj;
}

std::shared_ptr<DirectX::CommonStates>& Camera::GetPtrStates()
{
    return ptrStates;
}

Microsoft::WRL::ComPtr<ID3D12Resource>& Camera::GetPtrRoomTex()
{
    return ptrRoomTex;
}

std::shared_ptr<DirectX::BasicEffect>& Camera::GetPtrRoomEffect()
{
    return ptrRoomEffect;
}

DirectX::SimpleMath::Matrix Camera::GetView()
{
    return mView;
}

DirectX::SimpleMath::Matrix Camera::GetProj()
{
    return mProj;
}

bool Camera::GetFocus()
{
    return bFocus;
}

void Camera::SetPtrRoomEffect(const std::shared_ptr<DirectX::DX12::BasicEffect>& inp_basicEffectPtr)
{
    ptrRoomEffect = inp_basicEffectPtr;
}