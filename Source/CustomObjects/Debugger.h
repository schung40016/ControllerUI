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
    Text tDisplacement;
    Text tVelocityNum;
    Text tAccelerationNum;
    Text tPositionNum;
    Text tDisplacementNum;

    Line lnVelocity;

    // Frame by frame debugger.
    Text tFrameDesc1;
    Text tFrameDesc2;
    Text tFrameDesc3;
    Text tFrameDesc4;
    Text tFrameDesc5;

public:
    Debugger();

    Debugger(float inp_size, std::string inp_controllerName, std::string inp_objectFocusName, DirectX::SimpleMath::Vector2 inp_position);
};