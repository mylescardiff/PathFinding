#pragma once
/** \file IdleBehavior.h */
// Created by Myles Cardiff

#include ".\IBehavior.h"

/// <summary>
/// Enables the AI to just sit and wait where they are for a specified amount of time. 
/// </summary>
class IdleBehavior
	: public IBehavior
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	IdleBehavior(float idleTime);

	/// <summary>
	/// Default Destructor
	/// </summary>
	virtual ~IdleBehavior();

	/// <summary>
	/// Update (Tick) function for the component
	/// </summary>
	/// <param name="deltaTime">Delta (frame) time</param>
	virtual void Update(float deltaTime) override;

protected:

	float m_idleTime;

};
