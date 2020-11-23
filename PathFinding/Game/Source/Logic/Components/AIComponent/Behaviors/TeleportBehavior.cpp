#include "TeleportBehavior.h"



TeleportBehavior::TeleportBehavior(slth::Vector2f position, float rotation)
	: m_position(position)
	, m_rotation(rotation)
{
	//
}


void TeleportBehavior::Update(float deltaTime)
{
	IBehavior::Update(deltaTime);

	m_pTransform->SetPosition(m_position);
	m_pTransform->SetRotation(m_rotation);

	NextBehavior();
}
