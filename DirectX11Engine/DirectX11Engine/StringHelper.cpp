#include "StringHelper.h"

std::wstring StringHelper::StringToWideString(const std::string& str)
{
	std::wstring wstr;
	wstr.assign(str.begin(), str.end());
	return wstr;
}

std::string StringHelper::GetDirectoryFromPath(const std::string& filePath)
{
	size_t offBslash = filePath.find_last_of('\\');
	size_t offSlash = filePath.find_last_of('/');
	if (offBslash == std::string::npos && offSlash == std::string::npos) {
		return "";
	}
	return filePath.substr(0, (offBslash > offSlash ? offSlash : offBslash));
}

std::string StringHelper::GetFileExtension(const std::string& fileName)
{
	size_t off = fileName.find_last_of('.');
	if (off == std::string::npos) {
		return {};
	}
	return std::string(fileName.substr(off + 1));
}
