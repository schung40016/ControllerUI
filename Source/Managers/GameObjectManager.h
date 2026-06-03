#pragma once

#include "pch.h"
#include "unordered_map"
#include "Source/Components/BoxCollider.h"
#include "Source/UI_Objects/Line.h"
#include "Source/CustomObjects/Box.h"
#include "any"
#include "typeinfo"
#include "typeindex"

class GameObject;
class Image;
class Text;
class Triangle;
class Line;
class Quad;
class PlayerController;
class RigidBody;
class ControllerUI;
class DebuggerUI;
class Camera;
class BoxCollider;
class SpriteManager;
class AnimationController;

class GameObjectManager {

private:
	static GameObjectManager* instance;

	// Generic bank.
	std::unordered_map<std::type_index, std::any> banks;

	// Banks for specific object types.
	std::unordered_map<int, std::unordered_map<std::string, BoxCollider>> colliderObjBank = {};
	std::vector<std::pair<int, int>> colliderPairs = {};

	// Constructor.
	GameObjectManager();

public:
	// Don't implement.
	GameObjectManager(const GameObjectManager& obj) = delete;
	GameObjectManager& operator=(const GameObjectManager& obj) = delete;

	// Allow others to get a share of the object.
	static GameObjectManager* GetInstance();

	// Getters & Setters.
	
	/// <summary>
	/// Retrieves the bank of specified type.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename T>
	std::unordered_map<std::string, T>& GetBank()
	{
		auto key = std::type_index(typeid(T));
		auto it = banks.find(key);
		if (it == banks.end())
		{
			banks.emplace(key, std::unordered_map<std::string, T>{});
			it = banks.find(key);
		}

		return std::any_cast<std::unordered_map<std::string, T>&>(it->second);
	}

	/// <summary>
	/// Adds a item into the bank of specified type.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="id"></param>
	/// <param name="obj"></param>
	template<typename T>
	void Add(const std::string& id, const T& obj)
	{
		GetBank<T>()[id] = obj;
	}

	/// <summary>
	/// Retrieves item from the bank of specified type by id.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="id"></param>
	/// <returns></returns>
	template<typename T>
	T& Get(const std::string& id)
	{
		return GetBank<T>()[id];
	}

	/// <summary>
	/// Checks if the bank of specified type contains an item with the given id.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="id"></param>
	/// <returns></returns>
	template<typename T>
	bool Has(const std::string& id) const
	{
		auto key = std::type_index(typeid(T));
		auto it = banks.find(key);
		if (it != banks.end())
		{
			return false;
		}

		const std::any& a = it->second;
		const std::any& a = it->second;

		if (std::any_cast<const std::unordered_map<std::string, T>>(&a) == nullptr)
		{
			return false;
		}

		const auto& bank = std::any_cast<const std::unordered_map<std::string, T>&>(a);
		return bank.find(id) != bank.end();
	}

	// Getters & setters for specific banks.
	std::unordered_map<int, std::unordered_map<std::string, BoxCollider>>& GetColliderObjBank();
	std::vector<std::pair<int, int>>& GetColliderLayerPairs();

	void AddColliderLayerPair(const std::pair<int, int>& inp_pair);
	void AddColliderObj(int id, const std::string& objId, const BoxCollider& inp_colliderObj);

	// Destructor
	~GameObjectManager();
};