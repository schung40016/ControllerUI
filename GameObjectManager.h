#pragma once

#include "pch.h"
#include <Image.h>
#include <Text.h>
#include <Triangle.h>
#include <Shape.h>
#include <Quad.h>
#include <Line.h>
#include <unordered_map>
#include <Collider.h>

class GameObject;

class GameObjectManager {

private:
	static GameObjectManager* instance;

	// Store all objects here.
	std::unordered_map<std::string, GameObject> gameObjBank = {};
	std::unordered_map<std::string, Image> imgObjBank = {};
	std::unordered_map<std::string, Text> txtObjBank = {};
	std::unordered_map<std::string, Triangle> triObjBank = {};
	std::unordered_map<std::string, Line> lnObjBank = {};
	std::unordered_map<std::string, Quad> quadObjBank = {};

	// Constructor.
	GameObjectManager();

public:
	// Don't implement.
	GameObjectManager(const GameObjectManager& obj) = delete;

	// Allow others to get a share of the object.
	static GameObjectManager* GetInstance();

	// Getters & Setters.
	std::unordered_map<std::string, GameObject>& GetGameObjBank();

	std::unordered_map<std::string, Image>& GetImgObjBank();
	
	std::unordered_map<std::string, Text>& GetTxtObjBank();
	
	std::unordered_map<std::string, Triangle>& GetTriObjBank();

	std::unordered_map<std::string, Line>& GetLnObjBank();

	std::unordered_map<std::string, Quad>& GetQuadObjBank();

	GameObject& GetGameObj(const std::string id);

	Image& GetImgObj(const std::string id);

	Text& GetTxtObj(const std::string id);

	Triangle& GetTriObj(const std::string id);

	Line& GetLnObj(const std::string id);

	Quad& GetQuadObj(const std::string id);

	// Adders.
	void AddGameObj(std::string id, const GameObject& inp_gameObject);

	void AddImgObj(std::string id, const Image& inp_imgObj);

	void AddTxtObj(std::string id, const Text& inp_txtObj);

	void AddTriObj(std::string id, const Triangle& inp_triObj);

	void AddLnObj(std::string id, const Line& inp_lnObj);

	void AddQuadObj(std::string id, const Quad& inp_quadObj);
};