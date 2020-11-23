#include "Tileset.h"
#include <Graphics/IGraphics.h>

using slth::Tileset;

bool slth::Tileset::Load(std::string& relPath, XmlData* pXmlElement)
{
	m_name = pXmlElement->Attribute("name");
	m_tileWidth = pXmlElement->IntAttribute("tilewidth");
	m_tileHeight = pXmlElement->IntAttribute("tileheight");
	m_tileCount = pXmlElement->IntAttribute("tilecount");
	m_columns = pXmlElement->IntAttribute("columns");

	XmlData* pImageElement = pXmlElement->FirstChildElement("image");

	m_imgHeight = pImageElement->IntAttribute("width");
	m_imgWidth = pImageElement->IntAttribute("height");

	m_textureId = (relPath + std::string(pImageElement->Attribute("source")));

	m_pGraphics->LoadTexture(m_textureId.c_str());
	return true;
}