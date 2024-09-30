#include "pch.h"
#include "World.h"
#include "Source/Enum/EnumData.h"

World::World()
{
    resourceManager = GameObjectManager::GetInstance();
}

// For every new keyword, in a world destroyer, delete the pointer "free it up". DONE.
// Create a player object that initializes all these components. DONE.
// Redo Readme.txt to include build.exe steps and entire project steps.
// Separate all files into respective folders (file explorer). DONE.
// Try to build this on another machine. (put steps into readme.txt)

void World::Initialize()
{
    resourceManager = GameObjectManager::GetInstance();

    // Make custom objects.
    ground = SolidBox(defaultSizeMult, "ground", { 650.f, 800.f }, 800.f, 200.f);
    player = Player(defaultSizeMult, "player", {650.f, 650.f}, 50.f, 50.f);
    controller = Controller(defaultSizeMult * 3, "controller", { 150.f, 100.f });
    debugger = Debugger(defaultSizeMult * 3, "debugger", "player", {1000.f, 25.f});

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