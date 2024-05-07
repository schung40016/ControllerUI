#pragma once

#include "Source/pch.h"

class Component {
public:
	// Initialize all relevant classes/objects here.
	virtual void Awake();

	// Called every frame.
	virtual void Update(float deltaTime);
};