#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Quad.h"
#include "Controller.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "PlayerController.h"
#include "GameObjectManager.h"

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
public:
	World();

	void Initialize();
};