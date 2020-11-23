#include "FileUtil.h"
#include <fstream>
#include <iostream>
#include <filesystem>

using slth::FileUtil;

void slth::FileUtil::CreateFolder(const std::string& path)
{
	std::filesystem::create_directories(path);
}

// read the contents of a folder (C++ 17)
void slth::FileUtil::ReadFolder(const std::string& path)
{
	for (auto& i : std::filesystem::recursive_directory_iterator(path))
		std::cout << i.path() << std::endl;

}
