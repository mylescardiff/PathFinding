#pragma once
/** \file Logger.h */
/** Logger Header File */
// Created by Myles Cardiff

#include "..\Common.h"
#include <string>
#include <vector>

struct lua_State;

//! \namespace Glua
namespace glua
{
	// these need to be unique namesS
	SLTH_API int Logger_Log(lua_State* pState);
}

//! \namespace Sloth
namespace slth
{


// macros for easier typing of the various log functions



#if defined(DEBUG) || defined(SLTH_DEV)
#define _LOGS(message) slth::Logger::LogSimple(message)
#define _LOG(message) slth::Logger::Log(message)
#define _LOGI(message) slth::Logger::LogInfo(message)
#define _LOGW(message) slth::Logger::LogWarning(message)
#define _LOGE(message) slth::Logger::LogError(message)
#define _LOGL(message) slth::Logger::LogLua(message)
#else
#define _LOG(message) 
#define _LOGS(message) 
#define _LOGI(message) 
#define _LOGW(message) 
#define _LOGE(message)
#define _LOGL(message)
#endif
// log options
#define _LOG_SEVERITY 2 // 0 = Errors Only, 1 = Include Warnings, 2 = Include Info
#define _LOG_CONSOLE 1 // true / false
#define _LOG_FILE 0 // true / false

/** \class Logger */
/** Allows logging of engine information, warnings, errors to file */
class Logger 
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	
	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	
	SLTH_API static void LogSimple(const std::string& message);
	GLUA()
	SLTH_API static void Log(const std::string& message);
	
	// colored log functions
	GLUA()
	SLTH_API static void LogInfo(const std::string& message);
	SLTH_API static void LogWarning(const std::string& message);
	SLTH_API static void LogError(const std::string& message);

	SLTH_API static void LogLua(const std::string & message);
	
private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //
	static std::string GetTimestamp();

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}