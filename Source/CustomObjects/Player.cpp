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
}

Player::Player(float inp_size,
	std::string inp_playerName,
	DirectX::SimpleMath::Vector2 inp_position,
	float inp_width,
	float inp_length)
{
	GameObjectManager* resourceManager = GameObjectManager::GetInstance();
	sPlayerName = inp_playerName;
	fSizeMultiplier = inp_size;

	std::string sColliderName = sPlayerName + "_Collider";
	std::string sControllerName = sPlayerName + "_Controller";
	std::string sRigidBodyName = sPlayerName + "_RigidBody";
	std::string sCameraName = sPlayerName + "_Camera";
	std::string sAnimationControllerName = sPlayerName + "_AnimationController";
	std::string sImageName = sPlayerName + "_Image";

	std::unordered_map<std::string, int> states = { {"Jump", 1}, {"Run", 2}, {"Idle", 3} };

	// Create and store the GameObject first so components can reference it.
	GameObject player_gameObj = GameObject(sPlayerName, inp_position, fSizeMultiplier, { inp_width, inp_length });
	resourceManager->Add<GameObject>(sPlayerName, player_gameObj);

	GameObject& tempPlayerGame = resourceManager->Get<GameObject>(sPlayerName);
	tempPlayerGame.SetScale(.1f);

	Image playerSprite = Image(sImageName, DirectX::Colors::White, ".\\Images\\PlayerSpriteSheet.png", EnumData::Descriptors::PlayerImage, tempPlayerGame, .25f, .25f, .35f, false);
	resourceManager->Add<Image>(sImageName, playerSprite);

	// Create collider, store it, then create controller using the stored collider.
	std::vector<DirectX::SimpleMath::Vector2> playerCollisionBox = FetchPositionPairs(inp_width, inp_length);
	BoxCollider player_collider = BoxCollider(tempPlayerGame, playerCollisionBox, true);
	resourceManager->AddColliderObj(EnumData::ColliderLayers::Player, sColliderName, player_collider);

	PlayerController player_controller = PlayerController(tempPlayerGame, resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Player][sColliderName], 100.f, 5000.f);
	resourceManager->Add<PlayerController>(sControllerName, player_controller);

	RigidBody player_rigidBody = RigidBody(tempPlayerGame, true, 10.f, -9.81f);
	resourceManager->Add<RigidBody>(sRigidBodyName, player_rigidBody);

	Camera player_camera = Camera(tempPlayerGame, true);
	resourceManager->Add<Camera>(sCameraName, player_camera);

	AnimationController player_animationController = AnimationController(tempPlayerGame, playerSprite, states);
	resourceManager->Add<AnimationController>(sAnimationControllerName, player_animationController);
	
	// Wire components into the GameObject by fetching them from the manager.
	tempPlayerGame.SetComponents({
		&resourceManager->GetColliderObjBank()[EnumData::ColliderLayers::Player][sColliderName],
		&resourceManager->Get<PlayerController>(sControllerName),
		&resourceManager->Get<RigidBody>(sRigidBodyName),
		&resourceManager->Get<Camera>(sCameraName),
		&resourceManager->Get<AnimationController>(sAnimationControllerName)
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