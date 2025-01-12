#pragma once
#include "pch.h"

class EnumData {
public:
    enum Descriptors
    {
        MyFont,
        Controller,
        LeftTrigger,
        RightTrigger,
        PlayerImage,
        Count
    };

    enum ColliderLayers
    {
        Player,
        Ground
    };
};
