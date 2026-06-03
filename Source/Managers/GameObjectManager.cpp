#pragma once

#include "pch.h"
#include "GameObjectManager.h"
#include "Source/UI_Objects/Image.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Shapes/Triangle.h"
#include "Source/UI_Objects/Shapes/Shape.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/Enum/EnumData.h"
#include "Source/Components/PlayerController.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/ControllerUI.h"
#include "Source/Components/DebuggerUI.h"
#include "Source/Components/Camera.h"
#include "Source/Managers/SpriteManager.h"
#include "Source/Components/AnimationController.h"

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager* GameObjectManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new GameObjectManager();
    }
    
    return instance;
}

GameObjectManager::GameObjectManager()
{
}

std::unordered_map<int, std::unordered_map<std::string, BoxCollider>>& GameObjectManager::GetColliderObjBank()
{
	return colliderObjBank;
}

std::vector<std::pair<int, int>>& GameObjectManager::GetColliderLayerPairs()
{
	return colliderPairs;
}

void GameObjectManager::AddColliderLayerPair(const std::pair<int, int>& pair)
{
    colliderPairs.emplace_back(pair);
}

void GameObjectManager::AddColliderObj(int id, const std::string& objId, const BoxCollider& colliderObj)
{
	if (colliderObjBank.find(id) == colliderObjBank.end())
	{
        colliderObjBank[id] = {};
	}

	colliderObjBank[id][objId] = colliderObj;
}

GameObjectManager::~GameObjectManager() 
{
    delete instance;
}