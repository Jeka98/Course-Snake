#include "ImageResources.h"
#include "DirectoryHelper.h"

// fields
sf::Texture ImageResources::Texture; // MenuBackground
sf::Texture ImageResources::Background;
sf::Texture ImageResources::Reset;
sf::Texture ImageResources::Power;

// last.
const bool ImageResources::FooStatic = [] {
	Texture.loadFromFile(DirectoryHelper::GetImage("Texture1"));
	Background.loadFromFile(DirectoryHelper::GetImage("Background1"));
	Reset.loadFromFile(DirectoryHelper::GetImage("Reset"));
	Power.loadFromFile(DirectoryHelper::GetImage("Power"));
	return true;    // Note: unused dummy return value
}();