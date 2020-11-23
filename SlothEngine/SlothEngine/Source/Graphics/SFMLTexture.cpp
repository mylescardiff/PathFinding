#include "SFMLTexture.h"

using slth::SFMLTexture;

SFMLTexture::SFMLTexture()
{
	//
}

SFMLTexture::~SFMLTexture()
{
	delete m_pTexture;
}

bool slth::SFMLTexture::Init(sf::Texture* pTexture)
{
	m_pTexture = pTexture;
	return true;
}
