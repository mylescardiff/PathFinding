#include "ActorFactory.h"
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/ColliderComponent.h>
#include <Logic/Components/RenderBoxComponent.h>
#include <Logic/Components/TriggerComponent.h>
#include <Logic/Components/SpriteComponent.h>
#include <Logic/Components/TextComponent.h>
#include <Logic/Components/AnimationComponent.h>
#include <Logic/Components/RigidBodyComponent.h>
#include <Logic/Processes/AnimationProcess.h>
#include <Logic/Processes/ProcessManager.h>

using slth::ActorFactory;

ActorFactory::ActorFactory()
	: m_nextActorId(1)
	, m_pLuaState(nullptr)
{
	//
}

ActorFactory::~ActorFactory()
{
	
}

void slth::ActorFactory::Init()
{
	RegisterComponentCreator(HASH("Transform"), [](Actor* pOwner) {
		return new TransformComponent();
	});
	RegisterComponentCreator(HASH("Trigger"), [](Actor* pOwner) {
		return new TriggerComponent();
		});

	RegisterComponentCreator(HASH("RenderBox"), [](Actor* pOwner) {
		return new RenderBoxComponent();
	});

	RegisterComponentCreator(HASH("Sprite"), [](Actor* pOwner) {
		return new SpriteComponent();
	});

	RegisterComponentCreator(HASH("Animation"), [](Actor* pOwner) {
		return new AnimationComponent();
	});
	RegisterComponentCreator(HASH("Text"), [](Actor* pOwner) {
		return new TextComponent();
	});
	RegisterComponentCreator(HASH("RigidBody"), [](Actor* pOwner) {
		return new RigidBodyComponent();
	});
	RegisterComponentCreator(HASH("Collider"), [](Actor* pOwner) {
		return new ColliderComponent();
		});
}

void slth::ActorFactory::CreateActors(const char* filename, std::map<Id32, Actor*>& list, IGraphics* pGraphics, World* pWorld)
{
	using namespace tinyxml2;

	XMLDocument doc;
	XMLError error = doc.LoadFile(filename);
	if (error != XML_SUCCESS)
	{
		_LOGE("XML file load failed");
	}

	XMLElement* pRoot = doc.RootElement();
	XMLElement* pActorElement = pRoot->FirstChildElement("Actor");

	while (pActorElement)
	{
		CreateActor(pActorElement, list, pGraphics, pWorld);
		pActorElement = pActorElement->NextSiblingElement("Actor");
	}
}

void slth::ActorFactory::CreateActor(const char* tag, float x, float y, float width, float height, std::map<Id32, Actor*>& list, World* pWorld)
{
	Actor * pActor = new Actor(m_nextActorId++);	
	pActor->SetTag(tag);

	// transform
	TransformComponent* pTransform = new TransformComponent();
	pActor->AddComponent(pTransform);
	pTransform->Init(x, y, width, height, 0.f);
	
	// rigid body
	RigidBodyComponent* pRigidBody = new RigidBodyComponent();
	pActor->AddComponent(pRigidBody);
	pRigidBody->Init(RigidBodyComponent::BodyType::Static, RigidBodyComponent::BodyShape::Box);

	list.emplace(pActor->GetId(), pActor);
	pRigidBody->SetBody(pWorld);
}

void slth::ActorFactory::CreateActor(XmlData* pXmlElement, std::map<Id32, Actor*>& list, IGraphics* pGraphics, World* pWorld)
{
	Actor* pActor = new Actor(m_nextActorId++); 

	// read in components
	XmlData* pComponentElement = pXmlElement->FirstChildElement("Components");
	for (XmlData* pElement = pComponentElement->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
	{
		std::string tagName = pElement->Name();
		IComponent* pComponent = m_componentCreators[HASH(tagName)](pActor);

		//TODO: Log if componentCreators does not exist

		if (pComponent)
		{
			pComponent->Init(pElement);
			pActor->AddComponent(pComponent);
			pComponent->SetOwner(pActor);
		}

		// set transform world
		slth::TransformComponent* pTransform = dynamic_cast<slth::TransformComponent*>(pComponent);
		if (pTransform)
		{
			pTransform->SetWorld(pWorld);
		}

		// load the texture for the sprite, if it exists
		slth::SpriteComponent* pSpriteComp = dynamic_cast<slth::SpriteComponent*>(pComponent);
		if (pSpriteComp)
		{
			pSpriteComp->LoadTexture(pGraphics);
		}

		// set physics world
		slth::RigidBodyComponent* pRigidBody = dynamic_cast<slth::RigidBodyComponent*>(pComponent);
		if (pRigidBody)
		{
			pRigidBody->SetBody(pWorld);
		}
	}


	if (!pActor->Init(pXmlElement))
	{
		_LOGW("Actor Init() failed");
	}

	if (!pActor->PostInit())
	{
		_LOGW("Actor PostInit() failed");
	}

	RegisterWithLua(pActor);



	list.emplace(pActor->GetId(), pActor);
}

slth::Actor* slth::ActorFactory::CloneActor(Actor& otherActor, Vector2f position)
{
	return new Actor(otherActor, position, ++m_nextActorId);
	
}

slth::Actor* slth::ActorFactory::CreateBlockActor(const char* tag, Vector2f position, Vector2f size, Color color, std::map<Id32, Actor*>& list)
{
	Actor* pActor = new Actor(m_nextActorId++);
	pActor->SetTag(tag);

	// transform
	TransformComponent* pTransform = new TransformComponent();
	pActor->AddComponent(pTransform);
	pTransform->Init(position.x, position.y, size.x, size.y, 0.f);
	pTransform->SetOwner(pActor);

	// renderbox
	RenderBoxComponent* pRenderBox = new RenderBoxComponent();
	pActor->AddComponent(pRenderBox);
	pRenderBox->Init(size, color.m_red, color.m_green, color.m_blue);
	pRenderBox->SetOwner(pActor);

	pActor->PostInit();

	list.emplace(pActor->GetId(), pActor);

	return pActor;

}

slth::Actor* slth::ActorFactory::CreateBlankActor(const char* tag, std::map<Id32, Actor*>& list)
{
	Actor* pActor = new Actor(m_nextActorId++);
	pActor->SetTag(tag);
	list.emplace(pActor->GetId(), pActor);

	return pActor;
}

void slth::ActorFactory::RegisterWithLua(Actor * pActor)
{
	if (!pActor)
	{
		_LOGL("Cannot register nullptr with Lua");
		return;
	}
	
	lua_getglobal(m_pLuaState, "engine");		// [+1]

	lua_getfield(m_pLuaState, -1, "world");		// [+2]

	// create table for our actor
	lua_newtable(m_pLuaState);					// [+3]

	// set some actor data
	lua_pushstring(m_pLuaState, pActor->GetName().c_str());		// [+4] push a string onto the stack, not all actors will have this b/c i don't have a name
	lua_setfield(m_pLuaState, -2, "name");						// name the thing you just pushed onto the stack, in this case "name", this pops off

	lua_pushlightuserdata(m_pLuaState, pActor); // [+4] this is what lua calls a pointer, you're telling it the memory address of this actor
	lua_setfield(m_pLuaState, -2, "this");		// [+3]

	lua_newtable(m_pLuaState);					// [+4]
	for (auto& component : pActor->GetComponents())
	{
		component.second->RegisterWithLua(m_pLuaState, component.second->GetName());
	}
	lua_setfield(m_pLuaState, -2, "components"); // [+3]

	// set the key of the actor table
	lua_setfield(m_pLuaState, -2, pActor->GetName().c_str()); // [-1] 8:14 pm - explaination in lecture
	
	// remove the engine and world tables from the stack
	lua_pop(m_pLuaState, 2);
	
	                                                   
}
