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
    ground = SolidBox(defaultSizeMult, "ground", { 650.f, 800.f }, 800.f, 50.f);
    platform = SolidBox(defaultSizeMult, "platform", { 400.f, 650.f }, 200.f, 50.f);
    platform1 = SolidBox(defaultSizeMult, "platform2", { 800.f, 650.f }, 200.f, 50.f);
    wall = SolidBox(defaultSizeMult, "wall", { 200.f, 625.f }, 100.f, 400.f);
    wall2 = SolidBox(defaultSizeMult, "wall2", { 1100.f, 625.f }, 100.f, 400.f);
    player = Player(defaultSizeMult, "player", {650.f, 650.f}, 50.f, 60.f);
    controller = Controller(defaultSizeMult * 3, "controller", { 150.f, 100.f });
    debugger = Debugger(defaultSizeMult * 3, "debugger", "player", {900.f, 25.f});

    PrepCollisionLayers();
}

void World::PrepCollisionLayers()
{
    std::vector<std::vector<int>> colliderLayerMapping = {};

    colliderLayerMapping.push_back({ EnumData::ColliderLayers::Ground, EnumData::ColliderLayers::Player });
    colliderLayerMapping.push_back({ EnumData::ColliderLayers::Ground });

    for (int i = 0; i < colliderLayerMapping.size(); i++)
    {
        for (int j = 0; j < colliderLayerMapping[i].size(); j++)
        {
            worldColliderLayerPairs.emplace_back(std::make_pair(i, j));
        }
    }

    for (int i = 0; i < worldColliderLayerPairs.size(); i++)
    {
        resourceManager->AddColliderLayerPair(worldColliderLayerPairs[i]);
    }
}