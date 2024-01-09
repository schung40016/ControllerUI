#pragma once

#include "pch.h"
#include <GameObject.h>
#include <Image.h>
#include <Text.h>
#include <Triangle.h>
#include <Shape.h>
#include <Quad.h>
#include <Line.h>
#include <unordered_map>
#include <Collider.h>

class GameObjectManager {

private:
	// Controller objects here.
	std::unordered_map<std::string, GameObject> gameObjBank = {};
	std::unordered_map<std::string, Image> imgObjBank = {};
	std::unordered_map<std::string, Text> txtObjBank = {};
	std::unordered_map<std::string, Triangle> triObjBank = {};
	std::unordered_map<std::string, Line> lnObjBank = {};
	std::vector<Collider> colliderBank = {};

	// Renders any 
	std::unordered_map<std::string, Shape*> shpObjBank = {};

public:
	GameObjectManager();

	GameObjectManager(float horizontal, float vertical);

	// Getters & Setters.
	std::unordered_map<std::string, GameObject>& GetGameObjBank();

	std::unordered_map<std::string, Image>& GetImgObjBank();
	
	std::unordered_map<std::string, Text>& GetTxtObjBank();
	
	std::unordered_map<std::string, Triangle>& GetTriObjBank();

	std::unordered_map<std::string, Line>& GetLnObjBank();

	std::unordered_map<std::string, Shape*>& GetShpObjBank();
};