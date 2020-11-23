#include "ChaseBehavior.h"
#include <Logic/Actor.h>
#include <Logic/Components/AIComponent/AIComponent.h>

ChaseBehavior::ChaseBehavior(slth::Actor* pActor, float acquireDistance)
	: m_pChaseTarget(pActor)
	, m_acquireDistance(acquireDistance)
{
	//
}

void ChaseBehavior::Update(float deltaTime)
{
	IBehavior::Update(deltaTime);

	// predict the target's position
	slth::TransformComponent* pTargetTransform = m_pChaseTarget->GetComponent<slth::TransformComponent>();
	slth::Vector2f targetPos = pTargetTransform->GetPosition() + pTargetTransform->GetVelocity() * s_kPredictTurns * deltaTime;

	// check if we've reached the wapoint
	if (m_pTransform->GetPosition().IsApproximatleyEqualTo(targetPos, m_acquireDistance))
	{
		m_pTransform->Stop();
		NextBehavior();
		return;
	}

	m_pTransform->MoveTowards(targetPos, deltaTime);
	m_pTransform->RotateTowards(targetPos, deltaTime);
}
