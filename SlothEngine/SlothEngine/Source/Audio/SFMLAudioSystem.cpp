#include "SFMLAudioSystem.h"
#include <Logger/Logger.h>

using slth::SFMLAudioSystem;

SFMLAudioSystem::SFMLAudioSystem()
{
	//
}

SFMLAudioSystem::~SFMLAudioSystem()
{
	ClearTracks();
}

void slth::SFMLAudioSystem::LoadMusic(const char* name, const char * filename)
{
	sf::Music* pMusic = new sf::Music; 
	if (!pMusic->openFromFile(filename))
	{
		delete pMusic;
		_LOGE("Could not load music: " + std::string(filename));
		return;
	}
	s_musicList.insert(std::make_pair(std::hash<std::string>{}(name), new SFMLMusic(pMusic)));

}

void slth::SFMLAudioSystem::LoadSound(const char* name, const char * filename)
{
	sf::SoundBuffer* pSoundBuffer = new sf::SoundBuffer;
	if (!pSoundBuffer->loadFromFile(filename))
	{
		_LOGE("Could not load sound effect: " + std::string(filename));
	}
	sf::Sound* pSound = new sf::Sound(*pSoundBuffer);
	s_soundEffectList.insert(std::make_pair(std::hash<std::string>{}(name), new SFMLSoundEffect(pSound)));
}

void slth::SFMLAudioSystem::PlayMusic(const char* name)
{
	SFMLMusic* pMusic = GetMusicByName(name);
	
	sf::Music* pNativeMusic = pMusic->GetNativeMusic();
	
	pNativeMusic->setPosition(0, 1, 10); // change its 3D position
	pNativeMusic->setPitch(1);           // increase the pitch
	pNativeMusic->setVolume(50);         // reduce the volume
	pNativeMusic->setLoop(true);         // make it loop

	pNativeMusic->play();

	s_currentTrack = pMusic;

}

void slth::SFMLAudioSystem::PauseMusic()
{
	if (IsMusicPlaying())
	{
		s_currentTrack->GetNativeMusic()->pause();
	}
	else
	{
		if (s_currentTrack)
		{
			s_currentTrack->GetNativeMusic()->play();
		}
	}
}

void slth::SFMLAudioSystem::PlaySound(const char* name) 
{
	SFMLSoundEffect* pEffect = GetSoundByName(name);
	sf::Sound* sound = pEffect->GetSound();
	sound->play();
}

bool slth::SFMLAudioSystem::IsMusicPlaying() 
{
	if (s_currentTrack && s_currentTrack->GetNativeMusic()->getStatus() == sf::SoundSource::Playing)
	{
		return true;
	}
	return false;
}

void slth::SFMLAudioSystem::ClearTracks()
{
	// stop playing
	if (s_currentTrack)
	{
		s_currentTrack->GetNativeMusic()->stop();
	}

	// clean up loaded files
	for (auto pMusic : s_musicList)
	{
		if (pMusic.second)
			delete pMusic.second;
	}

	for (auto pSound : s_soundEffectList)
	{
		if (pSound.second)
		{
			delete pSound.second;

		}
	}
}

slth::SFMLMusic* slth::SFMLAudioSystem::GetMusicByName(const char* name)
{
	auto it = s_musicList.find(std::hash<std::string>{}(name));

	if (it != s_musicList.end())
	{
		return it->second;
	}
	return nullptr;
}

slth::SFMLSoundEffect* slth::SFMLAudioSystem::GetSoundByName(const char * name)
{
	auto it = s_soundEffectList.find(std::hash<std::string>{}(name));

	if (it != s_soundEffectList.end())
	{
		return it->second;
	}
	return nullptr;
}
