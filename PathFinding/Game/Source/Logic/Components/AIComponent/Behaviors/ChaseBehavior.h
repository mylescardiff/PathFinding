#pragma once
/** \file ChaseBehavior.h */
// Created by Myles Cardiff

#include ".\IBehavior.h"
#include <Logic/Actor.h>

/// <summary>
/// Enables this actor to chase another actor 
/// </summary>
class ChaseBehavior
	: public IBehavior
{
public:
	
	/// <summary>
	/// Explicit Constructor
	/// </summary>
	ChaseBehavior(slth::Actor* pActor, float aquireDistance);

	/// <summary>
	/// Update (Tick) function
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	virtual void Update(float deltaTime) override;

private:
	
	slth::Actor* m_pChaseTarget;
	float m_acquireDistance;

	// constants
	static constexpr float s_kPredictTurns = 100;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	void SetChaseTarget(slth::Actor* pChaseTarget) { m_pChaseTarget = pChaseTarget; }

};
