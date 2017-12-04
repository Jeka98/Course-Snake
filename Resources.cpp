#include "Resources.h"
#include "DirectoryHelper.h"

// repeat fields
ImageResources Resources::Images;
sf::Font Resources::Font;

// last.
const bool Resources::FooStatic = [] {
	Font.loadFromFile(DirectoryHelper::GetFont("arial"));
	return true;    // Note: unused dummy return value
}();