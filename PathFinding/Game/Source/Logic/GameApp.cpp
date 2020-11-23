#include "GameApp.h"
#include "GameLogic.h"
#include <Utilities/RectInt.h>
#include <Logic/Animation.h>


slth::ApplicationLayer* GameApp::Create()
{
	return new GameApp;
}

bool GameApp::Init()
{
	ApplicationLayer::Init();

	m_pGameLayer = new GameLogic;

	if (!m_pGameLayer->Init(this))
	{
		return false;
	}

	return true;
}



