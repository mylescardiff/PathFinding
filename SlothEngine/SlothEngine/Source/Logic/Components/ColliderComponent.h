#pragma once
/** \file ColliderComponent.h */
// Created by Myles Cardiff

#include ".\IComponent.h"
#include <Utilities/Vector2f.h>
#include <Utilities/RectInt.h>
#include <Common.h>

namespace slth
{
/** \class ColliderComponent */
class ColliderComponent
	: public IComponent
{
public:
	
	/** Default Constructor */
	SLTH_API ColliderComponent();

	/** Default Destructor */
	SLTH_API ~ColliderComponent();

	/** Copy Method */
	SLTH_API virtual IComponent* Copy(Actor* pNewOwner) override { return new ColliderComponent(*this); }

	/** Ideintifier Functions */
	static constexpr Id Identifier = Hasher::Hash32("Collider");
	SLTH_API virtual const Id GetIdentifier() const override { return Identifier; }
	SLTH_API virtual const char* GetName() const override { return "Collider"; };

	/** Initialization Functions*/
	SLTH_API virtual bool Init(XmlData* xmlElement) override;



private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	Vector2f m_size;
	Vector2f m_offset;
	float m_collisionTimeout;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API Vector2f GetSize() { return m_size; }
	SLTH_API Vector2f GetOffset() { return m_offset; }
	SLTH_API RectInt GetRect();

	SLTH_API float GetTimeout() { return m_collisionTimeout; }
	SLTH_API void SetTimout(float time) { m_collisionTimeout = time; }
	SLTH_API void DecreaseTimeout(float time) { m_collisionTimeout -= time; }

};
}