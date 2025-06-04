#include "pch.h"
#include "PlayerController.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/AnimationController.h"
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
	playerSprite = &GameObjectManager::GetInstance()->GetImgObj(parentObj->GetName() + "_Image");
	rb = parentObj->GetComponent<RigidBody>();
	ac = parentObj->GetComponent<AnimationController>();
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

	// Jump Movement.
	bool jumped = inputManager->a;

	rb->AddForce({ fSpeed * input.x, 0 });
	if (abs(rb->GetVelocity().x) > 1.f)
	{
		ac->AddAnimation("Run");
	}

	if (jumped && rb->isGrounded())
	{
		Jump();
	}

	if (!rb->isGrounded())
	{
		ac->AddAnimation("Jump");
	}

	ac->AddAnimation("Idle");
}

void PlayerController::Jump()
{
	rb->AddForce({ 0, fJumpHeight });
}