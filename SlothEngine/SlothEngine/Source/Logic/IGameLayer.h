#pragma once
/** \file IGameLayer.h */
// Created by Myles Cardiff

#include "..\Common.h"
#include <memory>
#include <vector>
#include <map>
#include <Logic/Processes/ProcessManager.h>
#include <Logic/Events/EventDispatcher.h>
#include <Logic/AnimationManager.h>
#include <Logic/World.h>
#include <Logic/Tiles/Map.h>
#include <Logic/Events/CollisionEvent.h>
#include <lua.hpp>
#include <Logic/Grid/GridSystem.h>
#include <Logic/Components/ColliderComponent.h>

namespace glua
{
	/// <summary>
	/// Glua version of the FindActor function for using it in script
	/// </summary>
	int IGameLayer_FindActor(lua_State* pState);
}

//! \namespace Sloth Engine
namespace slth
{
	/* Forward Declarations */
	class IView;
	class ApplicationLayer;
	class AnimationManager;
	class ActorFactory;
	class IGraphics;
	class IAudioSystem;

	/// <summary>
	/// Base class for all game logic. This class should be inherited by any 
	/// game and used to create main loop, update, draw and input logic. 
	/// </summary>
	class IGameLayer
	{
	public:
		
		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		
		/// <summary>
		/// Default Constructor
		/// </summary>
		SLTH_API IGameLayer();

		/// <summary>
		/// Default Destructor
		/// </summary>
		SLTH_API virtual ~IGameLayer();

		/// <summary>
		/// Get the game name. This should be overridden in derived classes and set. 
		/// </summary>
		/// <returns>c-style string representing the game name.</returns>
		SLTH_API virtual const char* GetGameName() const = 0;

		/// <summary>
		/// Initialize the game logic
		/// </summary>
		/// <param name="pAppLayer">A pointer to the application layer object (derived from ApplicationLayer)</param>
		/// <returns>True if initialization is succesful, false if it fails</returns>
		SLTH_API virtual bool Init(ApplicationLayer* pAppLayer);

		/// <summary>
		/// Post initalization function. This is intended for logic that must run after Init() has 
		/// completed but before the main game loop begins. 
		/// </summary>
		/// <returns>True if initialization is succesful, false if it fails</returns>
		SLTH_API virtual bool PostInit();

		/// <summary>
		/// This is the main update loop for all objects in the game. Should be overridden in the
		/// game logic to extend functionality, but make sure to call this function on the base class
		/// in your derivation
		/// </summary>
		/// <param name="deltaTime">Delta (frame) time in seconds</param>
		SLTH_API virtual void Update(float deltaTime);

		/// <summary>
		/// Draw the world on screen
		/// </summary>
		SLTH_API virtual void Draw();

		/// <summary>
		/// Called during the draw frame, but before anything is drawn
		/// </summary>
		SLTH_API virtual void PreDraw() {}

		/// <summary>
		/// Called during the draw frame, but between Actors and UI
		/// </summary>
		SLTH_API virtual void InnerDraw() {}

		/// <summary>
		/// Called during the draw frame, but after everything is drawn
		/// </summary>
		SLTH_API virtual void PostDraw() {}

		/// <summary>
		/// Add a view to the container of views (this is deprecated and no longer necessary)
		/// </summary>
		/// <param name="pView"></param>
		SLTH_API virtual void AddView(IView* pView) { m_pViews.emplace_back(pView); }

		/// <summary>
		/// Find an actor by integer ID
		/// </summary>
		/// <param name="id">The ID of the actor you want to find.</param>
		/// <returns>A pointer to the actor if found, nullptr if there is no actor with that ID</returns>
		SLTH_API virtual Actor* FindActor(Id32 id);

		/// <summary>
		/// Find an actor by name (c-style string version)
		/// </summary>
		/// <param name="name">The string name of the actor you're looking for</param>
		/// <returns>A pointer to the actor if found, nullptr if there is no actor with that name</returns>
		SLTH_API virtual Actor* FindActor(const char* name);

		/// <summary>
		/// Find a UI Element by name (std::string version)
		/// </summary>
		/// <param name="name">The std::string name of the actor you're looking for</param>
		/// <returns>A pointer to the actor if found, nullptr if there is no actor with that name</returns>
		SLTH_API virtual Actor* FindUIElement(std::string id);

		/// <summary>
		/// Find a UI Element by name (c-style string version)
		/// </summary>
		/// <param name="name">The string name of the actor you're looking for</param>
		/// <returns>A pointer to the actor if found, nullptr if there is no actor with that name</returns>
		SLTH_API virtual Actor* FindUIElement(const char* name) { return FindUIElement(std::string(name)); }

		/// <summary>
		/// Create an actor in the world from a pointer.
		/// </summary>
		/// <param name="pActor">The already-constructed actor you want to add to the world.</param>
		SLTH_API void AddActor(Actor* pActor);

		/// <summary>
		/// Destroy an actor. This will happen at the end of the frame when called. 
		/// </summary>
		/// <param name="id">The integer ID of the actor to be destroyed</param>
		SLTH_API virtual void KillActor(Id32 id);

		/// <summary>
		/// Draws colliders and physics bodies on screen. 
		/// </summary>
		SLTH_API virtual void DebugDraw() { m_pWorld->DebugDraw(); }

		/// <summary>
		/// Called when collision begins on two actors
		/// </summary>
		/// <param name="pActorA">The first actor involved in the collision</param>
		/// <param name="pActorB">The second actor involved in the collision</param>
		SLTH_API virtual void CollisionStart(Actor* pActorA, Actor* pActorB);

		/// <summary>
		/// Called when collision ends on two actors
		/// </summary>
		/// <param name="pActorA">The first actor involved in the collision</param>
		/// <param name="pActorB">The second actor involved in the collision</param>
		SLTH_API virtual void CollisionEnd(Actor* pActorA, Actor* pActorB);
		
		/// <summary>
		/// Called when trigger begins on two actors
		/// </summary>
		/// <param name="pActorA">The first actor involved in the collision</param>
		/// <param name="pActorB">The second actor involved in the collision</param>
		SLTH_API virtual void TriggerEnter(Actor* pActorA, Actor* pActorB) {}

		/// <summary>
		/// Called when trigger ends on two actors
		/// </summary>
		/// <param name="pActorA">The first actor involved in the collision</param>
		/// <param name="pActorB">The second actor involved in the collision</param>
		SLTH_API virtual void TriggerLeave(Actor* pActorA, Actor* pActorB) {};

		/// <summary>
		/// Sets all the actors with a specific tag visible / invisible
		/// </summary>
		/// <param name="tag">The string tag to search for</param>
		/// <param name="visible">True for visible, False for invisible</param>
		SLTH_API virtual void SetActorsVisibleByTag(const char* tag, bool visible);

		/// <summary>
		/// Pauses the game
		/// </summary>
		SLTH_API void Pause() { m_paused = !m_paused; }

		/// <summary>
		/// Quits the game
		/// </summary>
		SLTH_API void Quit() { m_quit = true; }

	protected:
		// --------------------------------------------------------------------- //
		// Protected Member Variables
		// --------------------------------------------------------------------- //

		ApplicationLayer* m_pAppLayer;

		std::vector<IView*> m_pViews;
		float m_timeAccumulator;

		ActorFactory* m_pActorFactory;
		std::map<Id32, slth::Actor*> m_actors;
		std::vector<Id32> m_actorsToDelete;
		std::vector<slth::Actor*> m_actorsToAdd;
		u32 m_playMode;

		std::map<Id32, slth::Actor*> m_uiElements;

		bool m_checkCollision; 
		float m_defaultCollideTimout;

		IGraphics* m_pGraphics;
		IAudioSystem* m_pAudio;
		World* m_pWorld;

		AnimationManager m_animationManager;
		EventDispatcher m_eventDispatcher;
		ProcessManager m_processManager;

		lua_State* m_pLuaState;
		bool m_luaTickExists;

		CollisionEvent* m_pCollisionEvent;

		slth::Map m_map;

		slth::GridSystem m_gridSystem;

		bool m_quit;
		bool m_paused;

private: 

		/// <summary>
		/// Creates the lua state for scripting to begin
		/// </summary>
		SLTH_API void CreateLuaState();

		/// <summary>
		/// Prints what's in the lua stack to the console
		/// CREDIT: Written by Dylan Wjinen.
		/// </summary>
		/// <param name="pLuaState"></param>
		static void PrintLuaStack(lua_State* pLuaState);

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //

		SLTH_API ActorFactory* GetActorFactory() { return m_pActorFactory; }
		SLTH_API IAudioSystem* GetAudio() { return m_pAudio; }
		SLTH_API IGraphics* GetGraphics() { return m_pGraphics; }
		SLTH_API World* GetWorld() { return m_pWorld; }
		SLTH_API std::map<Id32, slth::Actor*>& GetActors() { return m_actors; }
		SLTH_API EventDispatcher& GetEventDispatcher() { return m_eventDispatcher; }
		SLTH_API ProcessManager& GetProcessManager() { return m_processManager; }
		SLTH_API AnimationManager& GetAnimationsManager() { return m_animationManager; }
		SLTH_API Map& GetMap() { return m_map; }
		SLTH_API GridSystem& GetGrid() { return m_gridSystem; }
		SLTH_API std::map<Id32, slth::Actor*>& GetUIElements() { return m_uiElements; }

		SLTH_API bool HasQuit() { return m_quit; }

		SLTH_API void SetDefaultCollisionTimeout(float timeout) { m_defaultCollideTimout = timeout; }

		SLTH_API const u32 GetPlayMode() { return m_playMode; }
		SLTH_API void SetPlayMode(const u32 playMode) { m_playMode = playMode; }
	};
}