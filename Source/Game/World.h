#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/CustomObjects/Controller.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/BoxCollider.h"
#include "Source/Components/PlayerController.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/CustomObjects/Player.h"
#include "Source/CustomObjects/SolidBox.h"

// Responsible for initializing all our game objects.
class World
{
private:
    const int defaultSizeMult = 975.f;

    GameObjectManager* resourceManager;

    // Create custom objects:
    SolidBox ground;
    Player player;
    Controller controller;

    std::vector<std::pair<int, int>> worldColliderLayerPairs = {};

    void PrepCollisionLayers();
public:
	World();

	void Initialize();
};