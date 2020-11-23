#include "CellularAutomaton.h"
#include <Logic/Grid/GridTile.h>
#include <assert.h>
#include <Utilities/Utilities.h>

using slth::CellularAutomaton;

CellularAutomaton::CellularAutomaton()
	: m_spaceType(SpaceType::kMoore)
	, m_steps(0)
{
	//
}

slth::CellularAutomaton::CellularAutomaton(SpaceType spaceType)
	: m_spaceType(spaceType)
	, m_steps(0)
{
	//
}

CellularAutomaton::~CellularAutomaton()
{
	//
}

void slth::CellularAutomaton::Run(GridSystem& grid)
{
	// this uses the existing GridSystem's m_type property to store the state for 
	// the purpose of running cellular automata

	// make a copy of just the states at each index for running automata
	// this was to avoid copying my GridSystem object which has a bunch of 
	// pointers and actors to it, and all we need here is the state the cell
	// is in

	if (m_steps != 0 && m_currentSteps > m_steps)
		return;

	std::vector<u32> gridCopy;
	gridCopy.resize(grid.GetTiles().size());

	// this adds N to complexity, but don't think there's a way around that
	// becuase we need the surrounding tiles for each
	for (size_t i = 0; i < grid.GetTiles().size(); ++i)
	{
		gridCopy[i] = grid.GetTile(i).GetType();
	}

	for (size_t i = 0; i < grid.GetTiles().size(); ++i)
	{
		// loop through the rules and detemine state
		for (AutomataRule rule : m_rules)
		{
			// state is defined by game logic as enum: u32
			// outcome is defined by the user in whatever function they pass into the rule

			slth::GridTile& pTile = grid.GetTile(i);
			rule(pTile, gridCopy, grid);
			
		}
	}
	
	++m_currentSteps;
}

void slth::CellularAutomaton::Reset()
{
	m_steps = 0;
	m_currentSteps = 0;
	ClearRules();
}


