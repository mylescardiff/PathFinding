#pragma once
/** \file TeleportBehavior.h */
// Created by Myles Cardiff

#include ".\IBehavior.h"

/// <summary>
/// Enables teleporting the actor from one position & rotation to another instantly
/// </summary>
class TeleportBehavior
	: public IBehavior
{
public:
		
	/// <summary>
	/// Explicit Constructor
	/// </summary>
	TeleportBehavior(slth::Vector2f position, float rotation);
	   
	/// <summary>
	/// Update (Tick) function for the component
	/// </summary>
	/// <param name="deltaTime">Delta (frame) time</param>
	virtual void Update(float deltaTime) override;

private:
	
	slth::Vector2f m_position;
	float m_rotation;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
