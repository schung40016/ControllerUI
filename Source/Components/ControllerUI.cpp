#pragma once

#include "pch.h"
#include "ControllerUI.h"
#include "Source/Managers/GameObjectManager.h"

ControllerUI::ControllerUI()
{
    resourceManager = GameObjectManager::GetInstance();
}

ControllerUI::ControllerUI(std::string inp_parentObjName)
{
    parentObjName = inp_parentObjName;
    resourceManager = GameObjectManager::GetInstance();
}

void ControllerUI::Update(float deltaTime) 
{
    // Update resource data manager triangles not here.
    //resourceManager = GameObjectManager::GetInstance();

    resourceManager->GetTxtObj("connectionStatus").SetText(inputManager->isConnected ? "On" : "Off");
    std::unordered_map<std::string, Triangle>& refTriangleBank = resourceManager->GetTriObjBank();
    std::unordered_map<std::string, Line>& refLineBank = resourceManager->GetLnObjBank();

    refTriangleBank[parentObjName+"_a"].SetDisplay(inputManager->a);
    refTriangleBank[parentObjName + "_b"].SetDisplay(inputManager->b);
    refTriangleBank[parentObjName + "_x"].SetDisplay(inputManager->x);
    refTriangleBank[parentObjName + "_y"].SetDisplay(inputManager->y);
    refTriangleBank[parentObjName + "_start"].SetDisplay(inputManager->start);
    refTriangleBank[parentObjName + "_view"].SetDisplay(inputManager->view);

    refTriangleBank[parentObjName + "_dPadUp"].SetDisplay(inputManager->dPadUp);
    refTriangleBank[parentObjName + "_dPadDown"].SetDisplay(inputManager->dPadDown);
    refTriangleBank[parentObjName + "_dPadLeft"].SetDisplay(inputManager->dPadLeft);
    refTriangleBank[parentObjName + "_dPadRight"].SetDisplay(inputManager->dPadRight);

    refTriangleBank[parentObjName + "_leftShoulder"].SetDisplay(inputManager->leftShoulder);
    refTriangleBank[parentObjName + "_rightShoulder"].SetDisplay(inputManager->rightShoulder);
    refTriangleBank[parentObjName + "_leftTrigger"].SetDisplay(inputManager->leftTrigger);
    refTriangleBank[parentObjName + "_rightTrigger"].SetDisplay(inputManager->rightTrigger);

    refTriangleBank[parentObjName + "_leftStick"].SetDisplay(inputManager->leftStick);
    refTriangleBank[parentObjName + "_rightStick"].SetDisplay(inputManager->rightStick);

    refLineBank[parentObjName + "_leftStickDir"].SetPoint2(inputManager->leftStickPos.x * fStickLineMultiplier, inputManager->leftStickPos.y * -fStickLineMultiplier);
    refLineBank[parentObjName + "_rightStickDir"].SetPoint2(inputManager->rightStickPos.x * fStickLineMultiplier, inputManager->rightStickPos.y * -fStickLineMultiplier);
}