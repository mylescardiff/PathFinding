#pragma once
/** \file IBehavior.h */
// Created by Myles Cardiff
#include <Logic/Components/TransformComponent.h>

class AIComponent;

/// <summary>
/// Base class for all AI behaviors
/// </summary>
class IBehavior
{
public:

	/// <summary>
	/// Initialize the behavior
	/// </summary>
	/// <param name="pOwner">A pointer to the AIComponent this behavior is assigned to</param>
	virtual void Init(AIComponent* pOwner);

	/// <summary>
	/// Base Update (tick) function for behaviors
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void Update(float deltaTime);

	/// <summary>
	///  Chain another behavior to run after the current one
	/// </summary>
	/// <param name="nextBehavior"></param>
	/// <returns>A pointer to the next behavior</returns>
	IBehavior* ChainBehavior(IBehavior* nextBehavior);

	/// <summary>
	/// Move to the next behavior, if one is specified
	/// </summary>
	void NextBehavior();

protected:
	
	slth::TransformComponent* m_pTransform;
	AIComponent* m_pOwner;
	IBehavior* m_pNextBehavior;

};
