#include "TurnBehavior.h"
#include <Logic/Components/TransformComponent.h>


TurnBehavior::TurnBehavior(float angle)
	: m_angle(angle)
{
	//
}


TurnBehavior::~TurnBehavior()
{
	
}

void TurnBehavior::Update(float deltaTime)
{
	IBehavior::Update(deltaTime);

	m_pTransform->RotateTowards(m_angle, deltaTime);
	if (m_angle - m_pTransform->GetRotation() < 0.05f)
	{
		NextBehavior();
	}
	
}
