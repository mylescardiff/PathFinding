#pragma once
/** \file AIComponent.h */
// Created by Myles Cardiff

#include <Logic/Components/IComponent.h>
#include <vector>
#include <Utilities/Vector2f.h>
#include <Logic/Components/AIComponent/Behaviors/IBehavior.h>

/// <summary>
/// Adds some AI functionality to the actor
/// </summary>
class AIComponent
	: public slth::IComponent
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	/// <summary>
	/// Complie-time unique ID (int) for the component type
	/// </summary>
	static constexpr Id Identifier = slth::Hasher::Hash32("AI");

	/// <summary>
	/// Get the unique identifier for this component
	/// </summary>
	/// <returns>Unsigned int unique ID</returns>
	virtual const Id GetIdentifier() const override { return Identifier; }

	/// <summary>
	/// Get the name of this component
	/// </summary>
	/// <returns>String unique name</returns>
	virtual const char* GetName() const override { return "AI"; };

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	AIComponent();

	/// <summary>
	/// Default Destructor. Deletes the pointer to next behavior (if any).
	/// </summary>
	virtual ~AIComponent();

	/// <summary>
	/// Creates a copy of the transform component
	/// </summary>
	/// <param name="pNewOwner">The new owning actor of this component</param>
	/// <returns>A pointer to the new copy</returns>
	virtual IComponent* Copy(slth::Actor* pNewOwner) override;

	/// <summary>
	/// Initilizes the transform component from XML node (see /data/actors.xml for syntax)
	/// </summary>
	/// <param name="xmlElement">The tinyxml node pointer contianing the data</param>
	/// <returns></returns>
	virtual bool Init(XmlData* xmlElement) override;

	/// <summary>
	/// Updates the transform and velocity based on info from the AI's logic
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	void Update(float deltaTime);

	/// <summary>
	/// Persue another actor
	/// </summary>
	/// <param name="target"></param>
	void Chase(slth::Actor* target, float aquireDistance);

	/// <summary>
	/// Set the behavior, will begin executing immediatley. To set sequences of 
	/// behaviors, see IBehavior::ChainBehavior()
	/// </summary>
	/// <param name="pBehavior">A constructured pointer to the new behavior</param>
	/// <returns>A pointer to the new behavior. This is returned so that multiple 
	/// actions can be chained to execte one after the other</returns>
	IBehavior* SetBehavior(IBehavior* pBehavior);

	static constexpr float kSlowRadius = 50.f;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	IBehavior* m_pCurrentBehavior;

public:

	IBehavior* CurrentBehavior() { return m_pCurrentBehavior; }
	
};
