#pragma once
/** \file TurnBehavior.h */
// Created by Myles Cardiff

#include ".\IBehavior.h"

/// <summary>
/// Enables the AI to rotate to a new heading. Note: UP is zero rotation. 
/// </summary>
class TurnBehavior
	: public IBehavior
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	TurnBehavior(float angle);

	/// <summary>
	/// Default Destructor
	/// </summary>
	virtual ~TurnBehavior();

	/// <summary>
	/// Update (Tick) function
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	virtual void Update(float deltaTime) override;

protected:

	float m_angle;

};
