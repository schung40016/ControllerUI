#pragma once
#include "pch.h"

/*
	Since only need 1 instance of the game controller feedback
	and we want to export the instance to all files within the 
	project w/o worrying about constant passing and initialization,
	use Singleton design.

	This script checks what buttons on the Controller/PC were pressed.
*/ 
class InputManager {
private:
	static InputManager* instance;
	std::unique_ptr<DirectX::GamePad> m_gamePad;
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	// Constructor.
	InputManager();

public:
	DirectX::GamePad::ButtonStateTracker m_buttons;

	// Keyboard & Mouse
	boolean m1 = false;
	boolean m2 = false;
	DirectX::Keyboard::State m_prevKB{};
	DirectX::Keyboard::State m_currKB{};

	// Gamepad
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

	/// <summary>
	/// Binds the mouse to the game window so DirectX::Mouse can track cursor/button state.
	/// </summary>
	/// <param name="window"></param>
	void SetWindow(HWND window);

	/// <summary>
	/// Fetches keyboard for instant access to keyboard button checks.
	/// </summary>
	/// <returns></returns>
	DirectX::Keyboard* GetKeyboard();

	/// <summary>
	/// Fetches mouse state for instant access to mouse button checks.
	/// </summary>
	/// <returns></returns>
	DirectX::Mouse::State GetMouse();

	/// <summary>
	/// Returns an instance of the input manager.
	/// </summary>
	/// <returns></returns>
	static InputManager* GetInstance();

	~InputManager();
};