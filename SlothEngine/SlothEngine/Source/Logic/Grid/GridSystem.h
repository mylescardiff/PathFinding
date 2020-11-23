#pragma once
/** \file GridSystem.h */
// Created by Myles Cardiff

#include <Utilities/Vector2f.h>
#include <map>
#include <vector>
#include <Utilities/RectInt.h>
#include <Graphics/ITexture.h>
#include <Logic/Grid/GridTile.h>
#include <queue>

namespace slth
{
	class ActorFactory;
	class Actor;
	class IGraphics;

	/// <summary>
	/// Priority ordering function for the A* (see PathAStarInternal)
	/// </summary>
	auto nodePriorityFunc = [](GridTile* pLeft, GridTile* pRight)
	{
		return pLeft->GetFScore() > pRight->GetFScore();
	};

	typedef std::priority_queue<GridTile*, std::vector<GridTile*>, decltype(nodePriorityFunc)> OpenSet;
	typedef std::vector<Vector2f> GridPath;

/// <summary>
/// Serves as a tile-based graph for drawing on screen, and finding things like best path. 
/// </summary>
class GridSystem
{
public:

	/// <summary>
	/// Default Constructor 
	/// </summary>
	SLTH_API GridSystem();

	/// <summary>
	/// Initialze the grid from supplied data 
	/// </summary>
	/// <param name="size">Size of the grid, in tiles</param>
	/// <param name="position">The upper left starting position of the grid, in pixels</param>
	/// <param name="tileSize">the size of each tile, technically you can have 
	/// rectangular pixels but that will probably break something</param>
	/// <param name="tileSpacing">(Depricated) this won't acutally do anything</param>
	/// <returns></returns>
	SLTH_API bool Init(slth::Vector2f size, slth::Vector2f position, slth::Vector2f tileSize, float tileSpacing);

	/// <summary>
	/// Inisitalize the grid from an XML file
	/// </summary>
	/// <param name="filename"></param>
	SLTH_API void Init(const char* filename);

	/// <summary>
	/// Get the center tile, or as close to it as we can
	/// </summary>
	/// <returns>Reference the center-most tile</returns>
	SLTH_API GridTile& GetCenterTile();

	/// <summary>
	/// Grabs the tile at position (x, y), returns nullptr if there isn't one
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	SLTH_API slth::GridTile& GetTile(int x, int y);

	/// <summary>
	/// Gets the tile at the specified index
	/// </summary>
	/// <param name="index">The index of the tile you want</param>
	/// <returns>Refernce to the tile if one exists, InvalidTile if one does not</returns>
	SLTH_API slth::GridTile& GetTile(const size_t index);

	/// <summary>
	/// Get the screen position of the tile at (x, y)
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	SLTH_API Vector2f GetScreenPositionFromTile(int x, int y);

	/// <summary>
	/// Get the screen position of the tile at (x, y)
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	SLTH_API Vector2f GetScreenPositionFromTile(slth::Vector2f vec);

	/// <summary>
	/// Get tile at screen position
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	SLTH_API GridTile& GetTileAtScreenPosition(Vector2f pos);

	/// <summary>
	/// Gets the draw rect of the grid system 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	SLTH_API RectInt GetRect(int x, int y);

	/// <summary>
	/// Paint the tiles in a XXYY range, or just a single tile if endpoint is not supplied
	/// </summary>
	/// <param name="startX"></param>
	/// <param name="startY"></param>
	/// <param name="color"></param>
	/// <param name="weight"></param>
	/// <param name="endX"></param>
	/// <param name="endY"></param>
	/// <param name="identifier"></param>
	/// <param name="type"></param>
	SLTH_API void PaintTiles(int startX, int startY, Color color, float weight, int endX = -1, int endY = -1, u32 identifier = 0, u32 type = 0);

	/// <summary>
	/// Render the grid on screen
	/// </summary>
	/// <param name="pGraphics">A pointer to the graphics object</param>
	SLTH_API void Draw(slth::IGraphics* pGraphics);

	/// <summary>
	/// Finds the shortest path between two tiles using the A* algorithm
	/// </summary>
	/// <param name="startIndex">Staring tile index</param>
	/// <param name="destIndex">Ending tile index</param>
	/// <returns>A vector of tile indexes in order if a path is found; 
	/// An empty vector if no path can be found</returns>
	SLTH_API bool FindPathAStar(size_t startIndex, size_t destIndex, GridPath& pathBack, long long timeAllowed);

	/// <summary>
	/// Resume path in progress
	/// </summary>
	/// <returns></returns>
	SLTH_API bool Resume(GridPath& pathBack, long long timeAllowed);

	/// <summary>
	/// Resets the search data on the grid so that it can be pathed again
	/// </summary>
	SLTH_API void Reset();

	/// <summary>
	/// Dumps the current grid data to screen (or maybe XML file in the future)
	/// </summary>
	SLTH_API void OutputGridData();
	
	static constexpr float kImpassibleWeight = 10.f;
	static constexpr float kDiagonalWeight = 1.7f;

private:
	
	Vector2f m_size; 
	Vector2f m_position;
	Vector2f m_tileSize;
	u32 m_tileSpacing;
	Color m_backgroundColor;
	std::vector<GridTile> m_tiles;
	GridTile m_invalidTile;
	bool m_hidden; 

	// --------------------------------------------------------------------- //
	// Search Algorithm Stuff
	// --------------------------------------------------------------------- //

	OpenSet m_openSet; 
	GridTile* m_pCurrentNode;
	bool m_pathInProgress;
	size_t m_pathStartIndex;
	size_t m_pathEndIndex;
	bool m_usePureDistance;
	
	// private constants 
	static constexpr int kTileMarkerReduction = 3;

	/// <summary>
	/// Internal version of A* (contains the actual algorithm). This is necssary for 
	/// time-slicing the pathing. 
	/// </summary>
	/// <param name="pathBack"></param>
	/// <param name="timeAllowed"></param>
	/// <returns></returns>
	bool PathAStarInternal(GridPath& pathBack, long long timeAllowed);

	/// <summary>
	/// Creates tiles based on the data collected in Init()
	/// </summary>
	void CreateTiles();

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API std::vector<GridTile>& GetTiles() { return m_tiles; }
	
	SLTH_API Vector2f GetSize() { return m_size; }

	SLTH_API Color GetBackgroundColor() const { return m_backgroundColor; }

	SLTH_API void SetBackgroundColor(Color color) { m_backgroundColor = color; }

	SLTH_API GridTile& InvalidTile() { return m_invalidTile; }

	SLTH_API bool IsPathInProgress() const { return m_pathInProgress; }

	SLTH_API bool GetWeightOnlyMode() const { return m_usePureDistance; }

	SLTH_API void SetWeightOnlyMode(bool val) { m_usePureDistance = val; }

	SLTH_API void ToggleWeightMode() { m_usePureDistance = !m_usePureDistance; }

};
}