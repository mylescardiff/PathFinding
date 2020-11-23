#pragma once
/** \file Planet.h */
// Created by Myles Cardiff

#include <vector>
#include <string>
#include <Graphics/IGraphics.h>
#include <Utilities/Noise.h>
#include <Utilities/Rng.h>
#include <SFML/Graphics.hpp>

/** \class Planet */
class Planet
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	struct Moon
	{
		float m_size;
		float m_orbit; 
	};

	enum class PlanetType
	{
		kRocky,
		kGasGiant,
	};

	enum class SoilElements
	{
		kNone,
		kIron,
		kPotassium,
		kCopper,
		kSulfer,
		kNumSoilElements
	};

	constexpr static slth::Color s_kSoilColors[] = { 
		slth::Color(133, 133, 133), 
		slth::Color(149, 86, 40), 
		slth::Color(135, 27, 139),
		slth::Color(89, 160, 99),
		slth::Color(195, 199, 81)
	};

	enum class GasTypes
	{
		kHydrogen,
		kOxygen,
		kCarbonDioxide,
		kSulfurDioxide,
		kNumAtmos
	};
	constexpr static slth::Color s_kGasColors[] = {
	slth::Color(217, 156, 59),
	slth::Color(59, 215, 217),
	slth::Color(103, 103, 205),
	slth::Color(148, 72, 74),

	};

	constexpr static int kNumColorShades = 6;
	constexpr static int kNumGasStripes = 10;
	constexpr static float kColorRange = 200.f;
	enum class PlanetSurfaceType
	{
		kLand,
		kSea,
		kNumTypes
	};

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	Planet(std::string& name, PlanetType type, float radius, float distance, slth::Vector2f positionOnScreen, u32 planetSeed);

	/** Generate Biomes */
	void GenerateBiomes(size_t starTypeIndex);

	/** Create a Gas Giant */
	void GenerateGasGiant(slth::Color baseColor, slth::Noise& noiseGen);

	/** Create a Rocky Planet */
	void GenerateRocky(slth::Color baseColor, slth::Noise& noiseGen, slth::Rng& rng, float goldLocksMin, float goldiLocksMax, float waterLevel);

	/** Draw planet on screen */
	void Draw(slth::IGraphics* pGraphics, float expandFactor);

	/** Get a range of colors + / - the base color */
	void GetColorArray(slth::Color baseColor, slth::Color* array, float numColors);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	PlanetType m_type;
	std::string m_name;
	float m_radius;
	float m_orbitalDistance;
	
	slth::Vector2f m_onScreenPosition;
	unsigned long long m_planetSeed; 
	float m_waterLevel;

	sf::Image m_planetImage;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	float GetRadius() const { return m_radius; }
	float GetOrbit() const { return m_orbitalDistance; }
	const std::string& GetName() { return m_name; }
	void SetPosition(slth::Vector2f pos) { m_onScreenPosition = pos; }
	sf::Image& GetImage() { return m_planetImage; }
	slth::Vector2f GetPosition() const { return m_onScreenPosition; }
	

};
