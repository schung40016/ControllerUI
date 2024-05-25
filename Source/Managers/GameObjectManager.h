#pragma once

#include "pch.h"
#include "Source/UI_Objects/Image.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Shapes/Triangle.h"
#include "Source/UI_Objects/Shapes/Shape.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/UI_Objects/Line.h"
#include "unordered_map"
#include "Source/Components/BoxCollider.h"
#include "Source/Enum/EnumData.h"
#include "Source/Components/PlayerController.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/ControllerUI.h"

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

	// Components.
	std::unordered_map<std::string, PlayerController> controllerBank = {};
	std::unordered_map<std::string, RigidBody> rigidBodyBank = {};
	std::unordered_map<std::string, ControllerUI> controllerUIBank = {};
	std::unordered_map<int, std::unordered_map<std::string, BoxCollider>> colliderObjBank = {};
	std::vector<std::pair<int, int>> colliderPairs = {};

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

	std::unordered_map<int, std::unordered_map<std::string, BoxCollider>>& GetColliderObjBank();

	std::vector<std::pair<int, int>>& GetColliderLayerPairs();

	GameObject& GetGameObj(const std::string id);

	Image& GetImgObj(const std::string id);

	Text& GetTxtObj(const std::string id);

	Triangle& GetTriObj(const std::string id);

	Line& GetLnObj(const std::string id);

	Quad& GetQuadObj(const std::string id);

	PlayerController& GetPlayerController(const std::string id);

	RigidBody& GetRigidBody(const std::string id);

	ControllerUI& GetControllerUI(const std::string id);

	// Adders.
	void AddGameObj(std::string id, const GameObject& inp_gameObject);

	void AddImgObj(std::string id, const Image& inp_imgObj);

	void AddTxtObj(std::string id, const Text& inp_txtObj);

	void AddTriObj(std::string id, const Triangle& inp_triObj);

	void AddLnObj(std::string id, const Line& inp_lnObj);

	void AddQuadObj(std::string id, const Quad& inp_quadObj);

	void AddColliderLayerPair(std::pair<int, int>& inp_pair);

	void AddColliderObj(int id, std::string objId, const BoxCollider& inp_colliderObj);

	void AddPlayerController(std::string id, const PlayerController& inp_playerController);

	void AddRigidBody(std::string id, const RigidBody& inp_rigidBody);

	void AddControllerUI(std::string id, const ControllerUI& inp_controllerUI);

	// Destructor
	~GameObjectManager();
};