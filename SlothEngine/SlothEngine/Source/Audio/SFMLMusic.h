#pragma once
/** \file SFMLMusic.h */

// Created by Myles Cardiff

#include ".\IMusic.h"
#include <SFML/Audio.hpp>
#include <Audio/SFMLMusic.h>

//! \namespace Sloth Engine
namespace slth
{
/** \class SFMLMusic */
class SFMLMusic
	: public IMusic
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Implicit Constructor */
	SFMLMusic(sf::Music* pMusic)
		: m_pMusic(pMusic)
	{
	
	}

	/** Default Destructor */
	~SFMLMusic();

	/** Get the underlying sf::Music pointer */
	sf::Music* GetNativeMusic() const { return m_pMusic; }

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	sf::Music* m_pMusic; 

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}