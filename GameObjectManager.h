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
	std::vector<GameObject*> gameObjBank = {};
	std::vector<Image> imgObjBank = {};
	std::vector<Text> txtObjBank = {};
	std::vector<Triangle> triObjBank = {};
	std::vector<Line> lnObjBank = {};
	std::vector<Collider> colliderBank = {};
	std::vector<Quad> quadObjBank = {};

	// Constructor.
	GameObjectManager();

public:
	// Don't implement.
	GameObjectManager(const GameObjectManager& obj) = delete;

	// Allow others to get a share of the object.
	static GameObjectManager* GetInstance();

	// Getters & Setters.
	std::vector<GameObject*>& GetGameObjBank();

	std::vector<Image>& GetImgObjBank();
	
	std::vector<Text>& GetTxtObjBank();
	
	std::vector<Triangle>& GetTriObjBank();

	std::vector<Line>& GetLnObjBank();

	std::vector<Quad>& GetQuadObjBank();


	// Adders.
	void AddGameObj(GameObject* inp_gameObject);

	void AddImgObj(const Image& inp_imgObj);

	void AddTxtObj(const Text& inp_txtObj);

	void AddTriObj(const Triangle& inp_triObj);

	void AddLnObj(const Line& inp_lnObj);

	void AddQuadObj(const Quad& inp_quadObj);
};