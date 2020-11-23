#include "TriggerComponent.h"

using slth::TriggerComponent;

TriggerComponent::TriggerComponent()
	: m_radius(9999.f)
	, m_active(false)
{
	
}

slth::IComponent* TriggerComponent::Copy(slth::Actor* pNewOwner)
{
	TriggerComponent* pCopy = new TriggerComponent();
	pCopy->SetOwner(pNewOwner);
	pCopy->m_radius = m_radius;
	pCopy->m_tag = m_tag;

	return pCopy;
}

bool slth::TriggerComponent::Init(XmlData* xmlElement)
{
	m_radius = xmlElement->FloatAttribute("radius");
	m_tag = xmlElement->Attribute("tag");
	return true;
}
