#pragma once

#include "pch.h"
//#include "Movement.h"
//
//Movement::Movement() {}
//
//void Movement::Update(float deltaTime)		// Calls all relevant functions for calculations.
//{
//	actVelocity.x = Interpoplate(totalGoalVelocity.x, actVelocity.x, deltaTime * 10);
//	actVelocity.y = Interpoplate(totalGoalVelocity.y, actVelocity.y, deltaTime * 10);
//
//	parentObj->MovePosition({ actVelocity.x, actVelocity.y });
//}
//
//void Movement::ApplyForce(DirectX::SimpleMath::Vector2 goalVelocity)
//{
//	totalGoalVelocity += goalVelocity;
//}
//
//float Movement::Interpoplate(float goalPosition, float currPosition, float dt)
//{
//	float pos_diff = goalPosition - currPosition;
//
//	if (pos_diff > dt)
//	{
//		return currPosition + dt;
//	}
//	if (pos_diff < -dt)
//	{
//		return currPosition - dt;
//	}
//	return goalPosition;
//}