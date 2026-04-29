#pragma once
#include "pch.h"
#include "functional"
#include "string"
#include "InputManager.h"

struct ActionBinding 
{
	std::function<bool()> isPressed;
	std::function<bool()> wasPressed;
	std::function<bool()> wasReleased;
};

class InputController
{
private:
	static std::unordered_map<std::string, ActionBinding> mActions;
	static std::unordered_map<std::string, std::function<DirectX::SimpleMath::Vector2()>> mAxes;

	static void LoadDefaultLayout();

public:
	static void Initialize();
	static void LoadLayout(const std::string& layoutName);

	// Responsible for checking input status.
	static bool GetButton(const std::string& actionName);
	static bool GetButtonDown(const std::string& actionName);
	static bool GetButtonReleased(const std::string& actionName);
	static DirectX::SimpleMath::Vector2 GetAxis(const std::string& axisName);

	static void RegisterAction(const std::string& actionName, ActionBinding binding);
	static void RegisterAxis(const std::string& axisName, std::function<DirectX::SimpleMath::Vector2()> axisFunc);

	// Remove since this is singleton design.
	InputController() = delete;
	~InputController() = delete;
	InputController(const InputController&) = delete;
	InputController& operator=(const InputController&) = delete;
};