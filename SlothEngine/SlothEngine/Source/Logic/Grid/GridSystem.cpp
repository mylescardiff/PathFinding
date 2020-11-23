#include "GridSystem.h"
#include <Logic/Grid/GridTile.h>
#include <Logic/Actor.h>
#include <Logic/ActorFactory.h>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/RenderBoxComponent.h>
#include <Utilities/RectInt.h>
#include <Logic/ActorFactory.h>
#include <Common.h>
#include <Utilities/Utilities.h>
#include <Graphics/IGraphics.h>
#include <queue>
#include <iostream>
#include <chrono>
#include <thread>

using slth::GridSystem;
using namespace std::chrono_literals;

static const float root2 = std::sqrt(2.f);

GridSystem::GridSystem()
	: m_tileSpacing(0)
	, m_hidden(true)
	, m_openSet(nodePriorityFunc)
	, m_pCurrentNode(nullptr)
	, m_usePureDistance(false)
	, m_pathEndIndex(0)
	, m_pathStartIndex(0)
	, m_backgroundColor(Color(0.f, 0.f, 0.f))
	, m_pathInProgress(false)
{
	m_invalidTile.SetType(GridTile::kInvalidTile);
}

bool slth::GridSystem::Init(slth::Vector2f size, slth::Vector2f position, slth::Vector2f tileSize, float tileSpacing)
{
	m_size = size;
	m_position = position;
	m_tileSize = tileSize;
	m_tileSpacing = (u32)tileSpacing;
	m_backgroundColor = Color(0.f, 0.f, 0.f, 0.f);

	CreateTiles();
	
	return true;
}

void slth::GridSystem::Init(const char* filename)
{
	using namespace tinyxml2;

	XMLDocument doc;
	XMLError error = doc.LoadFile(filename);
	if (error != XML_SUCCESS)
	{
		_LOGE("XML file load failed");
	}

	XMLElement* pRoot = doc.RootElement();
	XMLElement* pTileElement = pRoot->FirstChildElement("Tile");

	m_tileSize.x = pRoot->FloatAttribute("tile-size");
	m_tileSize.y = m_tileSize.x;

	m_position.x = pRoot->FloatAttribute("x");
	m_position.x = pRoot->FloatAttribute("y");

	m_backgroundColor.m_red = pRoot->FloatAttribute("background-r");
	m_backgroundColor.m_green = pRoot->FloatAttribute("background-g");
	m_backgroundColor.m_blue = pRoot->FloatAttribute("background-b");

	m_size.x = pRoot->FloatAttribute("size-x");
	m_size.y = pRoot->FloatAttribute("size-y");

	CreateTiles();

	PaintTiles(0, 0, m_backgroundColor, 1.f, (int)m_size.x, (int)m_size.y, 0, 0);

	while (pTileElement)
	{
		Color color;
		color.m_red = pTileElement->FloatAttribute("r");
		color.m_green = pTileElement->FloatAttribute("g");
		color.m_blue = pTileElement->FloatAttribute("b");
		float weight = pTileElement->FloatAttribute("weight");
		int index = pTileElement->IntAttribute("index");

		// create and place the tile
		m_tiles[index].SetWeight(weight);
		m_tiles[index].SetColor(color);
		m_tiles[index].SetIndex(index);

		pTileElement = pTileElement->NextSiblingElement("Tile");
	}

}


slth::GridTile& slth::GridSystem::GetCenterTile()
{
	if (m_tiles.size() == 0)
		return m_invalidTile;

	return GetTile((u8)m_size.x / 2, (u8)m_size.y / 2);
}

slth::GridTile& slth::GridSystem::GetTile(int x, int y)
{
	// check for off map negatives
	if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
		return m_invalidTile;

	size_t index = Vector2f::IndexFromPosition(x, y, (int)m_size.x);
	return GetTile(index);
}

slth::GridTile& slth::GridSystem::GetTile(const size_t index)
{
	if (index < m_tiles.size())
	{
		return m_tiles[index];
	}
	else
	{
		return m_invalidTile;
	}
}

slth::Vector2f slth::GridSystem::GetScreenPositionFromTile(int x, int y)
{
	return Vector2f(
		m_position.x + (m_tileSize.x + m_tileSpacing) * x,
		m_position.y + (m_tileSize.y + m_tileSpacing) * y
	);
}

slth::Vector2f slth::GridSystem::GetScreenPositionFromTile(slth::Vector2f vec)
{
	return GetScreenPositionFromTile((int)vec.x, (int)vec.y);
}

slth::GridTile& slth::GridSystem::GetTileAtScreenPosition(Vector2f pos)
{
	Vector2f offsetPos = pos - m_position;
	offsetPos = offsetPos / m_tileSize.x;

	size_t tileIndex = (size_t)slth::Vector2f::IndexFromPosition((int)offsetPos.x, (int)offsetPos.y, (int)m_size.x);

	if (tileIndex < m_tiles.size())
	{
		return m_tiles[tileIndex];
	}

	return m_invalidTile;
}

slth::RectInt slth::GridSystem::GetRect(int x, int y)
{
	Vector2f screenCoords = GetScreenPositionFromTile(x, y);
	return RectInt(
		static_cast<int>(screenCoords.x),
		static_cast<int>(screenCoords.y),
		static_cast<int>(screenCoords.x + m_tileSize.x),
		static_cast<int>(screenCoords.y + m_tileSize.y)
	);
}

void slth::GridSystem::PaintTiles(int startX, int startY, Color color, float weight, int endX, int endY, u32 identifier, u32 type)
{
	// if end x and y aren't supplied, assume they are just painting a single tile in that direction
	if (endX == -1)
		endX = startX;

	if (endY == -1)
		endY = startY;

	Vector2f cursorPos((float)startX, (float)startY);

	while (cursorPos.x <= endX)
	{
		while (cursorPos.y <= endY)
		{
			// paint
			GridTile& pTile = GetTile(static_cast<int>(cursorPos.x), static_cast<int>(cursorPos.y));
			if (pTile.GetType() != GridTile::kInvalidTile && cursorPos.x >= 0 && cursorPos.y >= 0 && cursorPos.x < m_size.x && cursorPos.y < m_size.y)
			{
				pTile.SetColor(color);
				pTile.SetWeight(weight);
				pTile.SetType(type);
			}
			++cursorPos.y;
		}
		++cursorPos.x;
		cursorPos.y = static_cast<float>(startY);
	}
}

void slth::GridSystem::Draw(slth::IGraphics* pGraphics)
{
	// draw the background, if its anything but black
	if (m_backgroundColor != slth::Color::Black()) 
	{
		slth::RectInt bgRec = {
				(int)m_position.x,
				(int)m_position.y,
				(int)m_position.x + (int)m_tileSize.x * (int)m_size.x,
				(int)m_position.y + (int)m_tileSize.y * (int)m_size.y
		};

		pGraphics->DrawRect(bgRec, m_backgroundColor, m_backgroundColor, 0.f, 0.f);
	}

	for (GridTile& tile : m_tiles)
	{
		if (m_backgroundColor != tile.GetColor())
		{
			Vector2f screenPos = GetScreenPositionFromTile((int)tile.GetCoordinates().x, (int)tile.GetCoordinates().y);
			slth::RectInt drawRect = {
				(int)screenPos.x,
				(int)screenPos.y,
				(int)screenPos.x + (int)m_tileSize.x,
				(int)screenPos.y + (int)m_tileSize.y
			};

			pGraphics->DrawRect(drawRect, tile.GetColor(), tile.GetColor(), 0.f, 0.f);
		}
#if _DEBUG
		if (tile.GetVisited() || tile.GetGScore() != GridTile::kInfinity || tile.GetIndex() == m_pathEndIndex)
		{
			Vector2f screenPos = GetScreenPositionFromTile((int)tile.GetCoordinates().x, (int)tile.GetCoordinates().y);
			
			slth::RectInt drawRect = {
				(int)screenPos.x + (int)m_tileSize.x / kTileMarkerReduction,
				(int)screenPos.y + (int)m_tileSize.y / kTileMarkerReduction,
				(int)screenPos.x + (int)m_tileSize.x - (int)m_tileSize.x / kTileMarkerReduction,
				(int)screenPos.y + (int)m_tileSize.y  - (int)m_tileSize.y / kTileMarkerReduction
			};

			slth::Color markerColor = slth::Color::White();
			if (tile.GetIsInPath())
			{
				markerColor = Color::Red();
			}
			else if (!tile.GetVisited())
			{
				markerColor = slth::Color::Black();
			}
		
			pGraphics->DrawRect(drawRect, markerColor, slth::Color::Black(), 0.f, 0.f);

		}
#endif
	}
#if _DEBUG
	// draw gridlines
	for (int y = 0; y < (int)m_size.x; ++y) {
		Vector2f top = { (float)y * m_tileSize.x, 0.f, };
		Vector2f bottom = { (float)y * m_tileSize.x, m_size.y * m_tileSize.y };
		pGraphics->DrawLine(top, bottom, slth::Color::White());
	}
	for (int x = 0; x < (int)m_size.y; ++x) {
		Vector2f left = { 0.f, m_tileSize.y * (float)x };
		Vector2f right = { m_size.x * m_tileSize.x, (float)x * m_tileSize.x };
		pGraphics->DrawLine(left, right, slth::Color::White());

	}
#endif
}

bool slth::GridSystem::FindPathAStar(size_t startIndex, size_t destIndex, GridPath& pathBack, long long timeAllowed)
{
	// reset the grid, path reference has been set
	Reset();

	// don't bother trying to get to an impassible tile
	if (m_tiles[destIndex].GetWeight() >= kImpassibleWeight)
		return true;
	
	m_pathStartIndex = startIndex;
	m_pathEndIndex = destIndex;
	m_pathInProgress = true;

	// place the start node in the open set
	m_tiles[m_pathStartIndex].SetScores(0.f, m_tiles[m_pathStartIndex].GetCoordinates().DistanceTo(m_tiles[m_pathEndIndex].GetCoordinates()));
	m_openSet.push(&m_tiles[m_pathStartIndex]);

	return PathAStarInternal(pathBack, timeAllowed);
}


bool slth::GridSystem::PathAStarInternal(GridPath& pathBack, long long timeAllowed)
{
	// note the time for slicing
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

	// store the destination vector for faster calc
	Vector2f destVector = m_tiles[m_pathEndIndex].GetCoordinates();

	while (!m_openSet.empty())
	{
		GridTile* m_pCurrentNode = m_openSet.top();
		
		// check for goal
		if (m_pCurrentNode->GetIndex() == m_pathEndIndex)
		{
			// we've found the goal, reconstruct the path
			GridTile* pLastTileInPath = &m_tiles[m_pathEndIndex];
			while (pLastTileInPath->GetIndex() != m_pathStartIndex)
			{
				Vector2f waypoint = GetScreenPositionFromTile(pLastTileInPath->GetCoordinates());
				pathBack.push_back(waypoint);

				if (pLastTileInPath->GetPredecessor() == GridTile::kInvalidTile)
					break;

				pLastTileInPath->SetIsInPath(true);
				pLastTileInPath = &m_tiles[pLastTileInPath->GetPredecessor()];
			}
			m_tiles[m_pathEndIndex].SetIsInPath(true);
			std::reverse(std::begin(pathBack), std::end(pathBack));

			m_pathInProgress = false;
			return true;
		}

		m_openSet.pop();
		m_pCurrentNode->SetVisited(true);

		std::vector<int> neigbors = Math::GetNeighbors((int)m_pCurrentNode->GetIndex(), (int)m_size.x, (int)m_size.y);
		for (int neighborIndex : neigbors)
		{
			// prevent out of range error, there's possibly a bug in my GetNeighbors function 
			if (neighborIndex >= m_tiles.size())
				continue;

			GridTile* pNeighborNode = &m_tiles[neighborIndex];

			// don't add tiles that are past the threshhold for "Impassible"
			if (pNeighborNode->GetWeight() >= kImpassibleWeight || pNeighborNode->GetVisited())
				continue;
		
			// approximate distance to next tile
			float dist = 1.f;
			if (m_pCurrentNode->GetCoordinates().x != pNeighborNode->GetCoordinates().x &&
				m_pCurrentNode->GetCoordinates().y != pNeighborNode->GetCoordinates().y)
			{
				dist = root2; 
			}

			float tenativeGScore; 
			if (!m_usePureDistance)
			{
				// if this is diagonal, artificially change the weight
				if (dist > 1.f)
					dist = kDiagonalWeight;
			}
			
			tenativeGScore = m_pCurrentNode->GetGScore()
				+ dist
				* pNeighborNode->GetWeight();

			if (tenativeGScore < m_tiles[neighborIndex].GetGScore())
			{
				// this path seems better, but heuristic may detemine
				// the order in the open set to be different later
				pNeighborNode->SetPredecessor(m_pCurrentNode->GetIndex());
				pNeighborNode->SetScores(
					tenativeGScore,
					tenativeGScore + pNeighborNode->GetCoordinates().DistanceTo(destVector)
				);

				if (!pNeighborNode->GetVisited())
					m_openSet.push(pNeighborNode);

				//accumulate time & check if we need to bail early
				std::chrono::steady_clock::time_point timeNow = std::chrono::steady_clock::now();
				long long seconds = (long long)std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - startTime).count();
				if (seconds > timeAllowed)
				{
					_LOGW("Pathing Time Exceeded: " + std::to_string(seconds) + " seconds");
					m_pathInProgress = true;
					return false; // false = not finished pathing
				}
			}

			
		}

	
	}

	_LOGW("Cannot find path to target");

	// no path found
	m_pathInProgress = false;
	return true;
}

void slth::GridSystem::CreateTiles()
{
	int index = 0;
	for (int y = 0; y < (int)m_size.y; ++y)
	{
		for (int x = 0; x < (int)m_size.x; ++x)
		{
			// create and place the tile
			GridTile pTile = GridTile(x, y, 1.f, m_backgroundColor);
			pTile.SetIndex(index);
			m_tiles.push_back(pTile);
			++index;
		}
	}
}

bool slth::GridSystem::Resume(GridPath& pathBack, long long timeAllowed)
{
	return PathAStarInternal(pathBack, timeAllowed);
}

void slth::GridSystem::Reset()
{
	m_pathInProgress = false;
	m_pCurrentNode = nullptr;

	// is there really no better way to do this?
	while (!m_openSet.empty())
	{
		m_openSet.pop();
	}
	for (GridTile& tile : m_tiles)
	{
		tile.Reset();
	}
}



void slth::GridSystem::OutputGridData()
{
	
	for (GridTile& tile : m_tiles)
	{
		if (tile.GetColor() != m_backgroundColor)
		{
			std::string outputElement = "<Tile index = '" + std::to_string(tile.GetIndex()) + "' ";
			outputElement += "r='" + std::to_string(tile.GetColor().m_red) + "' ";
			outputElement += "g ='" + std::to_string(tile.GetColor().m_green) + "' ";
			outputElement += "b ='" + std::to_string(tile.GetColor().m_blue) + "' ";
			outputElement += "weight ='" + std::to_string(tile.GetWeight()) + "' />";

			std::cout << outputElement << std::endl;
		}
		

	}

}



