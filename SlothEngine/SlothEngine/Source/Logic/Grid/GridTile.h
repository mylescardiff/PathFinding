#pragma once
/** \file GridTile.h */
// Created by Myles Cardiff

#include <Utilities/Color.h>
#include <Utilities/Vector2f.h>
#include <Logic/Actor.h>
#include <Logic/Components/RenderBoxComponent.h>

namespace slth
{
	class GridSystem;

/// <summary>
/// Represents a single tile in the grid system
/// </summary>
class GridTile
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	SLTH_API GridTile();
	
	/// <summary>
	/// Explicit Constructor
	/// </summary>
	/// <param name="x">X position</param>
	/// <param name="y">Y position</param>
	/// <param name="weight">Weight</param>
	/// <param name="color">Color</param>
	SLTH_API GridTile(int x, int y, float weight, Color color);

	/// <summary>
	/// Gets the Fscore, but includes a weight of the tiles in the calculation
	/// </summary>
	/// <returns></returns>
	SLTH_API float GetFScore() const;

	SLTH_API void Reset();

	// constants
	static constexpr float kInfinity = std::numeric_limits<float>::max();
	static constexpr u32 kInvalidTile = std::numeric_limits<u32>::max();

private:
	
	size_t m_index;
	Vector2f m_coordinates;
	Color m_color; 
	Actor* m_pActor;
	u32 m_type;
	
	// search-related fields
	size_t m_predecessor;
	float m_weight;
	float m_gScore;
	float m_fScore;
	bool m_visited;
	bool m_isInPath;
	
	
public:

	SLTH_API float GetWeight() const { return m_weight; }
	SLTH_API void SetWeight(float weight) { m_weight = weight; }
	SLTH_API Vector2f GetCoordinates() { return m_coordinates; }
	SLTH_API void SetColor(Color color) { m_color = color; }
	SLTH_API u32 GetType() const { return m_type; }
	SLTH_API Color GetColor() const { return m_color; }
	SLTH_API size_t GetIndex() const { return m_index; }
	SLTH_API void SetIndex(size_t index) { m_index = index; }
	SLTH_API void SetScores(float gScore, float fScore) { m_gScore = gScore; m_fScore = fScore;  }
	SLTH_API float GetGScore() const { return m_gScore; }
	
	SLTH_API void SetPredecessor(size_t index) { m_predecessor = index; }
	SLTH_API size_t GetPredecessor() const { return m_predecessor; }
	SLTH_API void SetType(u32 type) { m_type = type; }
	SLTH_API bool GetVisited() const { return m_visited; }
	SLTH_API void SetVisited(bool visited) { m_visited = visited; }
	SLTH_API bool GetIsInPath() const { return m_isInPath; }
	SLTH_API void SetIsInPath(bool isInPath) { m_isInPath = isInPath; }


};
}