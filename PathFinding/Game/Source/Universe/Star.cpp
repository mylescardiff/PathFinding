#include "Star.h"
#include <PCG/NameGenerator.h>
#include <Utilities/Noise.h>
#include <Utilities/Utilities.h>

// constants 
constexpr static int kMaxPlanets = 6;
constexpr static int kMinPlanets = 1;
constexpr static float kRockyChance = 0.6f;
constexpr static float kRockyGasDiff = 15;
constexpr static float kGasGiantChance = 0.4f;
constexpr static float kMinPlanetSize = 10.f;
constexpr static float kMaxPlanetSize = 80.f;
constexpr static float kPlanetDistance = 250.f;
constexpr static const char* s_kRomanNumerals[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X" };
constexpr static float kChangeOfNamedPlanet = 0.2f;

Star::Star(StarType type, slth::Vector2 position, int cellIndex)
	: m_position(position)
	, m_type(type)
	, m_cellIndex(cellIndex)
	, m_name("Unnamed Star")
	, m_hasMClassPlanet(false)
	, m_questNodeId(0)
{
	//
}

Star::~Star()
{
	//
}

Star::StarType Star::DetermineType(slth::Rng& rng)
{
	float roll = rng.RandFloat();
	float sumOfWeights = 1.f;

	for (int i = 0; i < static_cast<int>(StarType::kNumTypes); ++i)
	{
		roll -= s_starDataList[i].m_chanceOfAppearing;
		if (roll <= 0.f)
		{
			return static_cast<StarType>(i);
		}
	}

	// should never get here
	return StarType::kMainSequence;
}

void Star::GeneratePlanets(int worldSize, u32 seed)
{

	// don't regenerate planets if they already exist
	if (m_planets.size() > 0)
		return;

	slth::Noise noiseGen;
	noiseGen.SetSeed(seed);

	NameGenerator nameGen; 

	// individual RNG used here, and is based on the solar seed for this star
	// this way we don't have to keep all the planets in memory, we can just
	// regenerate based on the seed
	slth::Rng rng;
	
	slth::Vector2 coords = slth::Math::CoordsFromIndex(m_cellIndex, worldSize); // TODO: this
	u32 rngSeed = noiseGen.Get2DNoise((int)coords.x, (int)coords.y, seed);
	rng.Seed(rngSeed);

	int numPlanets = rng.RandIntInRange(kMinPlanets, kMaxPlanets);

	for (int i = 0; i < numPlanets; ++i)
	{
		// determine planet type (weighted random)
		float roll = rng.RandFloat();
		float sumOfWeights = 1.f;

		Planet::PlanetType planetType = Planet::PlanetType::kRocky;
		
		if (roll > kRockyChance)
			planetType = Planet::PlanetType::kGasGiant;

		// name 
		std::string name = "";
		if (roll > kChangeOfNamedPlanet)
			name = m_name + " " + s_kRomanNumerals[numPlanets - i - 1];
		else {
			name = nameGen.Generate(rng);
		}

		//size
		float size = 0.f;
		if (planetType == Planet::PlanetType::kGasGiant)
			size = rng.RandFloatInRange(kMaxPlanetSize - kRockyGasDiff, kMaxPlanetSize);
		else
			size = rng.RandFloatInRange(kMinPlanetSize, kMaxPlanetSize - (kRockyGasDiff * 2.f));

		float planetSpacing = (worldSize - kStarPortionOnScreen - 50.f) / numPlanets;

		slth::Vector2 planetPos =
		{
			planetSpacing * static_cast<float>(i) + (planetSpacing / 2.f),
			worldSize / 2.f - (size / 2.f) - 100.f
		};

		float orbitalDistance = worldSize - (planetPos.x + GetSize()) + (size / 2.f);
		
		// gas giants can only exist outside the goldilocks zone

		if (orbitalDistance < GetGoldilocksMax())
			planetType = Planet::PlanetType::kRocky;

		m_planets.emplace_back(Planet(name, planetType, size, orbitalDistance, planetPos, (u32)rng.Rand()));

		m_planets[i].GenerateBiomes(static_cast<size_t>(m_type));
	}
}

void Star::CreateSol(int worldSize)
{
	m_name = "Sol";

	float planetSpacing = (worldSize - kStarPortionOnScreen - 50.f) / 8;

	slth::Vector2 startPos =
	{
		planetSpacing * static_cast<float>(0) + (planetSpacing / 2.f),
		worldSize / 2.f - (80 / 2.f) - 100.f
	};
	
	slth::Noise noiseGen;
	noiseGen.SetSeed(361274); // EARTH in pager code 
	slth::Rng rng;
	rng.Seed(361274);

	std::string pluto = "Pluto";
	m_planets.emplace_back(Planet(pluto, Planet::PlanetType::kRocky, 10.f, 80.f, startPos, (u32)rng.Rand()));
	m_planets[0].GenerateRocky(slth::Color::DarkBeige(), noiseGen, rng, 0.f, 0.f, 0.75f);

	std::string neptune = "Neptune";
	startPos += slth::Vector2(60.f, 0.f);
	m_planets.emplace_back(Planet(neptune, Planet::PlanetType::kGasGiant, 40.f, 160.f, startPos, (u32)rng.Rand()));
	m_planets[1].GenerateGasGiant(slth::Color::Blue(), noiseGen);

	std::string uranus = "Uranus";
	startPos += slth::Vector2(100.f, 0.f);
	m_planets.emplace_back(Planet(uranus, Planet::PlanetType::kGasGiant, 40.f, 260.f, startPos, (u32)rng.Rand()));
	m_planets[2].GenerateGasGiant(slth::Color::LightBlue(), noiseGen);

	std::string saturn = "Saturn";
	startPos += slth::Vector2(100.f, 0.f);
	m_planets.emplace_back(Planet(saturn, Planet::PlanetType::kGasGiant, 50.f, 360.f, startPos, (u32)rng.Rand()));
	m_planets[3].GenerateGasGiant(slth::Color::Beige(), noiseGen);

	std::string jupiter = "Jupiter";
	startPos += slth::Vector2(120.f, 0.f);
	m_planets.emplace_back(Planet(jupiter, Planet::PlanetType::kGasGiant, 60.f, 460.f, startPos, (u32)rng.Rand()));
	m_planets[4].GenerateGasGiant(slth::Color::LightRed(), noiseGen);

	std::string mars = "Mars";
	startPos += slth::Vector2(130.f, 0.f);
	m_planets.emplace_back(Planet(mars, Planet::PlanetType::kRocky, 20.f, 500.f, startPos, (u32)rng.Rand()));
	m_planets[5].GenerateRocky(slth::Color(165.f, 67.f, 29.f), noiseGen, rng, 0.f, 0.f, 0.0f);

	std::string earth = "Earth";
	startPos += slth::Vector2(80.f, 0.f);
	m_planets.emplace_back(Planet(earth, Planet::PlanetType::kRocky, 30.f, 600.f, startPos, (u32)4564654));
	m_planets[6].GenerateRocky(slth::Color::Green(), noiseGen, rng, 0.f, 9999.f, 0.65f);

	std::string venus = "Venus";
	startPos += slth::Vector2(80.f, 0.f);
	m_planets.emplace_back(Planet(venus, Planet::PlanetType::kRocky, 30.f, 650.f, startPos, (u32)rng.Rand()));
	m_planets[7].GenerateRocky(slth::Color::Orange(), noiseGen, rng, 0.f, 9999.f, 0.0f);

	std::string mercury = "Mercury";
	startPos += slth::Vector2(80.f, 0.f);
	m_planets.emplace_back(Planet(mercury, Planet::PlanetType::kRocky, 15.f, 650.f, startPos, (u32)rng.Rand()));
	m_planets[8].GenerateRocky(slth::Color::LightYellow(), noiseGen, rng, 0.f, 9999.f, 0.0f);
}

void Star::ClearData()
{
	m_planets.clear();
}
