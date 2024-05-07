#pragma once
#include "Source/pch.h"

/*
	Since only need 1 instance of the game controller feedback
	and we want to export the instance to all files within the 
	project w/o worrying about constant passing and initialization,
	use Singleton design.
*/ 
class InputManager {
private:
	static InputManager* instance;
	std::unique_ptr<DirectX::GamePad> m_gamePad;
	DirectX::GamePad::ButtonStateTracker m_buttons;

	// Constructor.
	InputManager();

public:
	boolean a = false;
	boolean b = false;
	boolean x = false;
	boolean y = false;
	boolean start = false;
	boolean view = false;

	boolean dPadUp = false;
	boolean dPadDown = false;
	boolean dPadLeft = false;
	boolean dPadRight = false;

	boolean leftShoulder = false;
	boolean rightShoulder = false;
	boolean leftTrigger = false;
	boolean rightTrigger = false;

	boolean leftStick = false;
	boolean rightStick = false;

	boolean isConnected = false; 

	DirectX::SimpleMath::Vector2 leftStickPos;
	DirectX::SimpleMath::Vector2 rightStickPos;

	// Don't implement.
	InputManager(const InputManager& obj) = delete;

	void UpdateButtons();
	void ResetButtons();
	void SuspendGamepad();
	void ResumeGamepad();
	static InputManager* GetInstance();
};