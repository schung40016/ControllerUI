#include "pch.h";
#include "RigidBody.h";
#include "Source/Game/GameObject.h"
#include "Source/Tools/Raycast.h"

RigidBody::RigidBody()
{}

void RigidBody::Update(float deltaTime)		// Performs all calculations.
{
	CheckIfGrounded();
	ApplyGravity(deltaTime);
	ApplyForce(deltaTime);
}

RigidBody::RigidBody(GameObject& inp_parentObj, bool inp_isKinematic, float inp_fMass, 
	float inp_fAcceleration) : bIsKinematic(bIsKinematic), fMass(inp_fMass), fAcceleration(inp_fAcceleration)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
}

void RigidBody::ApplyGravity(float deltaTime)
{
	// Apply gravity here.
	if (bIsKinematic && !grounded)
	{
		DirectX::SimpleMath::Vector2 calcPos = parentObj->GetPosition() + velocity * deltaTime;

		parentObj->SetPosition(calcPos);
		velocity = velocity + gravityVelocity * deltaTime * fMass;
	}

	StopVelocity();
}

void RigidBody::StopVelocity()
{
	if ((grounded && actVelocity.y > 0) || ((topGroundedLeft || topGroundedRight)&& actVelocity.y < 0))
	{
		actVelocity.y = 0;
	}

	if ((rightGrounded && actVelocity.x > 0) || (leftGrounded && actVelocity.x < 0))
	{
		actVelocity.x = 0;
	}
}

int RigidBody::GetLayerMask() const
{
	return parentObj->GetLayerMask();
}

float RigidBody::GetMass()
{
	return fMass;
}

// Need to add a player controller
void RigidBody::AddForce(DirectX::SimpleMath::Vector2 inp_force)
{
	accumulatedForce += inp_force;
}

// Redo
void RigidBody::ApplyForce(float deltaTime)				// Fix force, it's backwards in regards to the y axis.
{
	// Apply resistance to the velocity overtime.
	velocity *= (1.0f - fDamping * deltaTime);
	// Update acceleration.
	totalGoalVelocity = (velocity - actVelocity) / deltaTime;

	// Apply added force.
	velocity += (accumulatedForce / fMass) * deltaTime;			// why mass? take out.
	// Reset accumulatedForce for the next time it is called.
	accumulatedForce = { 0, 0 };
	// Update parent object's position.
	actVelocity.x = Interpolate(velocity.x, actVelocity.x, deltaTime * smoothness);
	actVelocity.y = Interpolate(velocity.y, actVelocity.y, deltaTime * smoothness);

	parentObj->MovePosition(actVelocity);
}

// We feed it velocity, why name the inputs position???
float RigidBody::Interpolate(float goalPosition, float currPosition, float dt)
{
	float pos_diff = goalPosition - currPosition;

	if (pos_diff > dt)
	{
		velocity.y = 0.f;
		return currPosition + dt;
	}
	if (pos_diff < -dt)
	{
		return currPosition - dt;
	}
	return goalPosition;	// Calculate the decay on each force.
}

void RigidBody::CheckIfGrounded()
{
	float parentWidthHalved = parentObj->GetSize().x / 2.f;
	float parentLengthHalved = parentObj->GetSize().y / 2.f;
	float rayCastVerticalLength = parentLengthHalved + 2.f;
	float rayCastHorizontalLength = parentWidthHalved + 2.f;

	DirectX::SimpleMath::Vector2 parentPos = parentObj->GetPosition();
	DirectX::SimpleMath::Vector2 rightEdge = { parentPos.x + parentWidthHalved, parentPos.y};
	DirectX::SimpleMath::Vector2 leftEdge = { parentPos.x - parentWidthHalved, parentPos.y };
	bool groundedRightCheck = Raycast::CastRaycast(rightEdge, { 0, -1 }, EnumData::ColliderLayers::Ground, rayCastVerticalLength);
	bool groundedLeftCheck = Raycast::CastRaycast(leftEdge, { 0, -1 }, EnumData::ColliderLayers::Ground, rayCastVerticalLength);

	leftGrounded = Raycast::CastRaycast(parentPos, { 1, 0 }, EnumData::ColliderLayers::Ground, rayCastHorizontalLength);
	rightGrounded = Raycast::CastRaycast(parentPos, { -1, 0 }, EnumData::ColliderLayers::Ground, rayCastHorizontalLength);
	topGroundedLeft = Raycast::CastRaycast(rightEdge, { 0, 1 }, EnumData::ColliderLayers::Ground, rayCastVerticalLength);
	topGroundedRight = Raycast::CastRaycast(rightEdge, { 0, 1 }, EnumData::ColliderLayers::Ground, rayCastVerticalLength);

	grounded = groundedRightCheck || groundedLeftCheck;
}

boolean RigidBody::isGrounded()
{
	return grounded;
}

DirectX::SimpleMath::Vector2 RigidBody::GetVelocity() const
{
	return velocity;
}

DirectX::SimpleMath::Vector2 RigidBody::GetAcceleration() const
{
	return totalGoalVelocity;
}