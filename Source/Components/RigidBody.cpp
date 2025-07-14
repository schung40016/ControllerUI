#include "pch.h";
#include "RigidBody.h";
#include "Source/Game/GameObject.h"
#include "Source/Tools/Raycast.h"
#include "BoxCollider.h"
#include "vector"

RigidBody::RigidBody()
{}

RigidBody::RigidBody(GameObject& inp_parentObj, bool inp_isKinematic, float inp_fMass, 
	float inp_fAcceleration) : bIsKinematic(bIsKinematic), fMass(inp_fMass), fAcceleration(inp_fAcceleration)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
}

void RigidBody::Update(float deltaTime)		// Performs all calculations.
{
	CheckIfGrounded();
	ApplyGravity(deltaTime);
	StopVelocity();
	ApplyForce(deltaTime);
}

void RigidBody::ApplyGravity(float deltaTime)			// unsigned int, change deltaTime. (os get time call).
{
	// Use add force to apply gravity, not a standalone.
	if (bIsKinematic && !grounded)
	{
		DirectX::SimpleMath::Vector2 calcVelocity = gravityAcceleration * fMass;
		AddForce(calcVelocity);
	}
}

void RigidBody::StopVelocity()
{
	if ((grounded && actVelocity.y < 0))
	{
		actVelocity.y = 0;
		velocity.y = 0;
	}

	if ((rightGrounded && actVelocity.x > 0) || (leftGrounded && actVelocity.x < 0))
	{
		actVelocity.x = 0;
		velocity.x = 0;
	}

	if (topGrounded && actVelocity.y > 0)
	{
		actVelocity.y = 0;
		velocity.y = 0;
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
	// Acceleration = force / mass
	DirectX::SimpleMath::Vector2 acceleration = accumulatedForce / fMass;
	// Update velocity based on acceleration.
	velocity += acceleration * deltaTime;
	// Reset accumulatedForce for the next time it is called.
	accumulatedForce = { 0, 0 };
	// Update parent object's position.
	actVelocity.x = Interpolate(velocity.x, actVelocity.x, deltaTime * fSmoothness);
	actVelocity.y = Interpolate(velocity.y, actVelocity.y, deltaTime * fSmoothness);

	// Prevent parent object from moving to final location if collision is detected.
	BoxCollider* boxCollider = parentObj->GetComponent<BoxCollider>();
	const DirectX::SimpleMath::Vector2 parentPos = { parentObj->GetPosition().x, parentObj->GetPosition().y };

	parentObj->MovePosition(actVelocity);

	if (boxCollider)
	{
		bool result = boxCollider->CollidesWithLayer(1);

		if (result)
		{
			parentObj->SetPosition(parentPos + boxCollider->GetTotalDisplacement());
			boxCollider->ResetTotalDisplacement();
		}
	}
}

// We feed it velocity, why name the inputs position???
float RigidBody::Interpolate(float goalPosition, float currPosition, float dt)
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
	return goalPosition;	// Calculate the decay on each force.
}

void RigidBody::CheckIfGrounded()
{
	float parentWidthHalved = parentObj->GetSize().x / 2.f;
	float parentLengthHalved = parentObj->GetSize().y / 2.f;
	float rayCastVerticalLength = parentLengthHalved + fGroundCheckerOffset;
	float rayCastHorizontalLength = parentWidthHalved + fGroundCheckerOffset;

	DirectX::SimpleMath::Vector2 parentPos = parentObj->GetPosition();
	DirectX::SimpleMath::Vector2 rightEdge = { parentPos.x + parentWidthHalved, parentPos.y};
	DirectX::SimpleMath::Vector2 leftEdge = { parentPos.x - parentWidthHalved, parentPos.y };
	bool groundedRightCheck = Raycast::CastRaycast(rightEdge, { 0, -1 }, EnumData::ColliderLayers::Ground, rayCastVerticalLength);
	bool groundedLeftCheck = Raycast::CastRaycast(leftEdge, { 0, -1 }, EnumData::ColliderLayers::Ground, rayCastVerticalLength);

	leftGrounded = Raycast::CastRaycast(parentPos, { -1, 0 }, EnumData::ColliderLayers::Ground, rayCastHorizontalLength);
	rightGrounded = Raycast::CastRaycast(parentPos, { 1, 0 }, EnumData::ColliderLayers::Ground, rayCastHorizontalLength);
	bool topGroundedLeftCheck = Raycast::CastRaycast(rightEdge, { 0, 1 }, EnumData::ColliderLayers::Ground, rayCastVerticalLength);
	bool topGroundedRightCheck = Raycast::CastRaycast(rightEdge, { 0, 1 }, EnumData::ColliderLayers::Ground, rayCastVerticalLength);

	topGrounded = topGroundedLeftCheck || topGroundedRightCheck;
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