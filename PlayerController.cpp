#include "pch.h"
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
	DirectX::SimpleMath::Vector2 input = inputManager->leftStickPos;

	rb->AddForce({ fSpeed * input.x, 0 });

	// Suggest: movement component, figures out what forces should be applied on any object. More encapslation. 
	// dev UI: implement velocity line on player.
}

void PlayerController::Jump()
{
}
