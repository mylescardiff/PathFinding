#pragma once
/** \file ITexture.h */

// Created by Myles Cardiff

#include <Application/Window/IWindow.h>

//! \namespace Sloth Engine
namespace slth
{
/** \class ITexture */
/** Base interface for all textures */
	class ITexture
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	ITexture();

	/** Default Destructor */
	~ITexture();

	/** Gets the underlying pointer of whatever texutre type we're using (SDL, SFML, etc) */
	virtual void* GetNativeTexture() = 0;
	virtual bool Init( void*) = 0; 

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