#include "pch.h"
#include "World.h"
#include "fstream"
#include "iostream"
#include "GameObject.h"
#include "Source/Enum/EnumData.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/BoxCollider.h"
#include "Source/Components/PlayerController.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/CustomObjects/Sprite.cpp"
#include "ExternalLibraries/json.hpp"

World::World()
{
    resourceManager = GameObjectManager::GetInstance();
}

void World::Initialize()
{
    resourceManager = GameObjectManager::GetInstance();
    std::string playerObjectName = "player";

    PrepareObjects();

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
        worldColliderLayerPairs.emplace_back(std::make_pair(colliderLayerMapping[i][0], colliderLayerMapping[i][1]));
    }

    for (int i = 0; i < worldColliderLayerPairs.size(); i++)
    {
        resourceManager->AddColliderLayerPair(worldColliderLayerPairs[i]);
    }
}

void World::PrepareSprites()
{
    // Add sprites to list.
    std::unordered_map<std::string, std::vector<Sprite>> playerSprites = {};

    // Scan the file.
    nlohmann::json scanner;
    GetJsonScanner(jsonSpritePath) >> scanner;

    for (const auto& spriteSet : scanner["playerSprites"])
    {
        // Create temp sprite vector.
        std::vector<Sprite> tempSpriteSet = {};

        // Loop through every sprite in the set, create and add RECT and Sprite objects.
        for (const auto& sprite : spriteSet)
        {
            Sprite tempSprite;

            RECT tempRect = { sprite["rect"][0], sprite["rect"][1], sprite["rect"][2], sprite["rect"][3] };
            std::cout << sprite.dump(2) << std::endl;

            tempSprite.sName = sprite["name"].get<std::string>() + "_" + std::to_string(sprite["spriteCount"].get<int>());
            tempSprite.origin = { sprite["origin"][0].get<float>(), sprite["origin"][1].get<float>() };
            tempSprite.sourceRect = tempRect;

            tempSpriteSet.emplace_back(tempSprite);
        }

        // Add vector items into unordered_map using the first item's name as the key.
        playerSprites[spriteSet[0]["name"]] = tempSpriteSet;
    }
    playerSpriteManager = SpriteManager(player.GetPlayerName(), playerSprites);
}

void World::PrepareObjects()
{
    // Scan the file.
    nlohmann::json scanner;
    GetJsonScanner(jsonWorldPath) >> scanner;

    // Populate objects.
    for (const auto& block : scanner["blocks"])
    {
        SolidBox b(block["defaultSize"], block["name"], { block["position"][0].get<float>(), block["position"][1].get<float>() }, block["width"], block["length"]);

        blocks.push_back(b);
    }

    const auto& playScan = scanner["player"];
    const auto& conScan = scanner["controller"];
    const auto& debugScan = scanner["debug"];
    player = Player(playScan["defaultSize"], playScan["name"], { playScan["position"][0].get<float>(), playScan["position"][1].get<float>() }, playScan["width"], playScan["length"]);
    controller = Controller(conScan["defaultSize"], conScan["name"], { conScan["position"][0].get<float>(), conScan["position"][1].get<float>() });
    debugger = Debugger(debugScan["defaultSize"], debugScan["name"], debugScan["playerObj"], { debugScan["position"][0].get<float>(), debugScan["position"][1].get<float>() });
}

std::ifstream World::GetJsonScanner(const std::string& path)
{
    // Fetch JSON file.
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + path);
    }

    return file;
}

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