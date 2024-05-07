#include "Source/pch.h"
#include "World.h"
#include "Source/Enum/EnumData.h"

World::World()
{
}

// For every new keyword, in a world destroyer, delete the pointer "free it up".
// Create a player object that initializes all these components.
// Redo Readme.txt to include build.exe steps and entire project steps.
// Separate all files into respective folders (file explorer).
// Try to build this on another machine. (put steps into readme.txt)

void World::Initialize()
{
    resourceManager = GameObjectManager::GetInstance();

    ground = GameObject("ground", { 650.f, 800.f }, defaultSizeMult);
    GameObject& refGround = resourceManager->GetGameObj("ground");
    groundShape = Quad("groundShape", DirectX::Colors::DarkGray, resourceManager->GetGameObj("ground"), 1.f, 0, 0, 800.f, 200.f, true);
    std::vector<DirectX::SimpleMath::Vector2> groundCollisionBox = { { -400.f, 100.f }, {400.f, 100.f}, {400.f, -100.f}, {-400.f, -100.f} };

    // Create the player.
    player = GameObject("player", { 650.f, 650.f }, defaultSizeMult);

    GameObject& tempPlayer = resourceManager->GetGameObj("player");
    std::vector<DirectX::SimpleMath::Vector2> playerCollisionBox = { { -25.f, 25.f }, {25.f, 25.f}, {25.f, -25.f}, {-25.f, -25.f} };
    playerShape = Quad("playerShape", DirectX::Colors::Aqua, tempPlayer, 1.f, 0, 0, 50.f, 50.f, true);

    // Create colliders.
    BoxCollider groundCollider = BoxCollider(refGround, groundCollisionBox, false);
    BoxCollider playerCollider(tempPlayer, playerCollisionBox, true);

    resourceManager->AddColliderObj(EnumData::ColliderLayers::Ground, "groundCollider", groundCollider);
    resourceManager->AddColliderObj(EnumData::ColliderLayers::Player, "playerCollider", playerCollider);

    refGround.SetComponents({
        &resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Ground]["groundCollider"]
    });

    tempPlayer.SetComponents({
        &resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Player]["playerCollider"],
        new PlayerController(tempPlayer, resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Player]["playerCollider"]),
        new RigidBody(tempPlayer, 10.f)
    });

    controller = GameObject("controller", { 150.f, 100.f }, 3 * defaultSizeMult);
    GameObject& refController = resourceManager->GetGameObj("controller");    
    refController.SetComponents({
        new Controller(refController)
    });

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

//gameObjBank["Player"].SetComponents({
//    new PlayerController(gameObjBank["Player"]),
//    new RigidBody(gameObjBank["Player"], 10.f)
//    //Collider(gameObjBank["Player"], p2),  
//    //RigidBody(gameObjBank["Player"], {1, 0}, true, 10.f, 1.f),
//});

//shpObjBank.emplace_back(new Quad(DirectX::Colors::Aqua, gameObjBank["Player"], 1.f, 0, 0, 50.f, 50.f, true));