// --------------------------------------------------------
// Main.cpp
// --------------------------------------------------------
#include <iostream>
#include "Logic/GameApp.h"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main()
{
	// game logic start
	GameApp app;
	if (!app.Init())
	{
		return 1;
	}
	
	app.Run();
	app.Shutdown();
	

#if _DEBUG
	//system("pause");
#endif

	return 0;


}


