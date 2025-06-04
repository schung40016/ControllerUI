#include "pch.h"
#include "AnimationController.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/UI_Objects/Image.h"
#include "Source/Managers/SpriteManager.h"

AnimationController::AnimationController()
{
}

AnimationController::AnimationController(GameObject& inp_parentObj, Image& inp_img, std::unordered_map<std::string, int> inp_states)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
	image = &inp_img;
	states = inp_states;
}

void AnimationController::Awake()
{
	GameObjectManager* resourceManager = GameObjectManager::GetInstance();
	image = &resourceManager->GetImgObj(parentObj->GetName() + "_Image");
	spriteManager = &resourceManager->GetSpriteManager(parentObj->GetName() + "_SpriteManager");
}

void AnimationController::Update(float deltaTime)
{
	UpdateAnimation();
	Animate(deltaTime);
}

void AnimationController::Animate(float deltaTime)
{
	std::vector<Sprite> currentSpriteSet = spriteManager->GetSpriteSet(currentSpriteName);

	if (newSpriteSet)
	{
		// New sprite set, reset data.
		currentFrame = 0;
		animationTimer = 0;
		newSpriteSet = false;
	}
	else
	{
		animationTimer += deltaTime;

		if (animationTimer >= frameDuration)
		{
			// Reset animationTimer.
			animationTimer -= frameDuration;
			currentFrame = (currentFrame + 1) % currentSpriteSet.size();
		}
	}

	image->SetSpriteRender(currentSpriteSet[currentFrame].origin, currentSpriteSet[currentFrame].sourceRect);
}

// Adds to animation stack.
void AnimationController::AddAnimation(std::string spriteName)
{
	spritesToAnimate.emplace_back(spriteName);
}

void AnimationController::UpdateAnimation()
{
	std::pair<std::string, int> currentSpritePair = {};

	for (int i = 0; i < spritesToAnimate.size(); i++)
	{
		// Assign/Reassign if currentSprite is either null or has a lower priority than current sprite.
		if (currentSpritePair == std::make_pair(std::string(), 0) || states[spritesToAnimate[i]] < currentSpritePair.second)
		{
			currentSpritePair = { spritesToAnimate[i], states[spritesToAnimate[i]] };
		}
	}

	if (currentSpriteName != currentSpritePair.first)
	{
		newSpriteSet = true;
	}

	currentSpriteName = currentSpritePair.first;
	spritesToAnimate = {};
}

// Controller should pass the state itself. ANimationController should have a movement update function. Elevator state machine project (for reference).
// Two ways to stow map data: slow-JSON, fast-binary blob (do not try right now).
// Get JSON parser library to read map data. 


/*
Fix animation controller.
Fix gravity floaty.
Create map manager.
*/