#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(GameObject& inp_parentObj)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
	rb = new RigidBody(inp_parentObj);
	std::vector<DirectX::SimpleMath::Vector2> playerCollisionBox = { { -25.f, 25.f }, {25.f, 25.f}, {25.f, -25.f}, {-25.f, -25.f} };
	collider = new Collider(inp_parentObj, playerCollisionBox);
}

void PlayerController::Awake()
{
}

void PlayerController::Update(float deltaTime)
{
	Movement();
}

void PlayerController::Movement()
{
	DirectX::SimpleMath::Vector2 input = inputManager->leftStickPos;
	parentObj->MovePosition({ fSpeed * input.x, 0});
}

void PlayerController::Jump()
{

}