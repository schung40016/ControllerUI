#include "pch.h"
#include "fstream"
#include "iostream"
#include "MapEditor.h"
#include "GameObject.h"
#include "Source/Enum/EnumData.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/BoxCollider.h"
#include "Source/Components/PlayerController.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Managers/InputManager.h"
#include "Source/Managers/InputController.h"
#include "Source/CustomObjects/Sprite.cpp"
#include "ExternalLibraries/json.hpp"
#include "Source/Constants/DefaultValues.h"

MapEditor::MapEditor()
{
    resourceManager = GameObjectManager::GetInstance();
    inputManager = InputManager::GetInstance();
}

void MapEditor::Initialize()
{
    Load();
}

void MapEditor::Update()
{
	// Open up game engine console.
	if (InputController::GetButtonDown("Edit"))
	{
		isEditMode = !isEditMode;
	}

	if (isEditMode)
	{
		if (inputManager->GetMouse().leftButton)
		{
            // Prep properties.
            DirectX::SimpleMath::Vector2 mousePos = { (float)inputManager->GetMouse().x, (float)inputManager->GetMouse().y };

            // Temporary
            Box newBox(DefaultValues::DEFAULT_SIZE, DefaultValues::DEFAULT_NAME, mousePos);
		}

		if (inputManager->GetMouse().rightButton)
		{
            // Try showing a gray box on the side for now.
			//ShowProperties();
		}
	}
}

/// <inheritdoc/>
void MapEditor::Load()
{
	// Scan the file.
	nlohmann::json scanner;
	GetJsonScanner(jsonWorldPath) >> scanner;

    PrepareObjects();

    PrepareSprites();

    PrepCollisionLayers();
}

/// <inheritdoc/>
void MapEditor::LoadObjects(nlohmann::json scanner)
{
	// Populate objects.
	for (const auto& block : scanner["blocks"])
	{
		Box b(block["defaultSize"], block["name"], { block["position"][0].get<float>(), block["position"][1].get<float>() }, block["width"], block["length"], block["isColliding"]);

		blocks.emplace_back(b);
	}
}

/// <inheritdoc/>
void MapEditor::LoadScripts(nlohmann::json scanner)
{
}

/// <inheritdoc/>
void MapEditor::Save()
{
}

/// <inheritdoc/>
void MapEditor::PrepCollisionLayers()
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

/// <inheritdoc/>
void MapEditor::PrepareSprites()
{
    // Add sprites to list.
    std::unordered_map<std::string, std::vector<Sprite>> playerSprites = {};

    // Scan the file.
    nlohmann::json scanner;
    GetJsonScanner(jsonSpritePath) >> scanner;

    if (!scanner.contains("playerSprites"))
    {
        return;
	}

    for (const auto& spriteSet : scanner["playerSprites"])
    {
        std::vector<Sprite> tempSpriteSet = {};

        if(!spriteSet.is_array())
        {
            continue;
        }

        // Loop through every sprite in the set, create and add RECT and Sprite objects.
        for (const auto& sprite : spriteSet)
        {
            // Validate required fields.
            if (!sprite.contains("rect") || !sprite["rect"].is_array() || sprite["rect"].size() != 4)
            {
                continue;
            }

            Sprite tempSprite;

            const auto& rect = sprite["rect"];
            RECT tempRect = {
                static_cast<LONG>(rect[0].get<int>()),
                static_cast<LONG>(rect[1].get<int>()),
                static_cast<LONG>(rect[2].get<int>()),
                static_cast<LONG>(rect[3].get<int>())
            };

            const std::string baseName = sprite.value("name", std::string());
            const int spriteCount = sprite.value("spriteCount", 0);
			tempSprite.sName = baseName + "_" + std::to_string(spriteCount);

			const auto originJson = sprite.value("origin", nlohmann::json::array({0.0f, 0.0f}));
            tempSprite.origin = { originJson[0].get<float>(), originJson[1].get<float>() };
            tempSprite.sourceRect = tempRect;

            tempSpriteSet.emplace_back(std::move(tempSprite));
        }

        // Add vector items into unordered_map using the first item's name as the key.
        playerSprites[spriteSet[0]["name"]] = tempSpriteSet;
    }
    playerSpriteManager = SpriteManager(player.GetPlayerName(), playerSprites);
}

/// <inheritdoc/>
void MapEditor::PrepareObjects()
{
    // Scan the file.
    nlohmann::json scanner;
    GetJsonScanner(jsonWorldPath) >> scanner;

    // Populate objects.
    for (const auto& block : scanner["blocks"])
    {
        Box b(block["defaultSize"], block["name"], { block["position"][0].get<float>(), block["position"][1].get<float>() }, block["width"], block["length"], block["isColliding"]);

        blocks.emplace_back(b);
    }

    const auto& playScan = scanner["player"];
    const auto& conScan = scanner["controller"];
    const auto& debugScan = scanner["debug"];
    player = Player(playScan["defaultSize"], playScan["name"], { playScan["position"][0].get<float>(), playScan["position"][1].get<float>() }, playScan["width"], playScan["length"]);
    controller = Controller(conScan["defaultSize"], conScan["name"], { conScan["position"][0].get<float>(), conScan["position"][1].get<float>() });
    debugger = Debugger(debugScan["defaultSize"], debugScan["name"], debugScan["playerObj"], { debugScan["position"][0].get<float>(), debugScan["position"][1].get<float>() });
}

/// <inheritdoc/>
std::ifstream MapEditor::GetJsonScanner(const std::string& path)
{
	// Fetch JSON file.
	std::ifstream file(path);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + path);
	}

	return file;
}
