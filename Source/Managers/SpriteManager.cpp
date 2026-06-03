#include "pch.h"
#include "SpriteManager.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Managers/SpriteManager.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::SpriteManager(std::string inp_id, std::unordered_map<std::string, std::vector<Sprite>> inp_sprites)
{
	GameObjectManager* resourceManager = GameObjectManager::GetInstance();
	id = inp_id + "_SpriteManager";
	sprites = inp_sprites;
	resourceManager->Add<SpriteManager>(id, *this);
}

void SpriteManager::AddSprite(const std::string inp_spriteName, const std::vector<Sprite> inp_sprites)
{
	sprites[inp_spriteName] = inp_sprites;
}

const std::vector<Sprite> SpriteManager::GetSpriteSet(const std::string inp_spriteName)
{
	return sprites[inp_spriteName];
}