#pragma once
/** \file Layer.h */

// Created by Myles Cardiff

#include <Common.h>
#include <vector>
#include <Logic\Tiles\Tile.h>

//! \namespace Sloth Engine
namespace slth
{
/** \class Layer */
/** Represents a layer of tiles in the world */
class Layer
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //
	std::string m_layerName;
	std::vector<Tile> m_tiles;
	bool m_passable;
	bool m_overhead;
	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //


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