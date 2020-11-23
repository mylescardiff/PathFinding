#pragma once
#include <Common.h>
#include <Utilities\Vector2f.h>

/** \file Noise.h */
// Created by Myles Cardiff


namespace slth
{
/** \class Noise */
class Noise
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	SLTH_API constexpr Noise(u32 seed = 0) noexcept
		: m_seed(seed) 
	{ 
		//
	}

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/** Perlin Noise, taken from https://en.wikipedia.org/wiki/Perlin_noise */
	SLTH_API static float PerlinNoise(slth::Vector2f vec, u32 seed);

	SLTH_API static float GetPerlinNoise(slth::Vector2f vec, float maxX, float maxY, float noiseInputRange, u32 seed);

	SLTH_API static float GetOctavePerlinNoise(slth::Vector2f vec, float maxX, float maxY, float noiseInputRange, int numOctaves, float persistance, u32 seed);

	//-----------------------------------------------------------------------------------------------------------------
	// 1D Noise
	//-----------------------------------------------------------------------------------------------------------------
	SLTH_API static constexpr u32 Get1DNoise(int x, u32 seedOverride) noexcept
	{
		// This algorithm (called SquirrelNoise3) was originally written by Squirrel Eiserloh and was presented in 
		// his 2017 GDC talk titled Math for Game Programmers: Noise-Based RNG, which can be found here:
		// https://www.gdcvault.com/play/1024365/Math-for-Game-Programmers-Noise

		constexpr u32 kBitNoise1 = 0x68e31da4;
		constexpr u32 kBitNoise2 = 0xb5297a4d;
		constexpr u32 kBitNoise3 = 0x1b56c4e9;

		u32 mangledBits = static_cast<u32>(x);
		mangledBits *= kBitNoise1;
		mangledBits += seedOverride;
		mangledBits ^= (mangledBits >> 8);
		mangledBits *= kBitNoise2;
		mangledBits ^= (mangledBits << 8);
		mangledBits *= kBitNoise3;
		mangledBits ^= (mangledBits >> 8);
		return mangledBits;
	}
	
	SLTH_API constexpr u32 Get1DNoise(int x) const noexcept { return Get1DNoise(x, m_seed); }

	//-----------------------------------------------------------------------------------------------------------------
	// 2D Noise
	//-----------------------------------------------------------------------------------------------------------------
	SLTH_API static constexpr u32 Get2DNoise(int x, int y, u32 seedOverride) noexcept
	{
		constexpr unsigned int kPrime = 198491317;
		return Get1DNoise(x + (kPrime * y), seedOverride);
	}

	SLTH_API constexpr u32 Get2DNoise(int x, int y) const noexcept { return Get2DNoise(x, y, m_seed); }
	
	SLTH_API static constexpr float Get2DNoiseNormalized(int x, int y, u32 seedOverride) { return Normalize(Get2DNoise(x, y, seedOverride)); }

	//-----------------------------------------------------------------------------------------------------------------
	// 3D Noise
	//-----------------------------------------------------------------------------------------------------------------
	SLTH_API static constexpr u32 Get3DNoise(int x, int y, int z, u32 seedOverride) noexcept
	{
		constexpr u32 kPrime1 = 198491317;
		constexpr u32 kPrime2 = 6543989;
		return Get1DNoise(x + (kPrime1 * y) + (kPrime2 * z), seedOverride);
	}

	SLTH_API constexpr u32 Get3DNoise(int x, int y, int z) const noexcept { return Get3DNoise(x, y, z, m_seed); }
	

	// --------------------------------------------------------------------- //
	// Static Functions
	// --------------------------------------------------------------------- //

	/** Smooth Step, source: https://en.wikipedia.org/wiki/Smoothstep */
	SLTH_API static float SmoothStep(float x);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	u32 m_seed;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	

	/** Dot Grid Gradient */
	SLTH_API static float DotGridGradient(int ix, int iy, float x, float y, u32 seed);

	/* Normalize a u32 value to float */
	SLTH_API static constexpr float Normalize(u32 input) 
	{
		return (float)input / (float)std::numeric_limits<u32>::max();
	}


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	constexpr unsigned int GetSeed() const noexcept { return m_seed; }
	void SetSeed(unsigned int seed) noexcept { m_seed = seed; }
	


};
}