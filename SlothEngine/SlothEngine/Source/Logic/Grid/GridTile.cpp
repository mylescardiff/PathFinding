#include "GridTile.h"
#include <Utilities/RectInt.h>

using slth::GridTile;

GridTile::GridTile()
	: m_coordinates(Vector2f(0.f, 0.f))
	, m_pActor(nullptr)
	, m_weight(1.f)
	, m_color(Color(0.f, 0.f, 0.f))
	, m_gScore(kInfinity)
	, m_fScore(kInfinity)
	, m_index(0)
	, m_type(0)
	, m_predecessor(kInvalidTile)
	, m_visited(false)
	, m_isInPath(false)
{
	//
}

slth::GridTile::GridTile(int x, int y, float weight, Color color)
	: m_coordinates(Vector2f((float)x, (float)y))
	, m_pActor(nullptr)
	, m_color(color)
	, m_weight(weight)
	, m_gScore(kInfinity)
	, m_fScore(kInfinity)
	, m_predecessor(kInvalidTile)
	, m_type(0)
	, m_index(0)
	, m_visited(false)
	, m_isInPath(false)
{
	//
}

float slth::GridTile::GetFScore() const
{
	return m_fScore * m_weight;
}

void slth::GridTile::Reset()
{
	m_fScore = kInfinity;
	m_gScore = kInfinity;
	m_predecessor = kInvalidTile;
	m_isInPath = false;
	m_visited = false;
}




