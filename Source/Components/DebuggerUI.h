#pragma once

#include "pch.h"
#include "Component.h"
#include "Source/Game/GameObject.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Line.h"
#include "Source/Managers/InputManager.h"
#include "BoxCollider.h"
#include "queue"
#include "sstream"

class RigidBody;

class DebuggerUI : public Component
{
private:
	GameObjectManager *resourceManager = nullptr;
	InputManager *inputManager = InputManager::GetInstance();

	boolean bOn = true;
	RigidBody *rb = nullptr; 
	BoxCollider *bc = nullptr;

	std::string sParentObjName = "";
	std::string sObjectFocusName = "";

	// Frame by frame debugger.
	int frameCaptureRate = 30;
	int frameCount = 1;

	std::queue<std::string> qFrameDesc;

	void updateFrameByFrameDebugger(std::unordered_map<std::string, Text>& refTextBank, std::string displacement, std::string acceleration);

	float roundToDecimal(float input, float upTo = 3);

	std::string removeTrailingZeroes(float value);

public: 
	DebuggerUI();

	DebuggerUI(std::string inp_parentObjName, std::string inp_objectFocusName);

	void Awake() override;

	void Update(float deltaTime) override;
};