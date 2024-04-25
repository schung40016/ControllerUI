#include "pch.h"
#include "World.h"
#include "EnumData.h"

World::World()
{
}

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

    resourceManager->AddColliderObj(EnumData::ColliderLayers::Object, "groundCollider", groundCollider);
    resourceManager->AddColliderObj(EnumData::ColliderLayers::Object, "playerCollider", playerCollider);

    refGround.SetComponents({
        &resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Object]["groundCollider"]
    });

    tempPlayer.SetComponents({
        &resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Object]["playerCollider"],
        new PlayerController(tempPlayer, resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Object]["playerCollider"]),
        new RigidBody(tempPlayer, 10.f)
    });


    controller = GameObject("controller", { 150.f, 100.f }, 3 * defaultSizeMult);
    GameObject& refController = resourceManager->GetGameObj("controller");    
    refController.SetComponents({
        new Controller(refController)
    });
}

//gameObjBank["Player"].SetComponents({
//    new PlayerController(gameObjBank["Player"]),
//    new RigidBody(gameObjBank["Player"], 10.f)
//    //Collider(gameObjBank["Player"], p2),  
//    //RigidBody(gameObjBank["Player"], {1, 0}, true, 10.f, 1.f),
//});

//shpObjBank.emplace_back(new Quad(DirectX::Colors::Aqua, gameObjBank["Player"], 1.f, 0, 0, 50.f, 50.f, true));