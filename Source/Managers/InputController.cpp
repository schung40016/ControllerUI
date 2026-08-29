#include "pch.h"
#include "InputController.h"

std::unordered_map<std::string, ActionBinding> InputController::mActions;
std::unordered_map<std::string, std::function<DirectX::SimpleMath::Vector2()>> InputController::mAxes;

void InputController::Initialize()
{
	LoadDefaultLayout();
}

bool InputController::GetButton(const std::string& actionName)
{
	auto it = mActions.find(actionName);
	return (it != mActions.end()) && it->second.isPressed();
}

bool InputController::GetButtonDown(const std::string& actionName)
{
	auto it = mActions.find(actionName);
	return (it != mActions.end()) && it->second.wasPressed();
}

bool InputController::GetButtonReleased(const std::string& actionName)
{
	auto it = mActions.find(actionName);
	return (it != mActions.end()) && it->second.wasReleased();
}

DirectX::SimpleMath::Vector2 InputController::GetAxis(const std::string& axisName)
{
	auto it = mAxes.find(axisName);
	if (it != mAxes.end())
	{
		return it->second();
	}
	return { 0.f, 0.f };
}

void InputController::RegisterAction(const std::string& actionName, ActionBinding binding)
{
	mActions[actionName] = binding;
}

void InputController::RegisterAxis(
	const std::string& axisName, 
	std::function<DirectX::SimpleMath::Vector2()> axisFunc)
{
	mAxes[axisName] = axisFunc;
}

void InputController::LoadDefaultLayout()
{
	auto* im = InputManager::GetInstance();

	RegisterAction("Jump", 
	{
		[im]() { return im->a; },
		[im]() { return im->m_buttons.a == DirectX::GamePad::ButtonStateTracker::PRESSED; },
		[im]() { return im->m_buttons.a == DirectX::GamePad::ButtonStateTracker::RELEASED; }
	});

	RegisterAction("Select", 
	{
		[im]() { return im->rightTrigger; },
		[im]() { return im->m_buttons.rightTrigger == DirectX::GamePad::ButtonStateTracker::PRESSED; },
		[im]() { return im->m_buttons.rightTrigger == DirectX::GamePad::ButtonStateTracker::RELEASED; }
	});

	RegisterAction("Edit",
	{
		[im]() { return im->m_currKB.IsKeyDown(DirectX::Keyboard::Keys::F1); },
		[im]() { return im->m_currKB.IsKeyDown(DirectX::Keyboard::Keys::F1) && !im->m_prevKB.IsKeyDown(DirectX::Keyboard::Keys::F1); },
		[im]() { return !im->m_currKB.IsKeyDown(DirectX::Keyboard::Keys::F1) && im->m_prevKB.IsKeyDown(DirectX::Keyboard::Keys::F1); }
	});

	RegisterAxis("Move", [im]() { return im->leftStickPos; });
}

void InputController::LoadLayout(const std::string& layoutName)
{
	mActions.clear();
	mAxes.clear();

	LoadDefaultLayout();
}