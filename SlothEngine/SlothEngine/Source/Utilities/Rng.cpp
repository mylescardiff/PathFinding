#include "Rng.h"

using slth::Rng;

constexpr float kPrecision = 1'000'000.f;
constexpr float kMaxIntAsFloat = static_cast<float>(0Xffffffff);

void slth::Rng::Seed(u64 seed)
{
	m_seed[0] = seed;
	m_seed[1] = seed;
}


u64 slth::Rng::Rand()
{
	unsigned long long x = m_seed[0];
	const unsigned long long y = m_seed[1];
	m_seed[0] = y;
	x ^= x << 23; 
	m_seed[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
	return m_seed[1] + y;
}

unsigned int slth::Rng::RandIntInRange(unsigned int low, unsigned int high)
{
	unsigned int rnd = static_cast<unsigned int>(Rand());
	return low + (rnd % (high - low + 1));
}

float slth::Rng::RandFloat()
{
	return static_cast<float>(static_cast<unsigned int>(Rand()) / kMaxIntAsFloat);
	
}

float slth::Rng::RandFloatInRange(float low, float high)
{
	return low + (RandFloat() * (high - low));
}

bool slth::Rng::RandBool()
{
	int percentRand = RandIntInRange(0, 100);
	return percentRand >= 50;
		
}

slth::Vector2f slth::Rng::RandomNormalizedVector()
{
	return slth::Vector2f(RandFloat(), RandFloat());
}
