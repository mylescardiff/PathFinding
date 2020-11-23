#include "AIComponent.h"
#include <Logic/Components/TransformComponent.h>
#include <Logic/Actor.h>
#include <tinyxml2.h> 
#include <Logic/Components/AIComponent/Behaviors/PatrolBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/ChaseBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/ChaseBehavior.h>


AIComponent::AIComponent()
	: m_pCurrentBehavior(nullptr)
{
	//
}

AIComponent::~AIComponent()
{
	delete m_pCurrentBehavior;
}

slth::IComponent* AIComponent::Copy(slth::Actor* pNewOwner)
{
	AIComponent* pCopy = new AIComponent;
	pCopy->SetOwner(pNewOwner);
	return pCopy;
}

bool AIComponent::Init(XmlData* pXmlElement)
{
	const char* stateString = pXmlElement->Attribute("state");

	// get the initial AI State
	if (strcmp(stateString, "Patrol") == 0)
	{
		PatrolBehavior* pPatrol = new PatrolBehavior();

		// get waypoints for patrol, if any
		XmlData* pWaypointElement = pXmlElement->FirstChildElement("Waypoints");
		if (pWaypointElement)
		{
			for (XmlData* pElement = pWaypointElement->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
			{
				slth::Vector2f wp;
				wp.x = pElement->FloatAttribute("x");
				wp.y = pElement->FloatAttribute("y");
				pPatrol->AddWaypoint(wp);
			}
		}
		SetBehavior(pPatrol);
	}
	else
	{
		//TODO: Implement other XML behaviors
	}

	return true;
}

void AIComponent::Update(float deltaTime)
{
	if (m_pCurrentBehavior)
	{
		m_pCurrentBehavior->Update(deltaTime);
	}
}

void AIComponent::Chase(slth::Actor* target, float aquireDistance)
{
	dynamic_cast<ChaseBehavior*>(m_pCurrentBehavior)->SetChaseTarget(target); // should be safe after setting type to chase. 
}

IBehavior* AIComponent::SetBehavior(IBehavior* pBehavior)
{
	if (m_pOwner)
		m_pOwner->GetComponent<slth::TransformComponent>()->Stop();
	
	if (m_pCurrentBehavior)
	{
		delete m_pCurrentBehavior;
	}
	m_pCurrentBehavior = pBehavior;
	
	if (pBehavior)
		pBehavior->Init(this);

	return pBehavior;
}




