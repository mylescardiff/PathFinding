#include "Map.h"
#include <sstream>

using slth::Map;

std::vector<slth::TiledObject> slth::Map::LoadMap(const char* filepath)
{
	std::vector<TiledObject> objects;

	XmlDoc doc;
	auto error = doc.LoadFile(filepath);
	if (error != tinyxml2::XML_SUCCESS)
	{
		_LOGE("Error opening tile xml");
		return objects;
	}

	XmlData* pRoot = doc.RootElement();

	m_mapWidth = pRoot->IntAttribute("width");
	m_mapHeight = pRoot->IntAttribute("height");
	m_tileSize = pRoot->IntAttribute("tilewidth");

	XmlData* pTileset = pRoot->FirstChildElement("tileset");
	std::string relativeFilepath = filepath;

	std::string subFilePath = relativeFilepath.substr(0, relativeFilepath.rfind('\\') + 1);
	m_tileset.Load(subFilePath, pTileset);

	for (XmlData* pLayer = pRoot->FirstChildElement("layer");
		pLayer != nullptr;
		pLayer = pLayer->NextSiblingElement("layer"))
	{
		Layer layer;
		layer.m_layerName = pLayer->Attribute("name");

		// load custom properties (just the passable) tag at the moment
		XmlData* pPropertiesTag = pLayer->FirstChildElement("properties");
		layer.m_passable = false;
		layer.m_overhead = false;
		if (pPropertiesTag)
		{
			for (XmlData* pPropertyTag = pPropertiesTag->FirstChildElement("property");
				pPropertyTag != nullptr;
				pPropertyTag = pPropertyTag->NextSiblingElement("property"))
			{
				auto test = pPropertyTag->Attribute("name");
				if (strcmp(pPropertyTag->Attribute("name"), "passable"))
					layer.m_passable = pPropertyTag->BoolAttribute("value");

				if (strcmp(pPropertyTag->Attribute("name"), "overhead"))
					layer.m_overhead = pPropertyTag->BoolAttribute("value");
			}
			
		}
		
		int gridX = 0;
		int gridY = 0;

		std::stringstream stream(pLayer->FirstChildElement("data")->GetText());
		std::string id;
		while (std::getline(stream, id, ','))
		{
			int index = std::stoi(id);

			if (index != 0)
			{
				// tile found
				Tile tile;
				tile.m_gridX = gridX;
				tile.m_gridY = gridY;
				tile.m_tileId = index;
				layer.m_tiles.emplace_back(tile);
			}

			++gridX;

			if (gridX >= (int)m_mapWidth)
			{
				gridX = 0;
				++gridY;
			}
		}

		m_layers.emplace_back(layer);

	}

	XmlData* pObjectGroup = pRoot->FirstChildElement("objectgroup");
	if (pObjectGroup)
	{
		for (XmlData* pObject = pObjectGroup->FirstChildElement("object");
			pObject != nullptr;
			pObject = pObject->NextSiblingElement("object"))
		{
			objects.push_back({
				pObject->FloatAttribute("x"),
				pObject->FloatAttribute("y"),
				pObject->FloatAttribute("width"),
				pObject->FloatAttribute("height")
			});
		}
	}

	return objects;

}

void slth::Map::DrawLayer(const char* name)
{
	int x = 0;
	int y = 0;

	slth::RectInt rectDest(0, 0, m_tileSize, m_tileSize);
	slth::RectInt rectSource;
	for (size_t iLayer = 0; iLayer < m_layers.size(); ++iLayer)
	{
		if (m_layers[iLayer].m_layerName == std::string(name))
		{
			for (size_t iTile = 0; iTile < m_layers[iLayer].m_tiles.size(); ++iTile)
			{
				slth::Tile& tile = m_layers[iLayer].m_tiles[iTile];

				// source rect
				rectSource.left = ((tile.m_tileId - 1) % m_tileset.m_columns) * m_tileSize;
				rectSource.top = ((tile.m_tileId - 1) / m_tileset.m_columns) * m_tileSize;
				rectSource.right = rectSource.left + m_tileSize;
				rectSource.bottom = rectSource.top + m_tileSize;

				// dest rect
				rectDest.left = tile.m_gridX * m_tileSize;
				rectDest.top = tile.m_gridY * m_tileSize;
				rectDest.right = rectDest.left + m_tileSize;
				rectDest.bottom = rectDest.top + m_tileSize;

				m_pGraphics->DrawTexture(m_tileset.m_textureId.c_str(), rectDest, rectSource, false, 0, slth::Vector2f(0, 0));

			}
		}
		
	}
}


