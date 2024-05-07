#pragma once
#include "Source/pch.h"

class EnumData {
public:
    enum Descriptors
    {
        MyFont,
        Controller,
        LeftTrigger,
        RightTrigger,
        Count
    };

    enum ColliderLayers
    {
        Player,
        Ground
    };
};
