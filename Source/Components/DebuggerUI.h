#pragma once

#include "pch.h"
#include "Component.h"
#include "queue"

class RigidBody;

class DebuggerUI : public Component
{
private:
	class GameObjectManager *resourceManager = nullptr;
	class InputManager* inputManager = nullptr;

	boolean bOn = true;
	class RigidBody *rb = nullptr; 
	class BoxCollider *bc = nullptr;

	std::string sParentObjName = "";
	std::string sObjectFocusName = "";

	// Frame by frame debugger.
	int frameCaptureRate = 30;
	int frameCount = 1;

	std::queue<std::string> qFrameDesc;

	void updateFrameByFrameDebugger(std::unordered_map<std::string, class Text>& refTextBank, std::string displacement, std::string acceleration);

	float roundToDecimal(float input, float upTo = 3);

	std::string removeTrailingZeroes(float value);

public: 
	DebuggerUI();

	DebuggerUI(std::string inp_parentObjName, std::string inp_objectFocusName);

	void Awake() override;

	void Update(float deltaTime) override;
};