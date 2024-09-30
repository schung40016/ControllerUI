#pragma once

#include "pch.h"
#include "Source/Managers/GameObjectManager.h"

class Debugger
{
private:
    GameObjectManager* resourceManager = nullptr;
    std::string sDebuggerName = "";
    std::string sObjectFocusName = "";
    float fSizeMultiplier = 975.f;

    Text tVelocity;
    Text tAcceleration;
    Text tPosition;
    Text tVelocityNum;
    Text tAccelerationNum;
    Text tPositionNum;

public:
    Debugger();

    Debugger(float inp_size, std::string inp_controllerName, std::string inp_objectFocusName, DirectX::SimpleMath::Vector2 inp_position);
};