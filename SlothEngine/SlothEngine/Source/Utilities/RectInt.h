#pragma once
/** \file RectInt.h */

// Created by Myles Cardiff
#include <Common.h>
#include <SFML/Graphics.hpp>
#include <Utilities/Vector2f.h>
//! \namespace Sloth Engine
namespace slth
{
	/** \class RectInt */

	class RectInt
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		int left;
		int top;
		int right;
		int bottom;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //

		/** Default Constructor */
		SLTH_API RectInt()
			: left(0)
			, right(0)
			, top(0)
			, bottom(0)
		{
			//
		}

		/** Explicit Constructor */
		SLTH_API RectInt(int l, int t, int r, int b)
			: left(l)
			, top(t)
			, right(r)
			, bottom(b)
		{
			//
		}

		// addition of a vector
		SLTH_API RectInt& operator+=(const Vector2f& vec)
		{
			left += (int)vec.x;
			right += (int)vec.x;
			top += (int)vec.y;
			bottom += (int)vec.y;
			return *this;
		}
		// subtraction of a vector
		SLTH_API RectInt& operator-=(const Vector2f& vec)
		{
			left -= (int)vec.x;
			right -= (int)vec.x;
			top -= (int)vec.y;
			bottom -= (int)vec.y;
			return *this;
		}
		SLTH_API sf::IntRect GetSFMLRect() { 
			return sf::IntRect(left, top, right - left, bottom - top); 
		}
		SLTH_API int GetArea() { return GetWidth()* GetHeight(); }
		
		SLTH_API Vector2f GetCenter()
		{
			return { static_cast<float>(right - GetWidth() / 2), static_cast<float>(bottom - GetHeight() / 2) };
		}

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
		SLTH_API int GetHeight() { return bottom - top; }
		SLTH_API int GetWidth() { return right - left; }
		SLTH_API std::string ToString()
		{
			std::string output =  "{L" + std::to_string(left) 
								+ ", T" + std::to_string(top)
								+ ", R" + std::to_string(right)
								+ ", B: " + std::to_string(bottom) + "}";

			return output;
		}
		SLTH_API bool Overlaps(slth::RectInt& rectTwo)
		{
			// check if the rects are entirely above or below, left or right of each other
			if (right < rectTwo.left || left > rectTwo.right)
				return false;

			if (bottom < rectTwo.top || top > rectTwo.bottom)
				return false;

			return true;
		}


	};
}