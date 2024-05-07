#pragma once
#include "Source/pch.h"
#include "GameObject.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Controller.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/BoxCollider.h"
#include "Source/Components/PlayerController.h"
#include "Source/Managers/GameObjectManager.h"

// Responsible for initializing all our game objects.
class World
{
private:
    const int defaultSizeMult = 975.f;

    GameObjectManager* resourceManager;

    GameObject ground;
    Quad groundShape;

    // Create the player.
    GameObject player;
    Quad playerShape;
    GameObject controller;

    std::vector<std::pair<int, int>> worldColliderLayerPairs = {};

    void PrepCollisionLayers();
public:
	World();

	void Initialize();
};