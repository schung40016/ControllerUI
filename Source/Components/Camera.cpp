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
}

void Camera::Awake()
{

}

void Camera::Update(float deltaTime) 
{
    float y = sinf(fPitch);
    float r = cosf(fPitch);
    float z = r * cosf(fYaw);
    float x = r * sinf(fYaw);

    DirectX::SimpleMath::Vector2 parentPos = parentObj->GetRenderPosition();
    v3CameraPos = { parentPos.x, parentPos.y, 0 };

    DirectX::XMVECTOR lookAt = v3CameraPos + DirectX::SimpleMath::Vector3(x, y, z);
    mView = XMMatrixLookAtRH(v3CameraPos, lookAt, DirectX::SimpleMath::Vector3::Up);
}

void Camera::ResetResources() 
{
    ptrRoom.reset();
    ptrRoomTex.Reset();
    ptrStates.reset();
    ptrRoomEffect.reset();
}

void Camera::PrepareProjection(DirectX::SimpleMath::Vector2 focusPosition, DirectX::SimpleMath::Vector2 viewPort)
{
    DirectX::SimpleMath::Vector2 halfViewport(viewPort.x * 0.5f, viewPort.y * 0.5f);

    // world → screen translation to keep player centered
    camOffset = halfViewport - DirectX::SimpleMath::Vector2(focusPosition.x, focusPosition.y);

    // keep camView2D for effects (shapes/lines)
    camView2D = DirectX::SimpleMath::Matrix::CreateTranslation(camOffset.x, camOffset.y, 0.0f);
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
    ptrRoomEffect->SetMatrices(DirectX::SimpleMath::Matrix::Identity, mView, mProj);
    ptrRoomEffect->SetDiffuseColor(colRoomColor);
    ptrRoomEffect->Apply(commandList);
    ptrRoom->Draw(commandList);
}

bool Camera::CanRender(DirectX::SimpleMath::Vector2 objectPosition, DirectX::SimpleMath::Vector2 objectDimensions)
{
    float halfWidth = objectDimensions.x / 2.0f;
    float halfLength = objectDimensions.y / 2.0f;

    // Calculate all the bounds of the shape.
    float topEdge = objectPosition.y + halfLength;
    float bottomEdge = objectPosition.y - halfLength;
    float leftEdge = objectPosition.x - halfWidth;
    float rightEdge = objectPosition.x + halfWidth;

    // Compare the bounds of the shape's to the camera's.
    if (topEdge < screenEdgePoints.z && bottomEdge > screenEdgePoints.x && leftEdge > screenEdgePoints.y && rightEdge < screenEdgePoints.w)
    {
        return false;
    }

    return true;
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

DirectX::SimpleMath::Matrix Camera::GetProjection()
{
    return camView2D;
}

DirectX::SimpleMath::Vector2 Camera::GetOffset()
{
    return camOffset;
}

/// <inheritdoc/>
bool Camera::GetFocus()
{
    return bFocus;
}

void Camera::SetPtrRoomEffect(const std::shared_ptr<DirectX::DX12::BasicEffect>& inp_basicEffectPtr)
{
    ptrRoomEffect = inp_basicEffectPtr;
}

void Camera::SetScreenSizeHalved(float width, float height)
{
    float halvedWidth = width / 2.0f;
    float halvedHeight = height / 2.0f;

    float x = v3CameraPos.x;
    float y = v3CameraPos.y;

    screenEdgePoints = { y + halvedHeight, x + halvedWidth, y - halvedHeight, x - halvedWidth};
}