#pragma once
/** \file TextureResource.h */

// Created by Myles Cardiff

#include ".\IResource.h"

//! \namespace Sloth Engine
namespace slth
{
/** \class TextureResource */
/** Holds a texture file (image) */
class TextureResource
	: public IResource
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	TextureResource();

	/** Default Destructor */
	~TextureResource();


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