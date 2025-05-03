#include "pch.h"
#include "AnimationController.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/UI_Objects/Image.h"
#include "Source/Managers/SpriteManager.h"

AnimationController::AnimationController()
{
}

AnimationController::AnimationController(GameObject& inp_parentObj, Image& inp_img)
{
	parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
	image = &inp_img;
}

void AnimationController::Awake()
{
	GameObjectManager* resourceManager = GameObjectManager::GetInstance();
	image = &resourceManager->GetImgObj(parentObj->GetName() + "_Image");
	spriteManager = &resourceManager->GetSpriteManager(parentObj->GetName() + "_SpriteManager");
}

void AnimationController::Update(float deltaTime)
{
	Animate(deltaTime);
}

void AnimationController::Animate(float deltaTime)
{
	std::vector<Sprite> currentSpriteSet = spriteManager->GetSpriteSet(currentSpriteSetName);

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

// Set animation cells.
void AnimationController::SetAnimation(std::string spriteName)
{
	if (currentSpriteSetName != spriteName)
	{
		newSpriteSet = true;
	}

	currentSpriteSetName = spriteName;
}
