#pragma once
#include "pch.h"
#include "MapEditor.h"

// Responsible for initializing all our game objects.
class World
{
private:
	MapEditor editor;

public:
	World();

	void Initialize();

	void Update(float elapsedTime);
};