#pragma once
/** \file Star.h */
// Created by Myles Cardiff

#include <Universe/Planet.h>
#include <Utilities/Vector2f.h>
#include <Utilities/Color.h>
#include <Utilities/Rng.h>
#include <Graph/GraphNode.h>
/** \class Star */
class Star
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	constexpr static float kStarPortionOnScreen = 150.f;
	
	// Tunables / Constants

	struct StarData
	{
		float m_size;
		float m_density;
		slth::Color m_color;
		float m_chanceOfAppearing;
		const char* m_name;
		float m_goldilocksMin;
		float m_golidlicksMax;
	};

	enum class StarType
	{
		kMainSequence,
		kWhiteDwarf,
		kRedGiant,
		kSuperGiant,
		kBlackHole,
		kNumTypes
	};

	

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/** Explicit Constructor */
	Star(StarType type, slth::Vector2f position, int cellIndex);

	/** Default Destructor */
	~Star();

	/** Determine Type From the size */
	static StarType DetermineType(slth::Rng& rng);

	/** Create random planets around this star*/
	void GeneratePlanets(int worldSize, u32 seed);

	/** Specifically create sol system */
	void CreateSol(int worldSize);

	/** Erase planets*/
	void ClearData();

private:
	
	// size, density, color, chance of appearing
	constexpr static Star::StarData s_starDataList[] = {
		{ 4.f, 3.f, slth::Color::LightYellow(), 0.8f, "Main Sequence", 400.f, 550.f },
		{ 4.f, 5.f, slth::Color::White(), 0.1f, "White Dwarf", 150.f, 350.f },
		{ 6.f, 3.f, slth::Color::LightRed(), 0.05f, "Red Giant", 350.f, 650.f },
		{ 8.f, 4.f, slth::Color::LightBlue(), 0.03f, "Blue Super Giant", 400.f, 900.f },
		{ 4.f, 10.f, slth::Color::LightPurple(), 0.02f, "Black Hole", 0.f, 0.f },
	};

	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	slth::Vector2f m_position;
	int m_cellIndex;
	StarType m_type;
	std::string m_name;
	std::vector<Planet> m_planets;
	bool m_hasMClassPlanet;
	
	u64 m_questNodeId;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	float GetSize() const { return s_starDataList[static_cast<size_t>(m_type)].m_size; }
	float GetDensity() const { return s_starDataList[static_cast<size_t>(m_type)].m_density; }
	slth::Color GetColor() const { return s_starDataList[static_cast<size_t>(m_type)].m_color; }
	float GetGoldilocksMin() { return s_starDataList[static_cast<size_t>(m_type)].m_goldilocksMin; }
	float GetGoldilocksMax() { return s_starDataList[static_cast<size_t>(m_type)].m_golidlicksMax; }
	const std::string& GetName() const { return m_name; }
	const char* GetTypeName() const { return s_starDataList[static_cast<size_t>(m_type)].m_name; }
	StarType GetType() const { return m_type; }
	std::vector<Planet>& GetPlanets() { return m_planets; }
	slth::Vector2f GetPosition() const { return m_position; } 
	u64 GetQuestNode() const { return m_questNodeId; }
	u32 GetIndex() const { return m_cellIndex; }

	void SetType(StarType type) { m_type = type; }
	void SetName(std::string& name) { m_name = name; }
	void SetQuestMarker(u64 nodeId) { m_questNodeId = nodeId; }
	static const StarData& GetStarTypeData(const size_t index) { return s_starDataList[index]; }

};
