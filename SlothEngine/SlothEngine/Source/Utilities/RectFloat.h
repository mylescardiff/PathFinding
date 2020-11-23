#pragma once
/** \file RectFloat.h */

// Created by Myles Cardiff
#include <Common.h>
#include <SFML/Graphics.hpp>
//! \namespace Sloth Engine
namespace slth
{
	/** \class RectFloat */

	class RectFloat
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		float left;
		float top;
		float right;
		float bottom;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //

		/** Default Constructor */
		SLTH_API RectFloat()
			: left(0)
			, right(0)
			, top(0)
			, bottom(0)
		{
			//
		}

		/** Explicit Constructor */
		SLTH_API RectFloat(float l, float t, float r, float b)
			: left(l)
			, top(t)
			, right(r)
			, bottom(b)
		{
			//
		}

		SLTH_API sf::FloatRect GetSFMLRect() { return sf::FloatRect(left, top, right - left, bottom - top); }



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
		SLTH_API float GetHeight() { return bottom - top; }
		SLTH_API float GetWidth() { return right - left; }

	};
}