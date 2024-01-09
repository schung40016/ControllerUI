#pragma once

#include "pch.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::GameObjectManager(float horizontal, float vertical)
{
    // Load all objects. 
    // Gamepad default position: (horizontal / 2.f), (vertical / 2.f).
    gameObjBank["Controller"] = GameObject({(horizontal / 10.f), (vertical / 9.0f)}, 2500.f);
    gameObjBank["Ground"] = GameObject({ 650.f, 800.f }, 1.f);

    txtObjBank["Title"] = Text(DirectX::Colors::Black, "ControllerUI", gameObjBank["Controller"], 0.f, -250.f);
    txtObjBank["Connection"] = Text(DirectX::Colors::Black, "Controller Connection: ", gameObjBank["Controller"], -50.f, 250.f);
    txtObjBank["Status"] = Text(DirectX::Colors::Black, "Connected", gameObjBank["Controller"], 300.f, 250.f);

    // Create a higher tier object to act as the parent for all these objects.
    imgObjBank["Gamepad"] = Image(DirectX::Colors::White, ".\\Images\\gamepad.png", EnumData::Descriptors::Controller, gameObjBank["Controller"], 0.f, 0.f, 1.f);
    imgObjBank["LeftTrigger"] = Image(DirectX::Colors::White, ".\\Images\\LeftTrigger.png", EnumData::Descriptors::LeftTrigger, gameObjBank["Controller"], -290.f, -140.f, 1.f);
    imgObjBank["RightTrigger"] = Image(DirectX::Colors::White, ".\\Images\\RightTrigger.png", EnumData::Descriptors::RightTrigger, gameObjBank["Controller"], 290.f, -140.f, 1.f);

    triObjBank["A"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 159.f, -38.f, 40.f, 40.f);
    triObjBank["B"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 199.f, -80.f, 40.f, 40.f);
    triObjBank["X"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 119.f, -80.f, 40.f, 40.f);
    triObjBank["Y"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 159.f, -120.f, 40.f, 40.f);

    triObjBank["Start"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 51.f, -80.f, 40.f, 40.f);
    triObjBank["View"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -39.f, -80.f, 40.f, 40.f);
    triObjBank["DPadUp"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -72.f, -20.f, 40.f, 40.f);
    triObjBank["DPadDown"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -72.f, 50.f, 40.f, 40.f);
    triObjBank["DPadLeft"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -109.f, 15.f, 40.f, 40.f);
    triObjBank["DPadRight"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -39.f, 15.f, 40.f, 40.f);
    triObjBank["LeftShoulder"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -149.f, -180.f, 40.f, 40.f);
    triObjBank["RightShoulder"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 151.f, -180.f, 40.f, 40.f);
    triObjBank["LeftTrigger"] = Triangle(DirectX::Colors::HotPink, imgObjBank["LeftTrigger"], 1.f, 1.f, 10.f, 40.f, 40.f);
    triObjBank["RightTrigger"] = Triangle(DirectX::Colors::HotPink, imgObjBank["RightTrigger"], 1.f, 1.f, 10.f, 40.f, 40.f);
    triObjBank["LeftStick"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -147.f, -80.f, 40.f, 40.f);
    triObjBank["RightStick"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 83.f, 15.f, 40.f, 40.f);

    lnObjBank["LeftStick"] = Line(DirectX::Colors::HotPink, imgObjBank["Gamepad"], -148.f, -78.f, 1.f);
    lnObjBank["RightStick"] = Line(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 80.f, 15.f, 1.f);

    shpObjBank["Ground"] = new Quad(DirectX::Colors::DarkGray, gameObjBank["Ground"], 1.f, 0, 0, 800.f, 200.f, true);

    // Player
    // - consist of a square.
}

// Getters & Setters.
std::unordered_map<std::string, GameObject>& GameObjectManager::GetGameObjBank()
{
	return gameObjBank;
}

std::unordered_map<std::string, Image>& GameObjectManager::GetImgObjBank()
{
	return imgObjBank;
}

std::unordered_map<std::string, Text>& GameObjectManager::GetTxtObjBank()
{
	return txtObjBank;
}

std::unordered_map<std::string, Triangle>& GameObjectManager::GetTriObjBank()
{
	return triObjBank;
}

std::unordered_map<std::string, Line>& GameObjectManager::GetLnObjBank()
{
	return lnObjBank;
}

std::unordered_map<std::string, Shape*>& GameObjectManager::GetShpObjBank()
{
    return shpObjBank;
}