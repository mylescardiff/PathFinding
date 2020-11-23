#include "TextComponent.h"
#include <Graphics/IGraphics.h>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Actor.h>

using slth::TextComponent;

bool slth::TextComponent::Init(XmlData * pXmlElement)
{
	const char* pText = pXmlElement->GetText();
	if (pText)
	{
		m_text = pText;
	}
	m_color = Color(
		pXmlElement->FloatAttribute("r"),
		pXmlElement->FloatAttribute("g"),
		pXmlElement->FloatAttribute("b"));

	//TODO: There's no way to render these at the moment, but will add them
	m_alignHorizontal = HorizontalAlignment::Left;
	m_alignVertical = VerticalAlignment::Middle;

	m_fontSize = static_cast<unsigned short>(pXmlElement->Int64Attribute("size"));
	m_offset.x = pXmlElement->FloatAttribute("offset-x");
	m_offset.y = pXmlElement->FloatAttribute("offset-y");
	return true;
}

void slth::TextComponent::Draw(IGraphics * pGraphics)
{
	if (!m_pTransformComponent)
		m_pTransformComponent = m_pOwner->GetComponent<TransformComponent>();

	Vector2f position = m_pTransformComponent->GetPosition() + m_offset;

	pGraphics->DrawText(m_text.c_str(), position, m_fontSize, m_color);

}

