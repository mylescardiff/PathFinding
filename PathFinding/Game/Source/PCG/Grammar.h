#pragma once
/** \file Grammar.h */
// Created by Myles Cardiff

#include <unordered_map>
#include <vector>
#include <Utilities/Rng.h>

// ------------------------------------------------------------------------
// Assignment 7.1 Notes
// ------------------------------------------------------------------------
//
//	* Grammar is a generic class, there are no derived versions.
// 
//	* Data is returned as two strings:
//			- The raw data e.g. aabbbbababa
//			- A translated string that replaces the terminating symbols with 
//			  full text. Translation rules are set similarly to the production rules
//	* 
//
//-------------------------------------------------------------------------------------------------------
// Part 1. Weapon Generator
//-------------------------------------------------------------------------------------------------------
//
// Starting state: ?
//
// Weapons W: 
//		S/s = sword 
//		A/a = axe
//		B/b = bow
//		M/m = mace
//		D/d = dagger 
//
//		* both terminating and non terminating versions here so that we 
//			can add the specific traits for each
//
// Bonuses / Curses: 
//		+ = plus
//		- = minus
//		1, 2, 3 = degree of bonus / curse
//
// Special Properties P: 
//		p  = sharpness
//		g = mighty
//		y = slaying
//		o = protection
//		n = poison
//
// Elemental Bonuses E: 
//		f = fire
//		l = lightning
//		c = cold
//		i = acid
//
// ---------------------------------------------------------------------------
//	* The actual grammar rules are set up in PostInit() (above)
// 
//	* RunGrammar() below fires off the process, and then sets the appropriate
//	  game objects on screen visible. 
//
//-------------------------------------------------------------------------------------------------------
// Part 2. My Own Derivation
//-------------------------------------------------------------------------------------------------------
//
//	* I ran out of time here, had another week from hell, unfortunatley :(. My intent was to create a 
//	  grammar that generated back stories / descriptions for the above weapons. 

struct Rule
{
	float m_weight;
	std::string m_successor;
	bool m_hasNonTerminators;
};

struct GrammarData
{
	std::string m_rawData;
	std::string m_translatedData;
};

using RuleSet = std::unordered_multimap<char, Rule>;

/** \class Grammar */
/** Simple Grammar Class */
class Grammar
{
public:

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	void Run(slth::Rng& rng, GrammarData& grammarData);
	void AddRule(const char ch, Rule rule);

protected:
	// --------------------------------------------------------------------- //
	// Protected Member Variables
	// --------------------------------------------------------------------- //

	RuleSet m_rules;
	std::string m_startingState;
	std::string m_terminators; 
	std::unordered_map<char, std::string> m_dictionary;
	
	// --------------------------------------------------------------------- //
	// Protected Member Functions
	// --------------------------------------------------------------------- //

	bool IsTermiatingCharacter(char ch);

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	void SetTerminators(const char* terminators) { m_terminators = terminators; }
	void SetStartingState(const char* state) { m_startingState = state; }

	void AddTranslation(char ch, const char* expandedString) { m_dictionary.emplace(ch, expandedString); }
};
