#pragma once

#include <SFML/Graphics.hpp>
#include "ImageResources.h"

struct Resources
{
	static ImageResources Images;

	static sf::Font Font;

	// HACK: this field must be last.
	static const bool FooStatic;
};