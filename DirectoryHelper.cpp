#include "DirectoryHelper.h"
#include <Windows.h>

using namespace std;

string DirectoryHelper::ResolvePath(const string& relativePath)
{
	const int bufferSize = 256;
	char executablePath[bufferSize];
	GetModuleFileName(nullptr, executablePath, bufferSize);

	std::string parentDirectory = executablePath;
	parentDirectory = parentDirectory.substr(0, parentDirectory.find_last_of("/\\"));

	return parentDirectory + '\\' + relativePath;
}

string DirectoryHelper::GetFont(const string& fontName)
{
	return ResolvePath("fonts/" + fontName + ".ttf");
}

string DirectoryHelper::GetImage(const string& imageName)
{
	return ResolvePath("images/" + imageName + ".png");
}

string DirectoryHelper::GetSound(const string& soundName)
{
	return ResolvePath("sounds/" + soundName + ".ogg");
}