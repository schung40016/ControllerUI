#pragma once

#include "pch.h"
#include <GameObject.h>
#include "Text.h"
#include "Triangle.h"
#include "Line.h"
#include "Image.h"
#include "InputManager.h"

class Controller : public Component
{
private:
    InputManager* inputManager = InputManager::GetInstance();

    boolean bConnected = false;

    std::shared_ptr<GameObject> parentObj = nullptr; // Need it for applying movement.

    Text controllerTitle;
    Text connectionTitle;
    Text connectionStatus;

    // Create a higher tier object to act as the parent for all these objects.
    Image gamePad;   // xbox controller
    Image imgLeftTrigger;    // left trigger.
    Image imgRightTrigger;  // right trigger.

    Triangle a; // a
    Triangle b; // b
    Triangle x; // x
    Triangle y;    // y

    Triangle start;  // start
    Triangle view;  // view
    Triangle dPadUp; // dpadup
    Triangle dPadDown;   // dpaddown
    Triangle dPadLeft;  // dpadright
    Triangle dPadRight;  // dpadlefft
    Triangle leftShoulder; // left shoulder
    Triangle rightShoulder;    // right shoulder
    Triangle leftTrigger;  // left trigger
    Triangle righTrigger;    // right trigger
    Triangle leftStick;    // left stick
    Triangle rightStick;  // right stick

    Line leftStickDir; // left stick direction
    Line rightStickDir;   // right stick direction

public:
	Controller(GameObject& inp_parentObj);

    void Update(float deltaTime) override;
};