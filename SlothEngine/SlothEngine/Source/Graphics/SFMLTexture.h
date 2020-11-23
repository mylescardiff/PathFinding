#pragma once
/** \file SFMLTexture.h */

// Created by Myles Cardiff

#include <SFML/Graphics.hpp>

//! \namespace Sloth Engine
namespace slth
{
/** \class SFMLTexture */
/** SFML Version of the texture class */
class SFMLTexture
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	SFMLTexture();

	/** Default Destructor */
	~SFMLTexture();

	virtual sf::Texture* GetNativeTexture() { return m_pTexture; }
	virtual bool Init(sf::Texture* pTexture);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	sf::Texture* m_pTexture;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //



public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	sf::Texture* GetTexture() { return m_pTexture; }
};
}