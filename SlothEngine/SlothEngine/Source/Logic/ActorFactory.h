#pragma once
/** \file ActorFactory.h */
// Created by Myles Cardiff

#include <memory>
#include <functional>
#include <Logic/Components/IComponent.h>
#include <Logic/Actor.h>
#include <Common.h>
#include <Utilities/Color.h>

#include <map>
#include <lua.hpp>


namespace slth
{
	class ProcessManager;
	class IProcess;
	class IGraphics;
	class World;

/// <summary>
/// Responsible for actor creation and insertion in the world, including components
/// </summary>
class ActorFactory
{
	using ComponentCreator = std::function<IComponent*(Actor*) >;
	using ComponentCreatorMap = std::unordered_map<Id, ComponentCreator>;
public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	SLTH_API ActorFactory();

	/// <summary>
	/// Default Destructor 
	/// </summary>
	SLTH_API ~ActorFactory();

	/// <summary>
	/// Initialize the ActorFactory
	/// </summary>
	SLTH_API void Init();

	/// <summary>
	/// Takes and stores a pointer to the LuaState for the game / application
	/// </summary>
	/// <param name="pLuaState"></param>
	SLTH_API void SetLuaState(lua_State* pLuaState) { m_pLuaState = pLuaState; }

	/// <summary>
	/// Create actors from and XML file and inserts them into the specified map of Actor pointers.
	/// </summary>
	/// <param name="filename">The XML filename</param>
	/// <param name="list">A reference to the map to put the actors in</param>
	/// <param name="pGraphics">A pointer to the graphics system (Needed for Sprite loading)</param>
	/// <param name="pWorld">A pointer to the World (Physics World, necessary for RigidBody)</param>
	SLTH_API void CreateActors(const char* filename, std::map<Id32, Actor*>& list, IGraphics* pGraphics, World* pWorld);
	
	/// <summary>
	/// Creates an actor from raw data. This only creates a Transform and RigidBody component
	/// </summary>
	/// <param name="tag">The tag (string) for the actor</param>
	/// <param name="x">The X position for the transform</param>
	/// <param name="y">The Y position for the transform</param>
	/// <param name="width">The width of the Transform</param>
	/// <param name="height">The height of the Transform</param>
	/// <param name="list">A reference to the map to put the actors in</param>
	/// <param name="pGraphics">A pointer to the graphics system (Needed for Sprite loading)</param>
	/// <param name="pWorld">A pointer to the World (Physics World, necessary for RigidBody)</param>
	SLTH_API void CreateActor(const char* tag, float x, float y, float width, float height, std::map<Id32, Actor*>& list, World* pWorld);

	/// <summary>
	/// Creates a blank actor with no components
	/// </summary>
	/// <param name="tag"></param>
	/// <param name="list">A reference to the map to put the actors in</param>
	/// <returns>A pointer to the newly created actor</returns>
	SLTH_API Actor* CreateBlankActor(const char* tag, std::map<Id32, Actor*>& list);

	SLTH_API void CreateActor(XmlData* pXmlElement, std::map<Id32, Actor*>& list, IGraphics* pGraphics, World* pWorld);

	SLTH_API virtual Actor* CloneActor(Actor& otherActor, Vector2f position);

	SLTH_API slth::Actor* CreateBlockActor(const char* tag, Vector2f position, Vector2f size, Color color, std::map<Id32, Actor*>& list);

	SLTH_API void RegisterComponentCreator(Id componentId, ComponentCreator creator) 
	{
		m_componentCreators[componentId] = creator;
	}

	void RegisterWithLua(Actor* pActor);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	u32 m_nextActorId;
	lua_State* m_pLuaState;

	ComponentCreatorMap m_componentCreators;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}