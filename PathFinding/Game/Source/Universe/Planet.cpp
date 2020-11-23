#include "Planet.h"
#include <Utilities/Noise.h>
#include <Utilities/Color.h>
#include <Utilities/Utilities.h>
#include <Universe/Star.h>
#include <Graphics/SFMLGraphics.h>


Planet::Planet(std::string& name, PlanetType type, float radius, float orbitalDistance, slth::Vector2 positionOnScreen, u32 planetSeed)
	: m_name(name)
	, m_type(type)
	, m_radius(radius)
	, m_orbitalDistance(orbitalDistance)
	, m_onScreenPosition(positionOnScreen)
	, m_planetSeed(planetSeed)
	, m_waterLevel(0.f)
	
{
	//
}


void Planet::GenerateBiomes(size_t starTypeIndex)
{
	const Star::StarData& starData = Star::GetStarTypeData(starTypeIndex);

	// establishing a new rng here based on the planet seed so they it will persist
	slth::Rng rng;
	rng.Seed(m_planetSeed);

	// set up tiles for the planet
	int mapSize = (int)m_radius * 2;
	int numTiles = mapSize * mapSize;

	slth::Noise noiseGen;
	noiseGen.SetSeed((unsigned int)m_planetSeed);

	if (m_type == PlanetType::kRocky)
	{

		// choose a random soil type for rocky planets
		size_t baseColorIndex = static_cast<size_t>(rng.RandIntInRange(0, static_cast<int>(SoilElements::kNumSoilElements) - 1));
	
		GenerateRocky(s_kSoilColors[baseColorIndex], noiseGen, rng, starData.m_goldilocksMin, starData.m_golidlicksMax, rng.RandFloatInRange(0.25f, 0.7f));
	}
	else
	{
		// choose a random soil type for rocky planets
		size_t baseColorIndex = static_cast<size_t>(rng.RandIntInRange(0, static_cast<int>(GasTypes::kNumAtmos) - 1));

		GenerateGasGiant(s_kGasColors[baseColorIndex], noiseGen);
		
	}
}

void Planet::GenerateGasGiant(slth::Color baseColor, slth::Noise& noiseGen)
{
	slth::Color gasColors[kNumGasStripes];
	GetColorArray(baseColor, gasColors, kNumGasStripes);

	int mapSize = (int)m_radius * 2;
	slth::Vector2 centerTile = { m_radius, m_radius };

	m_planetImage.create(mapSize, mapSize, sf::Color(0, 0, 0, 0));

	for (int y = 0; y < (int)m_radius * 2; ++y)
	{
		// get coords (1 Dimensinoal)
		slth::Vector2 coords = { 0.f, (float)y };

		// get noise & color
		float colorNoise = slth::Math::Normalize(noiseGen.GetOctavePerlinNoise(coords, (float)m_radius * 2.f, (float)mapSize, 5.0f, 3, 1.0f, (u32)m_planetSeed), -0.2f, 0.32f); //TODO: Magic Numbers
		
		for (int x = 0; x < (int)m_radius * 2; ++x)
		{
			slth::Color tileColor = gasColors[static_cast<size_t>(colorNoise * static_cast<float>(kNumGasStripes))];
			slth::Vector2 pixelCoords((float)x, (float)y);
			if (pixelCoords.DistanceTo(centerTile) > m_radius)
			{
				tileColor.m_opacity = 0;
			}
			else
			{
				int test = 1;
				test = 2;
			}
			m_planetImage.setPixel(
				(unsigned int)x,
				(unsigned int)y,
				sf::Color((sf::Uint8)tileColor.m_red, (sf::Uint8)tileColor.m_green, (sf::Uint8)tileColor.m_blue, (sf::Uint8)tileColor.m_opacity )
			);
		}

	}
}

void Planet::GenerateRocky(slth::Color baseColor, slth::Noise& noiseGen, slth::Rng& rng, float goldLocksMin, float goldiLocksMax, float waterLevel)
{
	int mapSize = (int)m_radius * 2;
	int numTiles = mapSize * mapSize;
	slth::Color soilColors[kNumColorShades];
	GetColorArray(baseColor, soilColors, kNumColorShades);

	m_waterLevel = waterLevel;

	unsigned int numColors = (unsigned int)numTiles * 4;
	
	m_planetImage.create(mapSize, mapSize, sf::Color(0, 0, 0, 0));

	slth::Vector2 centerTile = { m_radius, m_radius };

	for (int i = 0; i < numTiles; ++i)
	{
		// get coords
		slth::Vector2 coords = slth::Math::CoordsFromIndex(i, mapSize);

		// get noise & color
		float heightNoise = slth::Math::Normalize(noiseGen.GetOctavePerlinNoise(coords, (float)mapSize, (float)mapSize, 2.0f, 3, 1.0f, (u32)m_planetSeed), -0.2f, 0.32f);
		float heightIndex = heightNoise * static_cast<float>(kNumColorShades);
		slth::Color tileColor = soilColors[static_cast<size_t>(heightIndex)];

		// place water / ice / nothing based on goldilocks zone
		if (heightNoise < m_waterLevel)
		{
			if (m_orbitalDistance < goldLocksMin)
			{
				// water would burn off leave the tile as it is
			}
			else if (m_orbitalDistance > goldiLocksMax)
			{
				// to0 cold, water would be ice
				tileColor = slth::Color::White();
			}
			else
			{
				// goldilocks zone, place liquid water
				tileColor = slth::Color::Blue();
			}
		}

		if (coords.DistanceTo(centerTile) > m_radius)
		{
			tileColor.m_opacity = 0;
		}

		m_planetImage.setPixel(
			(unsigned int)coords.x,
			(unsigned int)coords.y,
			sf::Color((sf::Uint8)tileColor.m_red, (sf::Uint8)tileColor.m_green, (sf::Uint8)tileColor.m_blue, (sf::Uint8)tileColor.m_opacity)
		);
	}
}

void Planet::Draw(slth::IGraphics* pGraphics, float expandFactor)
{
	slth::Vector2 drawPosition = m_onScreenPosition;
	if (expandFactor > 1.05f)
	{
		drawPosition = { 50.f, 20.f };
	}
	else
	{
		// write the name
		slth::Vector2 textPos = m_onScreenPosition + slth::Vector2(0.f, -20.f);
		pGraphics->DrawText(m_name.c_str(), textPos, 16, slth::Color::White());
	}

	slth::RectInt drawRect(
		(int)drawPosition.x,
		(int)drawPosition.y,
		(int)drawPosition.x + (int)m_radius * 2 * (int)expandFactor,
		(int)drawPosition.y + (int)m_radius * 2 * (int)expandFactor
	);

	slth::RectInt textureRect(
		0, 0, (int)m_radius * 2, (int)m_radius * 2
	);

	pGraphics->DrawTexture(m_name.c_str(), drawRect, textureRect, false, 0.f, { 0.f, 0.f }, false, expandFactor);
	
}


void Planet::GetColorArray(slth::Color baseColor, slth::Color* array, float numColors)
{

	for (int i = 0; i < numColors; ++i)
	{
		float adjustmentIndex = i - ((float)numColors / 2);
		float adjustment = kColorRange / numColors * adjustmentIndex;
		array[i] = slth::Color(
			std::clamp(baseColor.m_red + adjustment, 0.f, 255.f),
			std::clamp(baseColor.m_green + adjustment, 0.f, 255.f),
			std::clamp(baseColor.m_blue + adjustment, 0.f, 255.f)
		);
	}
}


