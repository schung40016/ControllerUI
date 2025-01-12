#include "pch.h"
#include "PlayerController.h"
#include "Source/Components/RigidBody.h"
#include "Source/Game/GameObject.h"
#include "Source/Managers/InputManager.h"
#include "Source/UI_Objects/Image.h"
#include "Source/Managers/GameObjectManager.h"

PlayerController::PlayerController()
{}

PlayerController::PlayerController(GameObject& inp_parentObj, BoxCollider& inp_collider, float inp_speed, float inp_jumpHeight)
	: fSpeed(inp_speed), fJumpHeight(inp_jumpHeight)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
	collider = inp_collider;
}

void PlayerController::Awake()
{
	inputManager = InputManager::GetInstance();
	GameObjectManager* resourceManager = GameObjectManager::GetInstance();
	playerSprite = &resourceManager->GetImgObj(parentObj->GetName() + "_image");
	rb = parentObj->GetComponent<RigidBody>();
}

void PlayerController::Update(float deltaTime)
{
	Movement(deltaTime);
}

void PlayerController::Movement(float dt)
{
	// Horizontal Movement.
	DirectX::SimpleMath::Vector2 input = inputManager->leftStickPos;

	if (input.x > 0)
	{
		playerSprite->flipImage(false);
	}
	else if (input.x < 0)
	{
		playerSprite->flipImage(true);
	}

	rb->AddForce({ fSpeed * input.x, 0 });

	// Jump Movement.
	bool jumped = inputManager->a;
	
	if (jumped && rb->isGrounded())
	{
		rb->AddForce({ 0, -1.0f * fJumpHeight });			// Fix this.
	}
}

void PlayerController::Jump()
{
}
