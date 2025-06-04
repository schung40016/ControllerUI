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
	std::string currentSpriteName = {};								// Current series of frames we want to animate.
	bool newSpriteSet = false;
	int currentFrame = 0;
	float animationTimer = 0.f;
	float frameDuration = 0.1f;										// Determines how often to update frame.
	std::vector<std::string> spritesToAnimate = {};					// Holds a list of all sprites we should animate.
	std::unordered_map<std::string, int> states = {};				// Holds states along with their priority number.


public:
	AnimationController();

	AnimationController(GameObject& inp_parentObj, Image& inp_img, std::unordered_map<std::string, int> inp_states);

	void Awake() override;

	void Update(float deltaTime) override;

	void Animate(float deltaTime);

	void AddAnimation(std::string spriteName);

	void UpdateAnimation();
};

// Movement system should send states to the animation manager, and animation manager should handle appropriately.
// Movements should have their own states: run, falling, jumping. 