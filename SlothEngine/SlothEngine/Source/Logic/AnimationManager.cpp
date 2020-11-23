#include "AnimationManager.h"
#include <Graphics/IGraphics.h>
#include <Logic/Processes/AnimationProcess.h>
#include <Logic/Animation.h>
#include <Logger/Logger.h>

using slth::AnimationManager;

AnimationManager::AnimationManager()
{
	//
}

AnimationManager::~AnimationManager()
{
	for (auto pair : m_animations)
	{
		delete pair.second;
	}
	m_animations.clear();
}

slth::Animation* slth::AnimationManager::Find(Id id)
{
	auto it = m_animations.find(id);
	if (it == m_animations.end())
	{
		_LOGW("Could not find animation");
		return nullptr;
	}

	return it->second;
}

void slth::AnimationManager::LoadAnimations(const char* filename, IGraphics * pGraphics)
{
	using namespace tinyxml2;

	XMLDocument doc;
	XMLError error = doc.LoadFile(filename);
	if (error != XML_SUCCESS)
	{
		_LOGW("Could not load XML File");
	}

	XMLElement* pRoot = doc.RootElement();
	XMLElement* pProcessElement = pRoot->FirstChildElement("Animation");

	while (pProcessElement)
	{
		Animation* pAnimation = new Animation;
		pAnimation->Init(pProcessElement);
		pGraphics->LoadTexture(pAnimation->GetPath().c_str());
		m_animations.emplace(HASH(pAnimation->GetName()), pAnimation);

		pProcessElement = pProcessElement->NextSiblingElement("Animation");
	}
}

