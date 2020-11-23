#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#if _LOG_CONSOLE
#include <iostream>
#ifdef _WIN32
// this is windows specific so don't bother loading if it's not present
#include <windows.h>
#include <lua.hpp>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

#endif
using slth::Logger;

void slth::Logger::LogSimple(const std::string& message)
{
	std::cout << message << std::endl;
}

void slth::Logger::Log(const std::string & message)
{
#if _DEBUG
	
	// get timestamp
	std::string timeStamp = GetTimestamp();
	
#if _LOG_CONSOLE
	std::cout << timeStamp << " " << message << std::endl;

#if _LOG_FILE
	
	// write the line
	std::ofstream outFile;
	outFile.open("..\\Logs\\" + timeStamp + "-log.txt", std::ios_base::app);
	std::ostream& os = outFile;

	outFile << timeStamp << " " << type << message << std::endl;
	outFile.close();
	
	
#endif

#endif
	
#ifdef _WIN32
	// set this back to white, no matter what because if we've got here, then it's likely something changed it
	SetConsoleTextAttribute(hConsole, 15);
#endif
	
#endif
}

std::string slth::Logger::GetTimestamp()
{
	// this basic code structure was borrowed from: https://stackoverflow.com/questions/15957805/extract-year-month-day-etc-from-stdchronotime-point-in-c
	typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type> days;
	
	// get the current time
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// convert to local time
	time_t tt = std::chrono::system_clock::to_time_t(now);
	tm local_tm = *localtime(&tt);

	// print the date in YYYYMMDD-HHMMSS format
	char tempDateString[20];
	sprintf(tempDateString, "%04d%02d%02d-%02d%02d%02d", local_tm.tm_year + 1900, local_tm.tm_mon + 1, local_tm.tm_mday, local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec);
	return tempDateString;
}

void slth::Logger::LogInfo(const std::string& message)
{
#if _LOG_SEVERITY >= 2 
#ifdef _WIN32
	SetConsoleTextAttribute(hConsole, 10);
#endif
	Log(message);
#endif
}

void slth::Logger::LogWarning(const std::string& message)
{
#if _LOG_SEVERITY
#ifdef _WIN32
	SetConsoleTextAttribute(hConsole, 14);
#endif
	Log(message);
#endif
}

void slth::Logger::LogError(const std::string& message)
{
#ifdef _WIN32
	SetConsoleTextAttribute(hConsole, 12);
#endif
	Log(message);
}

void slth::Logger::LogLua(const std::string& message)
{
#ifdef _WIN32
	SetConsoleTextAttribute(hConsole, 14);
#endif
	Log(message);
}

int glua::Logger_Log(lua_State * pState)
{
	const char* message = lua_tostring(pState, -1);
	if (message)
	{
		_LOGL(message); 
	}
	return 0;
}
