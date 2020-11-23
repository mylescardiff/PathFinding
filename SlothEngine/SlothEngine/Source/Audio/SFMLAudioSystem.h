#pragma once
/** \file SFMLAudioSystem.h */

// Created by Myles Cardiff

#include <Audio/IAudioSystem.h>
#include <SFML/Audio.hpp>
#include <Audio/SFMLMusic.h>
#include <Audio/SFMLSoundEffect.h>

//! \namespace Sloth Engine
namespace slth
{
/** \class SFMLAudioSystem */

class SFMLAudioSystem
	: public IAudioSystem
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	SFMLAudioSystem();

	/** Default Destructor */
	virtual ~SFMLAudioSystem();

	/** Loads music from disk */
	virtual void LoadMusic(const char* name, const char* filename) override;

	/** Loads a sound effect from disk */
	virtual void LoadSound(const char* name, const char* filename) override;

	/** Plays music */
	virtual void PlayMusic(const char* name) override;

	/** Pauses / Resumes music */
	virtual void PauseMusic() override;

	/** Plays a sound effect */
	virtual void PlaySound(const char* name) override;

	/** Detects if music is currently playing or not */
	virtual bool IsMusicPlaying() override;

	/** Deletes music and tracks that have been loaded */
	virtual void ClearTracks() override;


private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	std::map<size_t, SFMLMusic*> s_musicList;
	std::map<size_t, SFMLSoundEffect*> s_soundEffectList;
	SFMLMusic* s_currentTrack;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	/** Pulls a pointer to song out of the list of loaded files */
	SFMLMusic* GetMusicByName(const char* name);

	/** Pulls a pointer to a sound effect out of the list of loaded files */
	SFMLSoundEffect* GetSoundByName(const char* name);

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}