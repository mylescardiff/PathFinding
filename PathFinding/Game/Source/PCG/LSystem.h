#pragma once
/** \file LSystem.h */
// Created by Myles Cardiff

#include <Utilities/Vector2.h>
#include <Utilities/Color.h>
#include <vector>
#include <Graphics/IGraphics.h>
#include <Utilities/Rng.h>
#include <stack>



class LSystem
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	struct LineData
	{
		slth::Vector2 m_start;
		slth::Vector2 m_end;
		slth::Color m_color;
	};

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	LSystem()
		: m_state("")
		, m_startPosition({ 0.f, 0.f })
		, m_lineDistance(25.f)
		, m_generation(1)
	{ }

	/** Explicit Constructor */
	LSystem(const char* state, float lineDistance)
		: m_state(state)
		, m_lineDistance(lineDistance)
		, m_startPosition({ 0.f, 0.f })
		, m_generation(1)
	{ }

	

protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	std::string m_state;
	std::vector<LineData> m_lineList;
	slth::Vector2 m_startPosition; 
	float m_lineDistance;
	int m_generation; 

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	void SetStartPosition(slth::Vector2 position);
};

// ----------------------------------------------------------------------------------
//	SIERPINSKI TRIANGLE APPROXIMATION
// ----------------------------------------------------------------------------------
//	* This one is pretty straightforward, just directly from wiki: https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle
//
//		variables: A B
//		constants : +−
//		start : A
//		rules : (A → B−A−B), (B → A+B+A)
//		angle : 60°

class SierpinskiTriangle : public LSystem
{

public: 

	SierpinskiTriangle()
		: LSystem("A", 5.f)
	{
		//
	}

	// making these non-virtual for performance
	void NextGeneration();
	void Draw(slth::IGraphics* pGraphics);

private:
	const float kAngle = 60.f;
	const float kLineReduction = 2.f;
	const float kMinumumLineLength = 3.f;
};


class FractalLightning : public LSystem
{

public:

	struct Transform
	{
		slth::Vector2 m_position;
		float m_angle;
	};

	FractalLightning()
		: LSystem("L", 5.f)
		, m_numBranches(0)
		, m_currentPosition({ {0.f, 0.f}, 0.f })
	{
		//
	}

	// making these non-virtual for performance
	void NextGeneration(slth::Rng& rng);
	void CreateLineList(slth::Rng& rng);
	void Draw(slth::IGraphics* pGraphics);

private:

	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	const float kAngle = 60.f;
	const float kMinLineLength = 3.f;
	const float kMaxLineLength = 20.f;
	const float kJitterChance = 0.8f;
	const float kBranchChance = 0.05f;
	const int kStartingBranches = 2;
	const float kAngleChange = 10.f;
	const float kMaxAngleDeviation = 60.f;
	const int kMaxBranches = 5;
	
	std::vector<LineData> m_lineList; 
	slth::Vector2 m_endPosition;
	Transform m_currentPosition; 
	int m_numBranches;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	void SetStartEndPositions(slth::Vector2 start, slth::Vector2 end);

};

