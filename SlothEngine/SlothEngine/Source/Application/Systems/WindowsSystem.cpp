//#include <sysinfoapi.h>
#include <iostream> //TESTING
#include <thread>
#include <winsock.h>
#include <windows.h>
#include <filesystem>
#include <Application/Systems/WindowsSystem.h>

namespace slth
{
	WindowsSystem::WindowsSystem()
	{
		//
	}

	WindowsSystem::~WindowsSystem()
	{
		//
	}

	void WindowsSystem::PrintSystemInfo()
	{
		float gigabyteConversion = 1073741824.f;

		// phyiscal memory, with help from: https://www.youtube.com/watch?v=71GxSJXxhtc
		MEMORYSTATUSEX memoryStatus;
		memoryStatus.dwLength = sizeof(memoryStatus);
		GlobalMemoryStatusEx(&memoryStatus);
		std::cout << "Physical Memory: " << static_cast<float>(memoryStatus.ullTotalPhys) / gigabyteConversion << " GB" << std::endl;

		// CPU cores
		std::cout << "CPU Cores: " << std::thread::hardware_concurrency() << std::endl;;

		// hard disk space, with help from: http://forums.codeguru.com/showthread.php?424302-disk-space&p=1578378#post1578378
		ULARGE_INTEGER freeBytesAvailable;
		ULARGE_INTEGER totalDiskSize;
		ULARGE_INTEGER totalFreeBytes;

		GetDiskFreeSpaceEx("c:\\", &freeBytesAvailable, &totalDiskSize, &totalFreeBytes);

		double freeGigs	= static_cast<double>(totalFreeBytes.QuadPart) / gigabyteConversion;
		double totalSizeGigs = static_cast<double>(totalDiskSize.QuadPart) / gigabyteConversion;
		std::cout << "Hard Drive: " << freeGigs << " / " << totalSizeGigs << " GB" << std::endl;

	}

	std::vector<std::string> WindowsSystem::GetFilesInFolder(std::string& path, bool recursive)
	{
		std::vector<std::string> files;
		if (recursive)
		{
			for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
			{
				files.emplace_back(entry.path().u8string());
			}
		}
		else
		{
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				files.emplace_back(entry.path().u8string());
			}
		}
		
		return files;
	}

	

};
