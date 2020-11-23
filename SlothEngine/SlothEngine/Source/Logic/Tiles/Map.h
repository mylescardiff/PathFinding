#pragma once
/** \file Map.h */

// Created by Myles Cardiff

#include <vector>
#include <Common.h>
#include <Logic/Tiles/Layer.h>
#include <Logic/Tiles/Tileset.h>
#include <Graphics/IGraphics.h>

//! \namespace Sloth Engine
namespace slth
{
	struct TiledObject
	{
		float x;
		float y;
		float width;
		float height;
	};
/** \class Map */
/** A Tile-based game map */
class Map
{

public:

	//<objectgroup name = "Objects" visible = "0" locked = "1">
	//<object id = "1" x = "-1" y = "0" width = "15" height = "510" / >
	//<object id = "2" x = "14" y = "0" width = "498" height = "15" / >
	//<object id = "3" x = "497" y = "17" width = "15" height = "495" / >
	//<object id = "10" x = "15" y = "495" width = "482" height = "17" / >
	//</ objectgroup>



	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //
	std::vector<Layer> m_layers;

	u32 m_mapWidth;
	u32 m_mapHeight;
	u32 m_tileSize;

	IGraphics* m_pGraphics;

	Tileset m_tileset;

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	SLTH_API void SetGraphics(IGraphics* pGraphics) { m_pGraphics = pGraphics; }
	SLTH_API void LoadTileset(std::string relativeFilepath, Tileset* pTileset);
	SLTH_API std::vector<TiledObject> LoadMap(const char* filepath);
	SLTH_API void DrawLayer(const char* name);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}