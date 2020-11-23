#pragma once
/** \file SFMLSoundEffect.h */

// Created by Myles Cardiff

#include ".\ISoundEffect.h"
#include <SFML/Audio.hpp>

//! \namespace Sloth Engine
namespace slth
{
/** \class SFMLSoundEffect */
class SFMLSoundEffect
	: public ISoundEffect
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Implicit Constructor */
	SFMLSoundEffect(sf::Sound* pSound); // passed by value b/c it needs to get copied here

	/** Default Destructor */
	virtual ~SFMLSoundEffect() override;

	/** Get the underlying sf::Sound pointer */
	sf::Sound* GetSound() const { return m_pSound; }

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	sf::Sound* m_pSound;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

};
}