#pragma once

#include "pch.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Shapes/Triangle.h"
#include "Source/UI_Objects/Line.h"

class Controller
{
private:
    std::string sControllerName = "";
    float fSizeMultiplier = 975.f;

    float fStickLineMultiplier = 10.f;

public:
    Controller();

	Controller(float inp_size, std::string inp_controllerName, DirectX::SimpleMath::Vector2 inp_position);
};