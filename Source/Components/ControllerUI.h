#pragma once

#include "pch.h"
#include "Component.h"

class ControllerUI : public Component
{
private:
	class GameObjectManager* resourceManager = nullptr;
	class InputManager* inputManager = nullptr;
	float fStickLineMultiplier = 10.f;
	std::string parentObjName = "";

public:
	ControllerUI();

	ControllerUI(std::string inp_parentObjName);

	void Update(float deltaTime) override;
};