#pragma once

#include "pch.h"
#include "Source/CustomObjects/Sprite.cpp"

class GameObjectManager;

class SpriteManager {
private:
	std::string id = "";
	std::unordered_map<std::string, std::vector<Sprite>> sprites = {};
	GameObjectManager* resourceManager;

public:
	SpriteManager();

	SpriteManager(std::string inp_id, std::unordered_map<std::string, std::vector<Sprite>> sprites);

	void AddSprite(const std::string inp_spriteName, const std::vector<Sprite> inp_sprites);

	const std::vector<Sprite> GetSpriteSet(const std::string inp_spriteName);
};