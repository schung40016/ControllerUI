#include "pch.h"
#include "World.h"
#include "Source/Enum/EnumData.h"
#include "GameObject.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/BoxCollider.h"
#include "Source/Components/PlayerController.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/CustomObjects/Sprite.cpp"

World::World()
{
    resourceManager = GameObjectManager::GetInstance();
}

void World::Initialize()
{
    resourceManager = GameObjectManager::GetInstance();
    std::string playerObjectName = "player";

    // Make custom objects.
    ground = SolidBox(defaultSizeMult, "ground", { 650.f, 175.f }, 800.f, 50.f);
    platform = SolidBox(defaultSizeMult, "platform", { 400.f, 325.f }, 200.f, 50.f);
    platform1 = SolidBox(defaultSizeMult, "platform2", { 800.f, 325.f }, 200.f, 50.f);
    wall = SolidBox(defaultSizeMult, "wall", { 200.f, 350.f }, 100.f, 400.f);
    wall2 = SolidBox(defaultSizeMult, "wall2", { 1100.f, 350.f }, 100.f, 400.f);
    player = Player(defaultSizeMult, playerObjectName, {650.f, 325.f }, 50.f, 60.f);
    controller = Controller(defaultSizeMult * 3, "controller", { 150.f, 875.f });
    debugger = Debugger(defaultSizeMult * 3, "debugger", "player", {900.f, 800.f});

    PrepareSprites();

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

void World::PrepareSprites()
{
    // Create sprites.
    std::string idleSpriteName = "Idle";
    RECT rectIdle = { 100, 400, 250, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 76.f, 110.f };
    spriteIdle.sourceRect = rectIdle;

    std::string jumpSpriteName = "Jump";
    RECT rectJump = { 170, 725, 360, 1200 };
    Sprite spriteJump;
    spriteJump.sName = jumpSpriteName + "_1";
    spriteJump.origin = { 100.f, 115.f };
    spriteJump.sourceRect = rectJump;

    std::string runSpriteName = "Run";
    RECT rectRun = { 375, 400, 550, 600 };
    Sprite spriteRun;
    spriteRun.sName = runSpriteName + "_1";
    spriteRun.origin = { 90.f, 110.f };
    spriteRun.sourceRect = rectRun;

    RECT rectRun2 = { 555, 400, 695, 600 };
    Sprite spriteRun2;
    spriteRun2.sName = runSpriteName + "_2";
    spriteRun2.origin = { 70.f, 110.f };
    spriteRun2.sourceRect = rectRun2;

    RECT rectRun3 = { 700, 400, 850, 600 };
    Sprite spriteRun3;
    spriteRun3.sName = runSpriteName + "_3";
    spriteRun3.origin = { 75.f, 110.f };
    spriteRun3.sourceRect = rectRun3;

    // Add sprites to list.
    std::unordered_map<std::string, std::vector<Sprite>> playerSprites = {};
    playerSprites[idleSpriteName] = { spriteIdle };
    playerSprites[jumpSpriteName] = { spriteJump };
    playerSprites[runSpriteName] = { spriteRun, spriteRun2, spriteRun3 };

    playerSpriteManager = SpriteManager(player.GetPlayerName(), playerSprites);
}

// TUne physics engine to feel smoother.
// Add map manager. 


/*
SPRITE INFORMATION

{ left, top, right, bottom}

IDLE:
    RECT rectIdle = { 100, 400, 250, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 76.f, 110.f };
    spriteIdle.sourceRect = rectIdle;


JUMP:
    RECT rectJump = { 170, 725, 360, 1200 };
    Sprite spriteJump;
    spriteJump.sName = jumpSpriteName + "_1";
    spriteJump.origin = { 100.f, 115.f };
    spriteJump.sourceRect = rectJump;

RUN:
    RECT rectIdle = { 375, 400, 550, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 90.f, 110.f };
    spriteIdle.sourceRect = rectIdle;

    RECT rectIdle = { 555, 400, 695, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 70.f, 110.f };
    spriteIdle.sourceRect = rectIdle;

        RECT rectIdle = { 700, 400, 850, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 75.f, 110.f };
    spriteIdle.sourceRect = rectIdle;
*/