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
std::vector<GameObject>& GameObjectManager::GetGameObjBank()
{
	return gameObjBank;
}

std::vector<Image>& GameObjectManager::GetImgObjBank()
{
	return imgObjBank;
}

std::vector<Text>& GameObjectManager::GetTxtObjBank()
{
	return txtObjBank;
}

std::vector<Triangle>& GameObjectManager::GetTriObjBank()
{
	return triObjBank;
}

std::vector<Line>& GameObjectManager::GetLnObjBank()
{
	return lnObjBank;
}

std::vector<Quad>& GameObjectManager::GetQuadObjBank()
{
    return quadObjBank;
}

// Adders
void GameObjectManager::AddGameObj(const GameObject& inp_gameObject)
{
    gameObjBank.emplace_back(inp_gameObject);
}

void GameObjectManager::AddImgObj(const Image& inp_imgObj)
{
    imgObjBank.emplace_back(inp_imgObj);
}

void GameObjectManager::AddTxtObj(const Text& inp_txtObj)
{
    txtObjBank.emplace_back(inp_txtObj);
}

void GameObjectManager::AddTriObj(const Triangle& inp_triObj)
{
    triObjBank.emplace_back(inp_triObj);
}

void GameObjectManager::AddLnObj(const Line& inp_lnObj)
{
    lnObjBank.emplace_back(inp_lnObj);
}

void GameObjectManager::AddQuadObj(const Quad& inp_quadObj)
{
    quadObjBank.push_back(inp_quadObj);
}