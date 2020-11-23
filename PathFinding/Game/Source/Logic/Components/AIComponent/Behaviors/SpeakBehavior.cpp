#include "SpeakBehavior.h"
#include <Logic/Actor.h>
#include <Logic/Components/TextComponent.h>
#include <Logic/Components/AIComponent/AIComponent.h>



SpeakBehavior::SpeakBehavior(const char* text, float duration)
	: m_text(text)
	, m_duration(duration)
{
	
}

SpeakBehavior::~SpeakBehavior()
{
	
}

void SpeakBehavior::Update(float deltaTime)
{
	m_pOwner->GetOwner()->GetComponent<slth::TextComponent>()->SetText(m_text);
	m_duration -= deltaTime;
	if (m_duration <= 0.f)
	{
		m_pOwner->GetOwner()->GetComponent<slth::TextComponent>()->SetText("");
		NextBehavior();
	}
}
