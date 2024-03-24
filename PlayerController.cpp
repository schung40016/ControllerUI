#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(GameObject& inp_parentObj, BoxCollider& inp_collider)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
	rb = new RigidBody(inp_parentObj);
	collider = inp_collider;
}

void PlayerController::Awake()
{
}

void PlayerController::Update(float deltaTime)
{
	Movement(deltaTime);
}

void PlayerController::Movement(float dt)
{
	DirectX::SimpleMath::Vector2 input = inputManager->leftStickPos;

	goalVelocity.x = fSpeed * input.x;

	actVelocity.x = Interpoplate(goalVelocity.x, actVelocity.x, dt * 10);

	parentObj->MovePosition({actVelocity.x, 0});

	// Suggest: movement component, figures out what forces should be applied on any object. More encapslation. 
	// dev UI: implement velocity line on player.
}

void PlayerController::Jump()
{

}

float PlayerController::Interpoplate(float goalPosition, float currPosition, float dt)
{
	float pos_diff = goalPosition - currPosition;

	if (pos_diff > dt)
	{
		return currPosition + dt;
	}
	if (pos_diff < -dt)
	{
		return currPosition - dt;
	}
	return goalPosition;
}
