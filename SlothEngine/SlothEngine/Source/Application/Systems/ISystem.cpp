#include <Application/Systems/ISystem.h>
#include <Application/Systems/WindowsSystem.h>

using slth::ISystem;

ISystem::ISystem()
{
	
}

ISystem::~ISystem()
{
	
}


ISystem* slth::ISystem::Create()
{
#ifdef _WIN32
	return new WindowsSystem;
#else
	std::cout << "This operating system is not supported" << std::endl;
#endif
	
	return nullptr;
}
