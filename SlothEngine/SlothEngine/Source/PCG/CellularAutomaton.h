#pragma once
/** \file CellularAutomaton.h */
// Created by Myles Cardiff

#include <Common.h>
#include <vector>
#include <functional>
#include <Logic/Grid/GridSystem.h>


//! \namespace Sloth Engine
namespace slth
{

	typedef std::function<void(slth::GridTile& pTile, std::vector<u32>& gridSection, slth::GridSystem & gridOriginal)> AutomataRule;


/** \class CellularAutomaton */
/** Cllular automaton that operates on a grid */
class CellularAutomaton
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	enum class SpaceType
	{
		kMoore,
		kVonNewman
	};

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/** Default Constructor */
	SLTH_API CellularAutomaton();

	/** Explicit Constructor */
	SLTH_API CellularAutomaton(SpaceType type);

	/** Default Destructor */
	SLTH_API ~CellularAutomaton();

	/** Run Rules */
	SLTH_API void Run(GridSystem& grid);

	SLTH_API void Reset();
	

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	SpaceType m_spaceType; 
	std::vector<AutomataRule> m_rules;
	u32 m_steps;
	u32 m_currentSteps;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API void AddRule(AutomataRule rule) { m_rules.emplace_back(rule); } 
	SLTH_API void ClearRules() { m_rules.clear(); }
	SLTH_API void SetSteps(u32 steps) { m_steps = steps; }
	SLTH_API u32 GetSteps() const { return m_steps; }

};
}