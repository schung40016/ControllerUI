#pragma once

#include "pch.h"
#include "Source/Game/GameObject.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Shapes/Triangle.h"
#include "Source/UI_Objects/Line.h"
#include "Source/UI_Objects/Image.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Components/ControllerUI.h"

class Controller
{
private:
    GameObjectManager* resourceManager = nullptr;
    std::string sControllerName = "";
    float fSizeMultiplier = 975.f;

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

    float fStickLineMultiplier = 10.f;
    Line leftStickDir; // left stick direction
    Line rightStickDir;   // right stick direction

public:
    Controller();

	Controller(float inp_size, std::string inp_controllerName, DirectX::SimpleMath::Vector2 inp_position);
};