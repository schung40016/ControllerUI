#pragma once

#include "pch.h"
#include "Component.h"

class SpriteManager;

// Responsible for taking in a state and animating image. 

class GameObject;

class AnimationController : public Component {
private:
	std::shared_ptr<class GameObject> parentObj = nullptr;			// Reference to parent object, just in case.
	class Image* image = nullptr;									// Reference to image object, pass in sprites here.
	SpriteManager* spriteManager = nullptr;							
	std::string currentSpriteSetName = "";								// Current series of frames we want to animate.
	bool newSpriteSet = false;
	int currentFrame = 0;
	float animationTimer = 0.f;
	float frameDuration = 0.1f;										// Determines how often to update frame.

public:
	AnimationController();

	AnimationController(GameObject& inp_parentObj, Image& inp_img);

	void Awake() override;

	void Update(float deltaTime) override;

	void Animate(float deltaTime);

	void SetAnimation(std::string spriteName);
};

// Movement system should send states to the animation manager, and animation manager should handle appropriately.
// Movements should have their own states: run, falling, jumping. 