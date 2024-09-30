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

std::unordered_map<int, std::unordered_map<std::string, BoxCollider>>& GameObjectManager::GetColliderObjBank()
{
    return colliderObjBank;
}

std::vector<std::pair<int, int>>& GameObjectManager::GetColliderLayerPairs()
{
    return colliderPairs;
}

std::unordered_map<std::string, DebuggerUI>& GameObjectManager::GetDebuggerUIObjBank()
{
    return debuggerUIBank;
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

PlayerController& GameObjectManager::GetPlayerController(const std::string id)
{
    return controllerBank[id];
}

RigidBody& GameObjectManager::GetRigidBody(const std::string id)
{
    return rigidBodyBank[id];
}

ControllerUI& GameObjectManager::GetControllerUI(const std::string id)
{
    return controllerUIBank[id];
}

DebuggerUI& GameObjectManager::GetDebuggerUI(const std::string id)
{
    return debuggerUIBank[id];
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

void GameObjectManager::AddColliderLayerPair(std::pair<int, int>& inp_pair)
{
    colliderPairs.emplace_back(inp_pair);
}

void GameObjectManager::AddColliderObj(int id, std::string objId , const BoxCollider& inp_colliderObj)
{
    if (colliderObjBank[id].empty())
    {
        colliderObjBank[id] = {};
    }
    colliderObjBank[id][objId] = inp_colliderObj;
}

void GameObjectManager::AddPlayerController(std::string id, const PlayerController& inp_playerController)
{
    controllerBank[id] = inp_playerController;
}

void GameObjectManager::AddRigidBody(std::string id, const RigidBody& inp_rigidBody)
{
    rigidBodyBank[id] = inp_rigidBody;
}

void GameObjectManager::AddControllerUI(std::string id, const ControllerUI& inp_controllerUI)
{
    controllerUIBank[id] = inp_controllerUI;
}

void GameObjectManager::AddDebuggerUI(std::string id, const DebuggerUI& inp_debuggerUI)
{
    debuggerUIBank[id] = inp_debuggerUI;
}

GameObjectManager::~GameObjectManager() {
    delete instance;
}