#pragma once

#include <SFML/Graphics.hpp>

struct ImageResources
{
	static sf::Texture Texture; // MenuBackground
	static sf::Texture Background;
	static sf::Texture Reset;
	static sf::Texture Power;

	// HACK: this field must be last.
	static const bool FooStatic;
};