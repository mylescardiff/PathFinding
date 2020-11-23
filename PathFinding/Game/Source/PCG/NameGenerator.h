#pragma once
/** \file NameGenerator.h */
// Created by Myles Cardiff

#include ".\LSystem.h"

// name generator rules

class NameGenerator : public LSystem
{
public:

	NameGenerator()
		: LSystem("", 5.f)
	{ 
		//
	}

private:

	// private members
	float m_chanceOfNewSyllable = 0.8f;
	void Reset();

public:

	// making these non-virtual for performance
	bool NextGeneration(slth::Rng& rng);
	std::string Generate(slth::Rng& rng);

};