#pragma once
/** \file Color.h */
#include <Common.h>
// Created by Myles Cardiff


//! \namespace Sloth Engine
namespace slth
{
/** \class Color */

class Color
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	float m_red;
	float m_green;
	float m_blue;
	float m_opacity;

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	constexpr Color()
		: m_red(0)
		, m_green(0)
		, m_blue(0)
		, m_opacity(255.f)
	{}

	/** Explicit Constructor */
	constexpr Color(float r, float g, float b)
		: m_red(r)
		, m_green(g)
		, m_blue(b)
		, m_opacity(255.f)
	{}

	/** Explicit Constructor w/ alpha*/
	constexpr Color(float r, float g, float b, float alpha)
		: m_red(r)
		, m_green(g)
		, m_blue(b)
		, m_opacity(alpha)
	{}

	/// <summary>
	/// Equality operator
	/// </summary>
	/// <param name="other">The Color to compare this one to</param>
	/// <returns>True if both elements of the Vector2 are the same, false otherwise</returns>
	SLTH_API bool operator==(const Color& other) const
	{
		return m_red == other.m_red && m_green == other.m_green && m_blue == other.m_blue;
	}

	/// <summary>
	/// Inequality operator
	/// </summary>
	/// <param name="other">The Vector2 to compare this one to</param>
	/// <returns>False if both elements of the Vector2 are the same, True otherwise</returns>
	SLTH_API bool operator!=(const Color& other) const
	{
		return !(*this == other);
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

	static constexpr slth::Color White() { return Color( 255.f, 255.f, 255.f); }
	static constexpr slth::Color Black() { return Color(0.f, 0.f, 0.f); }
	static constexpr slth::Color Red() { return Color(255.f, 0.f, 0.f); }
	static constexpr slth::Color LightRed() { return Color(255.f, 147.f, 147.f); }
	static constexpr slth::Color LightYellow() { return Color(255.f, 246.f, 147.f); }
	static constexpr slth::Color Orange() {	return Color(255.f, 165.f, 0.f); }
	static constexpr slth::Color LightBlue() { return Color(147.f, 203.f, 255.f); }
	static constexpr slth::Color LightPurple() { return Color(245.f, 176.f, 254.f); }
	static constexpr slth::Color Blue() { return Color(0.f, 0.f, 255.f); }
	static constexpr slth::Color Green() { return Color(102.f, 204.f, 1.f); }
	static constexpr slth::Color LightGreen() { return Color(102, 255, 102.f); }
	static constexpr slth::Color DarkGreen() { return Color(51.f, 102.f, 0.f); }
	static constexpr slth::Color DarkGray() { return Color(65.f, 65.f, 65.f); }
	static constexpr slth::Color MediumGray() { return Color(130.f, 130.f, 130.f); }
	static constexpr slth::Color LightGray() { return Color(205.f, 205.f, 205.f); }
	static constexpr slth::Color Beige() { return Color(202.f, 179.f, 136.f); }
	static constexpr slth::Color DarkBeige() { return Color(153.f, 102.f, 51.f); }

};
}