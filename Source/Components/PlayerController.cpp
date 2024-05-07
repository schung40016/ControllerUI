#include "Source/pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(GameObject& inp_parentObj, BoxCollider& inp_collider)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
	collider = inp_collider;
}

void PlayerController::Awake()
{
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
	rb->AddForce({ fSpeed * input.x, 0 });

	// Jump Movement.
	bool jumped = inputManager->a;
	
	if (jumped && rb->isGrounded())
	{
		rb->AddForce({ 0, -1.f * fJumpHeight });
	}
}

void PlayerController::Jump()
{
}
