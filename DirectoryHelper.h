#pragma once

#include <string>

class DirectoryHelper
{
public:
	static std::string ResolvePath(const std::string& relativePath);

	static std::string GetFont(const std::string& fontName);
	static std::string GetImage(const std::string& imageName);
	static std::string GetSound(const std::string& soundName);
};