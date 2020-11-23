#pragma once
/** \file SpeakBehavior.h */
// Created by Myles Cardiff

#include ".\IBehavior.h"

/// <summary>
/// Enables the actor to print text on the screen for a specified number of seconds. 
/// </summary>
class SpeakBehavior
	: public IBehavior
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	SpeakBehavior(const char* text, float duration);

	/// <summary>
	/// Default Destructor
	/// </summary>
	virtual ~SpeakBehavior();

	/// <summary>
	/// Update (Tick) function
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	virtual void Update(float deltaTime) override;

protected:
	
	const char* m_text;
	float m_duration;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
