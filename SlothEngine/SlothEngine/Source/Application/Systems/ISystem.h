#pragma once

/** \file ISystem.h */

// Created by Myles Cardiff

#include <Common.h>
#include <Application/Window/IWindow.h>
#include <Application/Systems/ISystem.h>

#include <memory>


//! \namespace Engine Contains all Engine code
namespace slth
{
/** \class ISystem */

class ISystem
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	SLTH_API ISystem();

	/** Default Destructor */
	SLTH_API virtual ~ISystem();

	/** Returns name for logging purposes */
	SLTH_API virtual const char* GetSystemName() const = 0;

	/** Prints data gleaned from the OS like memory, HD space, and # of cores */
	SLTH_API virtual void PrintSystemInfo() = 0;

	/** Lists the files in a folder on disk*/
	SLTH_API virtual std::vector<std::string> GetFilesInFolder(std::string& path, bool recursive) = 0;

	/** Creates a new system */
	SLTH_API static ISystem* Create();

	
private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}