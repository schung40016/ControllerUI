#pragma once

#include "pch.h"
#include "DebuggerUI.h"
#include "Source/Managers/GameObjectManager.h"

DebuggerUI::DebuggerUI()
{
    resourceManager = GameObjectManager::GetInstance();
}

DebuggerUI::DebuggerUI(std::string inp_parentObjName, std::string inp_objectFocusName)
{
    sParentObjName = inp_parentObjName;
    sObjectFocusName = inp_objectFocusName;
    resourceManager = GameObjectManager::GetInstance();
}

void DebuggerUI::Awake()
{
    GameObject& refPlayerObj = resourceManager->GetGameObj(sObjectFocusName);
    rb = refPlayerObj.GetComponent<RigidBody>();
}

void DebuggerUI::Update(float deltaTime)
{
    std::unordered_map<std::string, Text> &refTextBank = resourceManager->GetTxtObjBank();
    Line& lnVelocity = resourceManager->GetLnObj(sParentObjName + "_VelocityLine");

    GameObject &refPlayerObj = resourceManager->GetGameObj(sObjectFocusName);
    const DirectX::SimpleMath::Vector2 playerPos = refPlayerObj.GetPosition();
    Text &velocityNum = refTextBank[sParentObjName + "_velocity_num"];
    Text &accelerationNum = refTextBank[sParentObjName + "_acceleration_num"];
    Text &positionNum = refTextBank[sParentObjName + "_position_num"];
    DirectX::SimpleMath::Vector2 tempVelocity = rb->GetVelocity();
    DirectX::SimpleMath::Vector2 tempAcceleration = rb->GetAcceleration();

    refTextBank[sParentObjName + "_velocity"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_acceleration"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_position"].SetDisplay(bOn);

    velocityNum.SetDisplay(bOn);
    accelerationNum.SetDisplay(bOn);
    positionNum.SetDisplay(bOn);

    std::string sTempVelocity = "{" + std::to_string(tempVelocity.x) + ", " + std::to_string(tempVelocity.y) + "}";
    std::string sTempAccelration = "{" + std::to_string(tempAcceleration.x) + ", " + std::to_string(tempAcceleration.y) + "}";
    std::string sTempPosition = "{" + std::to_string(playerPos.x) + ", " + std::to_string(playerPos.y) + "}";
    velocityNum.SetText(sTempVelocity);
    accelerationNum.SetText(sTempAccelration);
    positionNum.SetText(sTempPosition);

    lnVelocity.SetPoint2(tempVelocity.x * 10.f, tempVelocity.y * 10.f);
}

/*
* 10/5/2024
- Improve jump (done)
- Add more props to the map.
- Update velocity and acceleration to be lines in the debug mode. (done)
- Make camera component. (done)
- Update debug component
*/