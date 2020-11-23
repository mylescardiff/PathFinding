#pragma once
/** \file TriggerComponent.h */
// Created by Myles Cardiff

#include ".\IComponent.h"

namespace slth
{
/// <summary>
/// </summary>
class TriggerComponent
	: public IComponent
{
public:

	/// <summary>
	/// Default Constructor
	/// </summary>
	SLTH_API TriggerComponent();
	
	/// /// <summary>
	/// Creates a copy of this component
	/// </summary>
	/// <param name="pNewOwner"></param>
	/// <returns></returns>
	slth::IComponent* Copy(slth::Actor* pNewOwner);

	/// <summary>
	/// Complie-time unique ID (int) for the component type
	/// </summary>
	SLTH_API static constexpr Id Identifier = Hasher::Hash32("Trigger");

	/// <summary>
	/// Get the unique identifier for this component
	/// </summary>
	/// <returns>Unsigned int unique ID</returns>
	SLTH_API virtual const Id GetIdentifier() const override { return Identifier; }

	/// <summary>
	/// Get the name of this component
	/// </summary>
	/// <returns>String unique name</returns>
	SLTH_API virtual const char* GetName() const override { return "Trigger"; };
	
	/// <summary>
	/// Initilizes the transform component from XML node (see /data/actors.xml for syntax)
	/// </summary>
	/// <param name="xmlElement">The tinyxml node pointer contianing the data</param>
	/// <returns></returns>
	SLTH_API virtual bool Init(XmlData* xmlElement) override;

private:
	
	float m_radius;
	std::string m_tag;
	bool m_active;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API const float GetRadius() const { return m_radius; }
	SLTH_API const std::string& GetTag() const { return m_tag; }
	SLTH_API const bool IsActive() const { return m_active; }
	SLTH_API void SetActive(bool active) { m_active = active; }


};
}