#pragma once
/** \file IComponent.h */

// Created by Myles Cardiff

#include <Common.h>
#include <Utilities/Hasher.h>

struct lua_State;

//! \namespace Sloth Engine
namespace slth
{

	class Actor;

/** \class IComponent */
/** Base interface for all components */
class IComponent
{
public:

	/// <summary>
	/// Default Destructor
	/// </summary>
	SLTH_API virtual ~IComponent() = default;

	/// <summary>
	/// Copy Method. This is here because copying a component without
	/// immediatley assigning the new owning Actor was problematic. 
	/// </summary>
	/// <param name="pNewOwner"></param>
	/// <returns></returns>
	SLTH_API virtual IComponent* Copy(Actor* pNewOwner) = 0;

	/// <summary>
	/// Each component needs a unique ID. That ID is used as the hash for the 
	/// list of components. Typcially this is the hashed string name of the 
	/// using a the compile-time hasher Hasher::Hash32("Whatever")
	/// </summary>
	/// <returns>the ID value</returns>
	SLTH_API virtual const Id GetIdentifier() const = 0;
	SLTH_API virtual const char* GetName() const = 0;

	/** Initialization Functions*/
	SLTH_API virtual bool Init(XmlData* xmlElement) = 0;
	SLTH_API virtual bool PostInit() { return true; };
	
	/** Register necessary functions for use in Lua */
	SLTH_API virtual void RegisterWithLua(lua_State* pLuaState, const char* name); 

	SLTH_API virtual void Update(float deltaTime) {}

protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	Actor* m_pOwner;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
	
	SLTH_API Actor* GetOwner() { return m_pOwner;  }
	SLTH_API void SetOwner(Actor* pOwner) { m_pOwner = pOwner; }

};
}