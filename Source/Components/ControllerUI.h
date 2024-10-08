#pragma once

#include "pch.h"
#include "Source/Components/Component.h"
#include "Source/Managers/InputManager.h"
#include "Source/UI_Objects/Shapes/Triangle.h"
#include "Source/UI_Objects/Line.h"

class ControllerUI : public Component
{
private:
	GameObjectManager* resourceManager = nullptr;
	InputManager* inputManager = InputManager::GetInstance();
	float fStickLineMultiplier = 10.f;
	std::string parentObjName = "";

public:
	ControllerUI();

	ControllerUI(std::string inp_parentObjName);

	void Update(float deltaTime) override;
};