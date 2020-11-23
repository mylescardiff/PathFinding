#pragma once
/** \file IAudioSystem.h */
/** Interface for playing music and sound effects */
// Created by Myles Cardiff

#include <string>
#include <memory>
#include <map>
#include <Audio/IMusic.h>
#include <Audio/ISoundEffect.h>

//! \namespace Sloth
namespace slth
{
/** \class IAudioSystem */
/** Interface for playing music and sound effectse */
class IAudioSystem
{
public:

	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //


	/** Default Destructor */
	virtual ~IAudioSystem() {}

	/** Loads music from disk */
	virtual void LoadMusic(const char* name, const char* filename) = 0;

	/** Loads a sound effect from disk */
	virtual void LoadSound(const char* name, const char* filename) = 0;

	/** Plays music */
	virtual void PlayMusic(const char* name) = 0;

	/** Pauses / Resumes music */
	virtual void PauseMusic() = 0;

	/** Plays a sound effect */
	virtual void PlaySound(const char* name) = 0;

	/** Detects if music is currently playing or not */
	virtual bool IsMusicPlaying() = 0;

	/** Deletes music and tracks that have been loaded */
	virtual void ClearTracks() = 0;

protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}