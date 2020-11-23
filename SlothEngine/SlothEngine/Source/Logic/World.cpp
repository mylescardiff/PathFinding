#include "World.h"
#include <Logger/Logger.h>
#include <Common.h>
#include <Graphics/IGraphics.h>
#include <Logic/Events/EventDispatcher.h>
#include <Logic/IGameLayer.h>

namespace slth
{
	World::World()
		: m_physicsScale(64.f)
		, m_pPhysicsWorld(nullptr)
	{
		//
	}

	World::~World()
	{
		delete m_pPhysicsWorld;
	}
	bool World::Init(const char* xmlFilePath)
	{
		using namespace tinyxml2;

		XMLDocument doc;
		XMLError error = doc.LoadFile(xmlFilePath);
		if (error != XML_SUCCESS)
		{
			_LOGE("XML file load failed");
			return false;
		}
		
		// read world data
		XMLElement* pRoot = doc.RootElement();
		m_size.x = pRoot->FloatAttribute("width");
		m_size.y = pRoot->FloatAttribute("height");

		m_physicsScale = pRoot->FloatAttribute("physics-scale");
		m_gravity.x = pRoot->FloatAttribute("gravity-x");
		m_gravity.y = pRoot->FloatAttribute("gravity-y");
		m_damping = pRoot->FloatAttribute("damping");

		// create the physics world
		m_pPhysicsWorld = new b2World(b2Vec2(m_gravity.x, m_gravity.y));
		m_pPhysicsWorld->SetContactListener(this);

#if _DEBUG_DRAW
		m_pPhysicsWorld->SetDebugDraw(&m_debugDraw);
		m_debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit | b2Draw::e_centerOfMassBit);
#endif
		m_pPhysicsWorld->SetWarmStarting(true);
		m_pPhysicsWorld->GetAutoClearForces();

		return true;
	}
	void World::Step(float32 timeStep, int32 velocityIterations, int32 positionIterations)
	{
		m_pPhysicsWorld->Step(timeStep, velocityIterations, positionIterations);
#if _DEBUG_DRAW
		m_pPhysicsWorld->DrawDebugData();
#endif
	}
	void World::BeginContact(b2Contact * pContact)
	{
		Actor* pActorA = static_cast<Actor*>(pContact->GetFixtureA()->GetBody()->GetUserData());
		Actor* pActorB = static_cast<Actor*>(pContact->GetFixtureB()->GetBody()->GetUserData());
		
		if (m_pGameLayer)
		{
			m_pGameLayer->CollisionStart(pActorA, pActorB);
		}
	}
	void World::EndContact(b2Contact * pContact)
	{
		Actor* pActorA = static_cast<Actor*>(pContact->GetFixtureA()->GetBody()->GetUserData());
		Actor* pActorB = static_cast<Actor*>(pContact->GetFixtureB()->GetBody()->GetUserData());

		if (m_pGameLayer)
		{
			m_pGameLayer->CollisionEnd(pActorA, pActorB);
		}
	}
	slth::CollisionPair World::GetPairFromContacts(b2Contact* pContact)
	{
		Actor* pActorA = static_cast<Actor*>(pContact->GetFixtureA()->GetBody()->GetUserData());
		Actor* pActorB = static_cast<Actor*>(pContact->GetFixtureB()->GetBody()->GetUserData());
		
		u32 idA = pActorA->GetId();
		u32 idB = pActorB->GetId();
		u32 lowestID = (idA < idB) ? idA : idB;
		u32 highestID = (idA > idB) ? idA : idB;

		uint64_t id = lowestID; // this combines the id
		id |= (uint64_t)(highestID) << 32;
		return {id, pActorA, pActorB};
	}
	void World::SetGameLayer(IGameLayer* pGameLayer)
	{
		m_pGameLayer = pGameLayer;
	}
}