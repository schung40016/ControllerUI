#pragma once

#include "pch.h"
#include "Player.h"

Player::Player()
{
	resourceManager = GameObjectManager::GetInstance();
}

Player::Player(float inp_size, std::string inp_playerName, DirectX::SimpleMath::Vector2 inp_position, float inp_width, float inp_length)
{
	resourceManager = GameObjectManager::GetInstance();
	sPlayerName = inp_playerName;
	fSizeMultiplier = inp_size;

	std::string sColliderName = sPlayerName + "_Collider";
	std::string sControllerName = sPlayerName + "_Controller";
	std::string sRigidBodyName = sPlayerName + "_RigidBody";

	// Try setting the objects from within the resourcemanager.
	GameObject player_gameObj = GameObject(sPlayerName, inp_position, fSizeMultiplier);
	GameObject& tempPlayerGame = resourceManager->GetGameObj(sPlayerName);
	Quad player_shape = Quad(sPlayerName + "_Shape", DirectX::Colors::Aqua, tempPlayerGame, 1.f, 0, 0, inp_width, inp_length, true);
	std::vector<DirectX::SimpleMath::Vector2> playerCollisionBox = FetchPositionPairs(inp_width, inp_length);

	BoxCollider player_collider = BoxCollider(tempPlayerGame, playerCollisionBox, true);
	PlayerController player_controller = PlayerController(tempPlayerGame, resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Player][sColliderName]);
	RigidBody player_rigidBody = RigidBody(tempPlayerGame, 10.f);

	// Add to the game object manager.
	resourceManager->AddColliderObj(EnumData::ColliderLayers::Player, sColliderName, player_collider);
	resourceManager->AddPlayerController(sControllerName, player_controller);
	resourceManager->AddRigidBody(sRigidBodyName, player_rigidBody);

	tempPlayerGame.SetComponents({
		&resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Player][sColliderName],
		&resourceManager->GetPlayerController(sControllerName),
		&resourceManager->GetRigidBody(sRigidBodyName),
	});
}

std::vector<DirectX::SimpleMath::Vector2> Player::FetchPositionPairs(const float inp_width, const float inp_length)
{
	std::vector<DirectX::SimpleMath::Vector2> quadrants = { {-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f} };
	std::vector<DirectX::SimpleMath::Vector2> results = {};

	for (DirectX::SimpleMath::Vector2 pair : quadrants)
	{
		results.push_back({pair.x * inp_width, pair.y * inp_length});
	}

	return results;
}