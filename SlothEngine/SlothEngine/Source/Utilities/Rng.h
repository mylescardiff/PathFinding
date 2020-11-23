/** \file Rng.h */
#pragma once
#include <Common.h>
#include <Utilities/Vector2f.h>

//! \namespace Sloth Engine
namespace slth
{
/** \class Rng */
/** Random Number Generator, Uses XorShift 128 */
class Rng
{
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	
	u64 m_seed[2];

public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	/** Seed the RNG with something psuedo random, like time e.g. */
	SLTH_API void Seed(u64 seed);
	
	/** Gets a random unsigned long long */
	SLTH_API unsigned long long Rand();

	/** Gets a random int within the specified range */
	SLTH_API unsigned int RandIntInRange(unsigned int low, unsigned int high);

	/** Gets a random float between 0 and 1*/
	SLTH_API float RandFloat();

	/** Gets a random float in the specified range */
	SLTH_API float RandFloatInRange(float low, float high);
	
	/* Gets a random true / false (coin flip) **/
	SLTH_API bool RandBool();

	SLTH_API slth::Vector2f RandomNormalizedVector();

};
}