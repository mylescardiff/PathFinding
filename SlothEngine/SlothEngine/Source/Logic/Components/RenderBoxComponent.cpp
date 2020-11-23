	 #include "RenderBoxComponent.h"
#include <Logic/Actor.h>
#include <Logic\Components\TransformComponent.h>
#include <Logic\Components\SpriteComponent.h>


using slth::RenderBoxComponent;

RenderBoxComponent::~RenderBoxComponent()
{
	
}

bool slth::RenderBoxComponent::Init(XmlData* xmlElement)
{
	m_color.m_red = xmlElement->FloatAttribute("r");
	m_color.m_green = xmlElement->FloatAttribute("g");
	m_color.m_blue = xmlElement->FloatAttribute("b");
	m_color.m_opacity = xmlElement->FloatAttribute("opacity");
	if (m_color.m_opacity == 0.f)
		m_color.m_opacity = 255.f;

	return true;
}

bool slth::RenderBoxComponent::Init(Vector2f size, float r, float g, float b)
{
	m_size = size;
	m_color = Color(r, g, b, 255.f);
	return true;
}

bool slth::RenderBoxComponent::PostInit()
{
	// check for transform component on the parent
	TransformComponent* transformComponent = GetTransform();
	if (!transformComponent)
	{
		_LOGW("There is not transform component on an actor with RenderBox");
		return false;
	}
	return true;
}

void slth::RenderBoxComponent::Draw(IGraphics* pGraphics)
{
	TransformComponent* pTransComp = GetTransform();
	Color color(m_color.m_red, m_color.m_green, m_color.m_blue, m_color.m_opacity);
	RectInt rect = pTransComp->GetPositionRect();
	pGraphics->DrawRect(rect, color, color, 0, pTransComp->GetRotation());
}

slth::TransformComponent* slth::RenderBoxComponent::GetTransform()
{
	if (!m_pTransform)
	{
		m_pTransform = m_pOwner->GetComponent<TransformComponent>();
	}

	return m_pTransform;
}

slth::SpriteComponent* slth::RenderBoxComponent::GetSprite()
{
	if (!m_pSprite)
	{
		m_pSprite = m_pOwner->GetComponent<SpriteComponent>();
	}

	return m_pSprite;
}



