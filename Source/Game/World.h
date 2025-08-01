#pragma once
#include "pch.h"
#include "Source/CustomObjects/Controller.h"
#include "Source/CustomObjects/SolidBox.h"
#include "Source/CustomObjects/Player.h"
#include "Source/CustomObjects/Debugger.h"
#include "Source/Managers/SpriteManager.h"

// Responsible for initializing all our game objects.
class World
{
private:
    const float defaultSizeMult = 975.f;

    class GameObjectManager* resourceManager;

    // Create custom objects:
    std::vector<SolidBox> blocks = {};
    SolidBox ground;
    SolidBox platform;
    SolidBox platform1;
    SolidBox wall;
    SolidBox wall2;
    Player player;
    Controller controller;
    Debugger debugger;
    SpriteManager playerSpriteManager;

    std::vector<std::pair<int, int>> worldColliderLayerPairs = {};

    // JSON directories:
    const std::string jsonWorldPath = "JSON/World.json";
    const std::string jsonSpritePath = "JSON/Sprites.json";

    void PrepCollisionLayers();

    void PrepareObjects();

    std::ifstream GetJsonScanner(const std::string& path);

public:
	World();

	void Initialize();

    void PrepareSprites();
};