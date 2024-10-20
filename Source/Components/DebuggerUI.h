#pragma once

#include "pch.h"
#include "Component.h"
#include "Source/Game/GameObject.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Line.h"
#include "Source/Managers/InputManager.h"

class RigidBody;

class DebuggerUI : public Component
{
private:
	GameObjectManager *resourceManager = nullptr;
	InputManager *inputManager = InputManager::GetInstance();

	boolean bOn = true;
	RigidBody *rb = nullptr; 

	std::string sParentObjName = "";
	std::string sObjectFocusName = "";

public: 
	DebuggerUI();

	DebuggerUI(std::string inp_parentObjName, std::string inp_objectFocusName);

	void Awake() override;

	void Update(float deltaTime) override;
};