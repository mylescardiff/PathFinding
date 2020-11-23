#include "Noise.h"
#include <Utilities/Vector2f.h>
#include <algorithm>
#include <Utilities/Rng.h>

using slth::Noise;


float slth::Noise::DotGridGradient(int ix, int iy, float x, float y, u32 seed)
{
	Vector2f gradientVec(
		Normalize(Get3DNoise(ix, iy, 0, seed)),
		Normalize(Get3DNoise(ix, iy, 1, seed))
	);

	Vector2f distanceVec(x - (float)ix, y - (float)iy);

	return distanceVec.DotProduct(distanceVec, gradientVec);
}

float slth::Noise::PerlinNoise(slth::Vector2f vec, u32 seed)
{
	// determine grid cell coordinates
	int x0 = (int)vec.x;
	int x1 = x0 + 1;
	int y0 = (int)vec.y;
	int y1 = y0 + 1;

	float sx = vec.x - (float)x0;
	float sy = vec.y - (float)y0;
	
	float n0 = DotGridGradient(x0, y0, vec.x, vec.y, seed);
	float n1 = DotGridGradient(x1, y0, vec.x, vec.y, seed);
	float ix0 = Vector2f::Lerp({ n0, n1 }, sx);

	n0 = DotGridGradient(x0, y1, vec.x, vec.y, seed);
	n1= DotGridGradient(x1, y1, vec.x, vec.y, seed);
	float ix1 = Vector2f::Lerp({ n0, n1 }, sx);

	float value = Vector2f::Lerp({ ix0, ix1 }, sy);

	return value;
}


float slth::Noise::GetPerlinNoise(slth::Vector2f vec, float maxX, float maxY, float noiseInputRange, u32 seed)
{
	float gridX = (vec.x / maxX) * noiseInputRange;
	float gridY = (vec.y / maxY) * noiseInputRange;
	return PerlinNoise({ gridX, gridY }, seed);
}

float slth::Noise::GetOctavePerlinNoise(slth::Vector2f vec, float maxX, float maxY, float noiseInputRange, int numOctaves, float persistance, u32 seed)
{
	if (numOctaves <= 0)
		return 0.f;

	float noise = 0.f;

	slth::Rng rng;
	rng.Seed(seed);

	float currentAmplitude = 1.f;
	float totalAmplitude = 0.f;

	for (int i = 0; i < numOctaves; ++i)
	{
		totalAmplitude += currentAmplitude;

		noise += GetPerlinNoise(vec, maxX, maxY, noiseInputRange, (u32)rng.Rand()) * currentAmplitude;

		//vec = vec * persistance;
		currentAmplitude *= persistance;
		noiseInputRange *= 2;

	}
	noise /= totalAmplitude;
	return noise;

}


float slth::Noise::SmoothStep(float x)
{
	// Scale, bias and saturate x to 0 to 1 range
	x = std::clamp(x, 0.0f, 1.0f);
	
	// Evaluate polynomial
	return x * x * x * (x * (x * 6 - 15) + 10);
}



