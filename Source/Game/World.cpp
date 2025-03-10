#include "pch.h"
#include "World.h"
#include "Source/Enum/EnumData.h"
#include "GameObject.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/BoxCollider.h"
#include "Source/Components/PlayerController.h"
#include "Source/Managers/GameObjectManager.h"

World::World()
{
    resourceManager = GameObjectManager::GetInstance();
}

void World::Initialize()
{
    resourceManager = GameObjectManager::GetInstance();

    // Make custom objects.
    ground = SolidBox(defaultSizeMult, "ground", { 650.f, 175.f }, 800.f, 50.f);
    platform = SolidBox(defaultSizeMult, "platform", { 400.f, 325.f }, 200.f, 50.f);
    platform1 = SolidBox(defaultSizeMult, "platform2", { 800.f, 325.f }, 200.f, 50.f);
    wall = SolidBox(defaultSizeMult, "wall", { 200.f, 350.f }, 100.f, 400.f);
    wall2 = SolidBox(defaultSizeMult, "wall2", { 1100.f, 350.f }, 100.f, 400.f);
    player = Player(defaultSizeMult, "player", {650.f, 325.f }, 50.f, 60.f);
    controller = Controller(defaultSizeMult * 3, "controller", { 150.f, 875.f });
    debugger = Debugger(defaultSizeMult * 3, "debugger", "player", {900.f, 800.f});

    PrepCollisionLayers();
}

void World::PrepCollisionLayers()
{
    std::vector<std::vector<int>> colliderLayerMapping = {};

    colliderLayerMapping.push_back({ EnumData::ColliderLayers::Player, EnumData::ColliderLayers::Ground });
    colliderLayerMapping.push_back({ EnumData::ColliderLayers::Ground, EnumData::ColliderLayers::Ground });

    for (int i = 0; i < colliderLayerMapping.size(); i++) // 0, 1
    {
        //for (int j = 0; j < colliderLayerMapping[i].size(); j++) // 
        //{
        //    worldColliderLayerPairs.emplace_back(std::make_pair(colliderLayerMapping[i][j], j));
        //}
        worldColliderLayerPairs.emplace_back(std::make_pair(colliderLayerMapping[i][0], colliderLayerMapping[i][1]));
    }

    for (int i = 0; i < worldColliderLayerPairs.size(); i++)
    {
        resourceManager->AddColliderLayerPair(worldColliderLayerPairs[i]);
    }
}

// TUne physics engine to feel smoother.
// Add animation manager. (feed spritesheet, and animate based on conditions)
// movement flags - set flag based on character's movement (state).
// Add map manager. 