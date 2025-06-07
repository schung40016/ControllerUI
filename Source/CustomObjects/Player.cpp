#include "pch.h"
#include "Player.h"
#include "Source/Game/GameObject.h"
#include "Source/UI_Objects/Shapes/Quad.h"
#include "Source/UI_Objects/Image.h"
#include "Source/Components/BoxCollider.h"
#include "Source/Components/PlayerController.h"
#include "Source/Components/RigidBody.h"
#include "Source/Components/Camera.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Components/AnimationController.h"

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
	std::string sCameraName = sPlayerName + "_Camera";
	std::string sAnimationControllerName = sPlayerName + "_AnimationController";

	std::unordered_map<std::string, int> states = { {"Jump", 1}, {"Run", 2}, {"Idle", 3}};

	// Try setting the objects from within the resourcemanager.
	GameObject player_gameObj = GameObject(sPlayerName, inp_position, fSizeMultiplier, { inp_width, inp_length });
	GameObject& tempPlayerGame = resourceManager->GetGameObj(sPlayerName);
	tempPlayerGame.SetScale(.1f);
	Image playerSprite = Image(sPlayerName + "_Image", DirectX::Colors::White, ".\\Images\\PlayerSpriteSheet.png", EnumData::Descriptors::PlayerImage, tempPlayerGame, .25f, .25f, .35f);
	std::vector<DirectX::SimpleMath::Vector2> playerCollisionBox = FetchPositionPairs(inp_width, inp_length);

	BoxCollider player_collider = BoxCollider(tempPlayerGame, playerCollisionBox, true);
	PlayerController player_controller = PlayerController(tempPlayerGame, resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Player][sColliderName], 100.f, 5000.f);
	RigidBody player_rigidBody = RigidBody(tempPlayerGame, 10.f, 10.f, -9.81f);
	Camera player_camera = Camera(tempPlayerGame, true);
	AnimationController player_animationController = AnimationController(tempPlayerGame, playerSprite, states);

	// Add to the game object manager.
	resourceManager->AddColliderObj(EnumData::ColliderLayers::Player, sColliderName, player_collider);
	resourceManager->AddPlayerController(sControllerName, player_controller);
	resourceManager->AddRigidBody(sRigidBodyName, player_rigidBody);
	resourceManager->AddCamera(sCameraName, player_camera);
	resourceManager->AddAnimationController(sAnimationControllerName, player_animationController);

	tempPlayerGame.SetComponents({
		&resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Player][sColliderName],
		&resourceManager->GetPlayerController(sControllerName),
		&resourceManager->GetRigidBody(sRigidBodyName),
		&resourceManager->GetCamera(sCameraName),
		&resourceManager->GetAnimationController(sAnimationControllerName)
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

std::string Player::GetPlayerName()
{
	return sPlayerName;
}