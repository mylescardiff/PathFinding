#pragma once
/** \file IResource.h */
// Created by Myles Cardiff
#include <Common.h>


//! \namespace Sloth Engine
namespace slth
{
/** \class IResource */
/** Base Class for all resource types */
class IResource
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/** Default Constructor */
	SLTH_API IResource();

	/** Default Destructor */
	SLTH_API ~IResource();

	/** Create from raw data */
	SLTH_API virtual IResource* Create(char* data) = 0;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	std::string m_path;
	size_t size;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}