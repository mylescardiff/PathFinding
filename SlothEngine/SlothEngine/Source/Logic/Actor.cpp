#include "Actor.h"
#include <Logic\Components\TransformComponent.h>
#include <Logic\Components\RigidBodyComponent.h>
#include <Logger/Logger.h>

using slth::Actor;

Actor::Actor(Id32 id)
	: m_id(id)
	, m_hidden(false)
{
	//
}

slth::Actor::Actor(const Actor& otherActor, const Vector2f position, u32 id)
{
	m_id = id;
	m_name = otherActor.m_name + std::to_string(m_id);
	m_tag = otherActor.m_tag;
	
	for (auto pComp : otherActor.m_components)
	{
		IComponent* copy = pComp.second->Copy(this);

		// check if this is a transform and make sure it's set 
		// to the new position before rigid body is initialized
		TransformComponent* pTransformComp = dynamic_cast<TransformComponent*>(copy);
		if (pTransformComp)
		{
			pTransformComp->SetPosition(position);
		}

		RigidBodyComponent* pRigidBody = dynamic_cast<RigidBodyComponent*>(copy);
		if (pRigidBody)
		{
			pRigidBody->SetPosition(position);
		}

		copy->SetOwner(this);

		m_components.emplace(pComp.first, copy);

		
	}

	if (!PostInit())
	{
		_LOGW("Actor PostInit() failed");
	}

}

Actor::~Actor()
{
	for (auto pComponent : m_components)
	{
		delete pComponent.second;
	}
}

bool slth::Actor::Init(XmlData* pData)
{
	m_name = pData->Attribute("ID");
	const char* charTag = pData->Attribute("tag");
	if (charTag)
	{
		m_tag = charTag;
	}
	else
	{
		m_tag = m_name;
	}
	m_hidden = pData->BoolAttribute("hidden");
	return true;
}

bool slth::Actor::PostInit()
{
	// need to run post init on all components now that they are loadeed
	// so we can check if the ones that rely on each other exist
	for (auto pComp : m_components)
	{
		pComp.second->PostInit();
	}
	
	return true;
}


SLTH_API void slth::Actor::AddComponent(IComponent* pComponent)
{
	pComponent->SetOwner(this);
	m_components.emplace(pComponent->GetIdentifier(), std::move(pComponent));
}

slth::IComponent * slth::Actor::GetComponent(Id id)
{
	auto componentItr = m_components.find(id);
	if (componentItr == m_components.end())
	{
		_LOGW("Component Find() failed.");
		return nullptr;
	}

	return componentItr->second;
}

slth::IComponent* slth::Actor::GetComponent(std::string& name)
{
	return GetComponent((Id)std::hash<std::string>()(name));
}

void slth::Actor::ApplyLinearImpulse(float x, float y)
{
	RigidBodyComponent* pRigidBody = GetComponent<RigidBodyComponent>();
	if (pRigidBody)
	{
		pRigidBody->ApplyLinearImpulse(x, y);
	}
}
