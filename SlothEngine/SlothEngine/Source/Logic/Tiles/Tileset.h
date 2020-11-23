#pragma once
/** \file Tileset.h */

// Created by Myles Cardiff
#include <Common.h>

//! \namespace Sloth Engine
namespace slth
{
	class ITexture;
	class IGraphics;

/** \class Tileset */
/** Represents a texture and size basis for creating a tile map */
class Tileset
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //
	std::string m_name;
	u32 m_tileWidth;
	u32 m_tileHeight;
	u32 m_tileCount;
	u32 m_columns;

	u32 m_imgWidth;
	u32 m_imgHeight;
	std::string m_textureId;

	IGraphics* m_pGraphics;
	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	bool Load(std::string& relPath, XmlData* pXmlElement);

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
	void SetGraphics(IGraphics* pGraphics) { m_pGraphics = pGraphics; }

};
}