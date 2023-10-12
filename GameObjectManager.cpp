#pragma once

#include "pch.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::GameObjectManager(float horizontal, float vertical)
{
	// Load all objects.
	gameObjBank["Controller"] = GameObject((horizontal / 2.f), (vertical / 2.f), std::min(horizontal, vertical));

    txtObjBank["Title"] = Text(DirectX::Colors::Black, "ControllerUI", gameObjBank["Controller"], 0.f, -250.f);
    txtObjBank["Connection"] = Text(DirectX::Colors::Black, "Controller Connection: ", gameObjBank["Controller"], -50.f, 250.f);
    txtObjBank["Status"] = Text(DirectX::Colors::Black, "Connected", gameObjBank["Controller"], 300.f, 250.f);

    // Create a higher tier object to act as the parent for all these objects.
    imgObjBank["Gamepad"] = Image(DirectX::Colors::White, ".\\Images\\gamepad.png", EnumData::Descriptors::Controller, gameObjBank["Controller"], 0.f, 0.f, 1.f);
    imgObjBank["LeftTrigger"] = Image(DirectX::Colors::White, ".\\Images\\LeftTrigger.png", EnumData::Descriptors::LeftTrigger, gameObjBank["Controller"], -290.f, -140.f, 1.f);
    imgObjBank["RightTrigger"] = Image(DirectX::Colors::White, ".\\Images\\RightTrigger.png", EnumData::Descriptors::RightTrigger, gameObjBank["Controller"], 290.f, -140.f, 1.f);

    triObjBank["A"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 108.f, -78.f);
    triObjBank["B"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 148.f, -120.f);
    triObjBank["X"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 68.f, -120.f);
    triObjBank["Y"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 108.f, -160.f);

    triObjBank["Start"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 0.f, -120.f);
    triObjBank["View"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -90.f, -120.f);
    triObjBank["DPadUp"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -123.f, -60.f);
    triObjBank["DPadDown"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -123.f, 10.f);
    triObjBank["DPadLeft"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -160.f, -25.f);
    triObjBank["DPadRight"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -80.f, -25.f);
    triObjBank["LeftShoulder"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -200.f, -220.f);
    triObjBank["RightShoulder"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 100.f, -220.f);
    triObjBank["LeftTrigger"] = Triangle(DirectX::Colors::HotPink, imgObjBank["LeftTrigger"], 1.f, -50.f, -30.f);
    triObjBank["RightTrigger"] = Triangle(DirectX::Colors::HotPink, imgObjBank["RightTrigger"], 1.f, -50.f, -30.f);
    triObjBank["LeftStick"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -198.f, -120.f);
    triObjBank["RightStick"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 32.f, -25.f);

    lnObjBank["LeftStick"] = Line(DirectX::Colors::HotPink, imgObjBank["Gamepad"], -148.f, -78.f, 1.f);
    lnObjBank["RightStick"] = Line(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 80.f, 15.f, 1.f);
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
