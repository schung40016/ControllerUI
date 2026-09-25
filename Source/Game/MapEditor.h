#pragma once
#include "pch.h"
#include "Source/CustomObjects/Controller.h"
#include "Source/CustomObjects/Box.h"
#include "Source/CustomObjects/Player.h"
#include "Source/CustomObjects/Debugger.h"
#include "Source/Managers/SpriteManager.h"
#include "ExternalLibraries/json.hpp"

class MapEditor
{
private:
	class GameObjectManager* resourceManager;
	class InputManager* inputManager;

	bool isEditMode = false;

	// Previous frame's left mouse state, used to detect a single click instead of a held button.
	bool wasLeftMouseDown = false;

	// Incrementing suffix that keeps every placed box's name unique.
	int nextPlacedBoxId = 0;
	const std::string placedBoxPrefix = "editorBox_";

	// Create custom objects:
	std::vector<Box> blocks = {};
	Player player;
	Controller controller;
	Debugger debugger;
	SpriteManager playerSpriteManager;

	std::vector<std::pair<int, int>> worldColliderLayerPairs = {};

	// JSON directories:
	const std::string jsonWorldPath = "JSON/World.json";
	const std::string jsonSpritePath = "JSON/Sprites.json";

	void Load();

	void LoadObjects(nlohmann::json scanner);

	void LoadScripts(nlohmann::json scanner);

	void Save();

	void PrepCollisionLayers();

	void PrepareObjects();

	void PrepareSprites();

	DirectX::SimpleMath::Vector2 GetCameraOffset();

	void PlaceBox(const DirectX::SimpleMath::Vector2& position);

	std::string GenerateBoxName();

	std::ifstream GetJsonScanner(const std::string& path);

public:
	MapEditor();

	void Update();

	void Initialize();
};