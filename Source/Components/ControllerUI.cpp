#pragma once

#include "pch.h"
#include "ControllerUI.h"
#include "Source/Managers/GameObjectManager.h"

void ControllerUI::Update(float deltaTime) 
{
    // Update resource data manager triangles not here.
    resourceManager = GameObjectManager::GetInstance();

    resourceManager->GetTxtObj("connectionStatus").SetText(inputManager->isConnected ? "On" : "Off");
    std::unordered_map<std::string, Triangle>& refTriangleBank = resourceManager->GetTriObjBank();
    std::unordered_map<std::string, Line>& refLineBank = resourceManager->GetLnObjBank();

    refTriangleBank["a"].SetDisplay(inputManager->a);
    refTriangleBank["b"].SetDisplay(inputManager->b);
    refTriangleBank["x"].SetDisplay(inputManager->x);
    refTriangleBank["y"].SetDisplay(inputManager->y);
    refTriangleBank["start"].SetDisplay(inputManager->start);
    refTriangleBank["view"].SetDisplay(inputManager->view);

    refTriangleBank["dPadUp"].SetDisplay(inputManager->dPadUp);
    refTriangleBank["dPadDown"].SetDisplay(inputManager->dPadDown);
    refTriangleBank["dPadLeft"].SetDisplay(inputManager->dPadLeft);
    refTriangleBank["dPadRight"].SetDisplay(inputManager->dPadRight);

    refTriangleBank["leftShoulder"].SetDisplay(inputManager->leftShoulder);
    refTriangleBank["rightShoulder"].SetDisplay(inputManager->rightShoulder);
    refTriangleBank["leftTrigger"].SetDisplay(inputManager->leftTrigger);
    refTriangleBank["rightTrigger"].SetDisplay(inputManager->rightTrigger);

    refTriangleBank["leftStick"].SetDisplay(inputManager->leftStick);
    refTriangleBank["rightStick"].SetDisplay(inputManager->rightStick);

    refLineBank["leftStickDir"].SetPoint2(inputManager->leftStickPos.x * fStickLineMultiplier, inputManager->leftStickPos.y * -fStickLineMultiplier);
    refLineBank["rightStickDir"].SetPoint2(inputManager->rightStickPos.x * fStickLineMultiplier, inputManager->rightStickPos.y * -fStickLineMultiplier);
}