#pragma once

#include "pch.h"
#include "../Constants/DefaultValues.h"

class Controller
{
private:
    std::string sControllerName = "";
    float fSizeMultiplier = DefaultValues::DEFAULT_SIZE;

    float fStickLineMultiplier = 10.f;

public:
    Controller();

	Controller(float inp_size, std::string inp_controllerName, DirectX::SimpleMath::Vector2 inp_position);
};