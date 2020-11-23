#include "IBehavior.h"
#include <Logic/Actor.h>
#include <Logic/Components/AIComponent/AIComponent.h>

void IBehavior::Init(AIComponent* pOwner)
{
	// grab references to the owner 
	m_pOwner = pOwner;
	
}

void IBehavior::Update(float deltaTime)
{
	if (!m_pTransform)
	{
		m_pTransform = m_pOwner->GetOwner()->GetComponent<slth::TransformComponent>();
	}
}

IBehavior* IBehavior::ChainBehavior(IBehavior* nextBehavior)
{
	m_pNextBehavior = nextBehavior;
	
	return nextBehavior;
}

void IBehavior::NextBehavior()
{
	if (m_pNextBehavior)
	{
		m_pOwner->SetBehavior(m_pNextBehavior);
	}
	else
	{
		m_pOwner->SetBehavior(nullptr);
	}
	
	
	
}
