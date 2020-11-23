#pragma once
#include <Common.h>
#include <Utilities/Vector2f.h>
#include <vector>

namespace slth
{
	class Math
	{
		public:

		SLTH_API static float Normalize(float input, float max, float min)
		{
			return (input - min) / (max - min);
		}
		
		//---------------------------------------------------------------
		// Coordinate Conversion Methods
		//---------------------------------------------------------------

		SLTH_API static int IndexFromCoords(int x, int y, int width)
		{
			return (y * width) + x;
		}

		SLTH_API static Vector2f CoordsFromIndex(int index, int width)
		{
			return Vector2f(
				static_cast<float>(index % width),
				static_cast<float>(index / width)
			);
		}
		SLTH_API static std::vector<int> GetNeighbors(int index, int width, int height)
		{
			Vector2f coords = CoordsFromIndex(index, width);
			return GetNeighbors((int)coords.x, (int)coords.y, width, height);
		}
		SLTH_API static std::vector<int> GetNeighbors(int xPos, int yPos, int width, int height)
		{
			std::vector<int> cells;
			cells.reserve(8);

			for (int y = yPos - 1; y <= yPos + 1; ++y)
			{
				for (int x = xPos - 1; x <= xPos + 1; ++x)
				{
					// don't return center tile
					if (x == xPos && y == yPos)
						continue;

					// don't return off-board cells
					if (x < 0 || x >= width || y < 0 || y >= height)
						continue;

					cells.emplace_back(IndexFromCoords(x, y, width));

				}
			}

			return cells;
		}

		/*SLTH_API static int LeftNeighborIndex(int index, int width)
		{
			Vector2 coords = CoordsFromIndex(index, width);
			--coords.x;
			return IndexFromCoords((int)coords.x, (int)coords.y, width);
		}

		SLTH_API static int RightNeighborIndex(int index, int width)
		{
			Vector2 coords = CoordsFromIndex(index, width);
			++coords.x;
			return IndexFromCoords((int)coords.x, (int)coords.y, width);
		}

		SLTH_API static int UpperNeighborIndex(int index, int width)
		{
			Vector2 coords = CoordsFromIndex(index, width);
			--coords.y;
			return IndexFromCoords((int)coords.x, (int)coords.y, width);
		}

		SLTH_API static int LowerNeighborIndex(int index, int width)
		{
			Vector2 coords = CoordsFromIndex(index, width);
			++coords.y;
			return IndexFromCoords((int)coords.x, (int)coords.y, width);
		}

		SLTH_API static int UpperRightNeighborIndex(int index, int width)
		{
			Vector2 coords = CoordsFromIndex(index, width);
			--coords.y;
			++coords.x;
			return IndexFromCoords((int)coords.x, (int)coords.y, width);
		}

		SLTH_API static int UpperLeftNeighborIndex(int index, int width)
		{
			Vector2 coords = CoordsFromIndex(index, width);
			--coords.y;
			--coords.x;
			return IndexFromCoords((int)coords.x, (int)coords.y, width);
		}

		SLTH_API static int LowerRightNeighborIndex(int index, int width)
		{
			Vector2 coords = CoordsFromIndex(index, width);
			++coords.y;
			++coords.x;
			return IndexFromCoords((int)coords.x, (int)coords.y, width);
		}

		SLTH_API static int LowerLeftNeighborIndex(int index, int width)
		{
			Vector2 coords = CoordsFromIndex(index, width);
			++coords.y;
			--coords.x;
			return IndexFromCoords((int)coords.x, (int)coords.y, width);
		}*/

		
	};

}