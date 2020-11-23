#pragma once
/** \file WindowsSystem.h */

// Created by Billy Graban

#include <Application/Systems/ISystem.h>
#include <Application/Window/IWindow.h>

//! \namespace Engine Contains all Engine code
namespace slth
{
/** \class WindowsSystem */

class WindowsSystem
	: public ISystem
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	SLTH_API WindowsSystem();

	/** Default Destructor */
	SLTH_API ~WindowsSystem();

	/** Returns the type of system e.g. "Windows" */
	SLTH_API virtual const char* GetSystemName() const override { return "Windows";  }

	/** Prints data gleaned from the OS like memory, HD space, and # of cores */
	SLTH_API virtual void PrintSystemInfo();

	/** Lists the files in a folder on disk*/
	SLTH_API virtual std::vector<std::string> GetFilesInFolder(std::string& path, bool recursive);

	

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