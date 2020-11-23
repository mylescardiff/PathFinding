#pragma once
/** \file World.h */
// Created by Myles Cardiff

#include <Box2D.h>
#include <Utilities/Vector2f.h>
#include <Logic/Actor.h>
#include <Graphics/SfmlDebugPhysicsRenderer.h>
//#include <Logic/IGameLayer.h>


//! \namespace Sloth Engine
namespace slth
{
	class IGraphics;
	class IGameLayer;

	struct CollisionPair
	{
		u64 m_id;
		Actor* m_pActorA;
		Actor* m_pActorB;
	};


/** \class World */
/** World Class */
class World : public b2ContactListener
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	SLTH_API World();

	/** Default Destructor */
	SLTH_API ~World();

	/** Initialize the world */
	SLTH_API bool Init(const char* xmlFilePath);

	/** Process one frame in the physics world */
	SLTH_API void Step(float32 timeStep, int32 velocityIterations, int32 positionIterations);


protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	
	Vector2f m_size;
	b2World* m_pPhysicsWorld;
	float m_physicsScale;
	Vector2f m_gravity;
	IGameLayer* m_pGameLayer;

	float m_damping;
	
	SfmlDebugPhysicsRenderer m_debugDraw;

	std::unordered_map<u64, CollisionPair> m_contactList;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	void BeginContact(b2Contact* pContact) final;
	void EndContact(b2Contact* pContact) final override;
	CollisionPair GetPairFromContacts(b2Contact* pContact);

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API void SetGraphics(IGraphics* pGraphics) { m_debugDraw.Init(pGraphics); }
	SLTH_API b2World* GetPhysicsWorld() { return m_pPhysicsWorld; }
	SLTH_API Vector2f GetSize() const { return m_size; }
	SLTH_API void SetSize(const float x, const float y) { m_size.x = x; m_size.y = y; }
	SLTH_API void SetGravity(float x, float y) { m_pPhysicsWorld->SetGravity(b2Vec2(x, y)); }
	SLTH_API float GetPhysicsScale() const { return m_physicsScale; }
	SLTH_API float GetDPI() const { return 1.f; }
	SLTH_API void DebugDraw() const { 
		m_pPhysicsWorld->DrawDebugData(); 
	}
	SLTH_API float GetDamping() const { return m_damping; }
	
	SLTH_API void SetGameLayer(IGameLayer* pGameLayer);
	SLTH_API Vector2f GetCenter() { return { m_size.x / 2, m_size.y / 2 }; }
};

}