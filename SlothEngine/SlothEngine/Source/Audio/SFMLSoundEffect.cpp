#include "SFMLSoundEffect.h"

using slth::SFMLSoundEffect;

slth::SFMLSoundEffect::SFMLSoundEffect(sf::Sound* pSound)
	: m_pSound(pSound)
{
}

SFMLSoundEffect::~SFMLSoundEffect()
{
	delete m_pSound->getBuffer();
	delete m_pSound;

}