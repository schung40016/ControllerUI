#include "pch.h"
#include "InputManager.h"

InputManager* InputManager::instance = NULL;

// Define the static member variables.
InputManager::InputManager()
{
	m_gamePad = std::make_unique<DirectX::GamePad>();
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_mouse = std::make_unique<DirectX::Mouse>();
}

void InputManager::UpdateButtons()
{
	auto pad = m_gamePad->GetState(0);

	m_prevKB = m_currKB;
	m_currKB = m_keyboard->GetState();

	bool f1Down = m_currKB.IsKeyDown(DirectX::Keyboard::Keys::F1);

	if (f1Down) 
	{
		int hi = 1;
	}

	isConnected = pad.IsConnected();

	if (isConnected)
	{
		m_buttons.Update(pad);

		a = pad.IsAPressed();
		b = pad.IsBPressed();
		x = pad.IsXPressed();
		y = pad.IsYPressed();
		start = pad.IsStartPressed();
		view = pad.IsViewPressed();
		dPadUp = pad.IsDPadUpPressed();
		dPadDown = pad.IsDPadDownPressed();
		dPadLeft = pad.IsDPadLeftPressed();
		dPadRight = pad.IsDPadRightPressed();
		leftShoulder = pad.IsLeftShoulderPressed();
		rightShoulder = pad.IsRightShoulderPressed();
		leftTrigger = pad.IsLeftTriggerPressed();
		rightTrigger = pad.IsRightTriggerPressed();
		leftStick = pad.IsLeftStickPressed();
		rightStick = pad.IsRightStickPressed();
		leftStickPos = { pad.thumbSticks.leftX, pad.thumbSticks.leftY };
		rightStickPos = { pad.thumbSticks.rightX, pad.thumbSticks.rightY };
		isConnected = pad.IsConnected();
	}
	else
	{
		m_buttons.Reset();
	}
}

void InputManager::ResetButtons()
{
	m_buttons.Reset();
}

void InputManager::ResumeGamepad()
{
	m_gamePad->Resume();
}

/// <inheritdoc/>
DirectX::Keyboard* InputManager::GetKeyboard()
{
	return m_keyboard.get();
}

/// <inheritdoc/>
DirectX::Mouse::State InputManager::GetMouse()
{
	return m_mouse.get()->GetState();
}

void InputManager::SuspendGamepad()
{
	m_gamePad->Suspend();
}

/// <inheritdoc/>
InputManager* InputManager::GetInstance()
{
	if (instance == NULL)
	{
		// We can access private members 
		// within the class.
		instance = new InputManager();

		// returning the instance pointer
		return instance;
	}
	else
	{
		// if instancePtr != NULL that means 
		// the class already have an instance. 
		// So, we are returning that instance 
		// and not creating new one.
		return instance;
	}
}

InputManager::~InputManager()
{
	delete instance;
}

