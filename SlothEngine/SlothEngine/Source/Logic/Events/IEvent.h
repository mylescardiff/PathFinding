#pragma once
/** \file IEvent.h */

// Created by Myles Cardiff

#include <Common.h>
#include <functional>

//! \namespace Sloth Engine
namespace slth
{
/** \class IEvent */
/** Base class for all engine and game logic */
class IEvent
{
public:

	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	SLTH_API IEvent();

	/** Default Destructor */
	SLTH_API virtual ~IEvent();

	SLTH_API virtual EventType GetType() = 0;
	SLTH_API virtual const char* GetName() const = 0;

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