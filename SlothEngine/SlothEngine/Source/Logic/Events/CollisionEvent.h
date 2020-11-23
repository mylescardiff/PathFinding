#pragma once
/** \file CollisionEvent.h */

// Created by Myles Cardiff

#include ".\IEvent.h"

//! \namespace Sloth Engine
namespace slth
{
/** \class CollisionEvent */
/** Fires when two actors collide */
class CollisionEvent
	: public IEvent
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	CollisionEvent();

	/** Default Destructor */
	~CollisionEvent();

	/** Ideintifier Functions */
	virtual EventType GetType() override { return 2; };
	virtual const char* GetName() const override { return "Collision"; }

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