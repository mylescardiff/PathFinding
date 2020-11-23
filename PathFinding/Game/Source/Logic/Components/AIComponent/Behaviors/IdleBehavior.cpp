#include "IdleBehavior.h"



IdleBehavior::IdleBehavior(float idleTime)
	: m_idleTime(idleTime)
{
	//
}

IdleBehavior::~IdleBehavior()
{
	
}

void IdleBehavior::Update(float deltaTime)
{
	m_idleTime -= deltaTime;
	if (m_idleTime <= 0.f)
	{
		NextBehavior();
		return;
	}

}
