 #include "ColliderComponent.h"
#include "TransformComponent.h"
#include <Logic/Actor.h>

using slth::ColliderComponent;

ColliderComponent::ColliderComponent()
	: m_collisionTimeout(0)
{
	
}

ColliderComponent::~ColliderComponent()
{
	
}

bool slth::ColliderComponent::Init(XmlData* xmlElement)
{
	m_size.x = xmlElement->FloatAttribute("sizeX");
	m_size.y = xmlElement->FloatAttribute("sizeY");
	m_offset.x = xmlElement->FloatAttribute("offsetX");
	m_offset.y = xmlElement->FloatAttribute("offsetY");
	return true;
}


slth::RectInt slth::ColliderComponent::GetRect()
{
	TransformComponent* pTransform = m_pOwner->GetComponent<TransformComponent>();
	if (pTransform)
	{
		RectInt transformPosRect = pTransform->GetPositionRect();
		return RectInt(transformPosRect.left + (int)m_offset.x, transformPosRect.top + (int)m_offset.y, transformPosRect.left + (int)m_offset.x + (int)m_size.x, transformPosRect.top + (int)m_offset.y + (int)m_size.y);
	}
	return RectInt(0, 0, 0, 0);
}

