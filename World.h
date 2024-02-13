#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Quad.h"
#include "Controller.h"
#include "RigidBody.h"
#include "Collider.h"
#include "PlayerController.h"

// Responsible for initializing all our game objects.
class World
{
private:
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