#pragma once
#include "pch.h"
#include "string"

namespace DefaultValues
{
	// String constants
	inline const std::string DEFAULT_NAME = "Default";

	// Value constants
	inline const float DEFAULT_SIZE = 975.f;
	inline const float Y_OFFSET = 975.f;

	// Render depth (z-order) constants.
	// Following Unity's convention, LOWER z renders on TOP of higher z.
	inline const float Z_DEFAULT = 0.f;
	inline const float Z_GUI = -100.f;
}