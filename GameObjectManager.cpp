#pragma once

#include "pch.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::instance = NULL;

GameObjectManager* GameObjectManager::GetInstance()
{
    if (instance == NULL)
    {
        instance = new GameObjectManager();
        return instance;
    }
    
    return instance;
}

GameObjectManager::GameObjectManager()
{
    //gameObjBank["Ground"] = GameObject({ 650.f, 800.f }, 1.f);
    //shpObjBank["Ground"] = new Quad(DirectX::Colors::DarkGray, gameObjBank["Ground"], 1.f, 0, 0, 800.f, 200.f, true);

    //std::vector<DirectX::SimpleMath::Vector2> playerCollisionBox = { { 0.f, 0.f }, {0.f, 50.f}, {50.f, -50.f}, {0, -50.f} };

    //// Create the player.
    //gameObjBank["Player"] = GameObject({ 650.f, 650.f }, 1.f);

    //gameObjBank["Player"].SetComponents({
    //    new PlayerController(gameObjBank["Player"]),
    //    new RigidBody(gameObjBank["Player"], 10.f)
    //    //Collider(gameObjBank["Player"], p2),  
    //    //RigidBody(gameObjBank["Player"], {1, 0}, true, 10.f, 1.f),
    //});

    //shpObjBank.emplace_back(new Quad(DirectX::Colors::Aqua, gameObjBank["Player"], 1.f, 0, 0, 50.f, 50.f, true));
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

std::unordered_map<std::string, Quad>& GameObjectManager::GetQuadObjBank()
{
    return quadObjBank;
}

GameObject& GameObjectManager::GetGameObj(const std::string id)
{
    return gameObjBank[id];
}

Image& GameObjectManager::GetImgObj(const std::string id)
{
    return imgObjBank[id];
}

Text& GameObjectManager::GetTxtObj(const std::string id)
{
    return txtObjBank[id];
}

Triangle& GameObjectManager::GetTriObj(const std::string id)
{
    return triObjBank[id];
}

Line& GameObjectManager::GetLnObj(const std::string id)
{
    return lnObjBank[id];
}

Quad& GameObjectManager::GetQuadObj(const std::string id)
{
    return quadObjBank[id];
}

// Adders
void GameObjectManager::AddGameObj(std::string id, const GameObject& inp_gameObject)
{
    gameObjBank[id] = inp_gameObject;
}

void GameObjectManager::AddImgObj(std::string id, const Image& inp_imgObj)
{
    imgObjBank[id] = inp_imgObj;
}

void GameObjectManager::AddTxtObj(std::string id, const Text& inp_txtObj)
{
    txtObjBank[id] = inp_txtObj;
}

void GameObjectManager::AddTriObj(std::string id, const Triangle& inp_triObj)
{
    triObjBank[id] = inp_triObj;
}

void GameObjectManager::AddLnObj(std::string id, const Line& inp_lnObj)
{
    lnObjBank[id] = inp_lnObj;
}

void GameObjectManager::AddQuadObj(std::string id, const Quad& inp_quadObj)
{
    quadObjBank[id] = inp_quadObj;
}