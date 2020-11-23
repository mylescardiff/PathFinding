#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/AnimationComponent.h>
#include <Logic/Components/SpriteComponent.h>
#include <Logic/Components/TextComponent.h>
#include <Logic/Components/RigidBodyComponent.h>
#include <Logic/Animation.h>
#include <Logic/IGameLayer.h>
#include <Common.h>
#include <time.h>
#include <Utilities/RectInt.h>
#include "HumanView.h"
#include "../Logic/GameLogic.h"

const float kMovementRate = 0.1f;
const float kFriction = 0.00f;
const float kSpinRate = 0.1f;

HumanView::HumanView()
{
	//
}

bool HumanView::Init(slth::IGameLayer* pGameLogic)
{
	// get stuff from the Game Logic
	m_pGameLogic = pGameLogic;
	m_pAudio = pGameLogic->GetAudio();
	m_pGraphics = pGameLogic->GetGraphics();

	// load the default font
	m_font.loadFromFile("Assets\\arial.ttf");
	
	//clear keybaordDraw(
	m_pKeyboard->ClearAllKeys();
	
	m_pPlayer = pGameLogic->FindActor("Player");
	
	return true;
}

void HumanView::Update(float deltaTime)
{
	//
}

void HumanView::ViewScene()
{
	m_pGraphics->StartDrawing();
	
	// draw the actors
	for (auto pActor: m_pGameLogic->GetActors())
	{
		if (pActor.second)
		{
			if (!pActor.second->IsHidden())
			{
				for (auto pComponent : pActor.second->GetComponents())
				{
					slth::IDrawableComponent* pDrawable = dynamic_cast<slth::IDrawableComponent*>(pComponent.second);
					if (pDrawable)
					{
						pDrawable->Draw(m_pGraphics);
					}
				}
			}
			
		}
	}

	// this is for manually drawing stuff from game layer, i'm considering  
	// ripping out the whole View thing, i really don't like it. 
	m_pGameLogic->Draw();

	m_pGameLogic->DebugDraw();

	//// draw the UI
	slth::Vector2 centerView = m_pGameLogic->GetWorld()->GetCenter();
	m_pGraphics->SetCameraPosition(centerView.x, centerView.y);
	m_pGraphics->SetCameraDefault();

	for (auto pUiElement : m_pGameLogic->GetUIElements())
	{
		if (pUiElement.second)
		{
			if (!pUiElement.second->IsHidden())
			{
				for (auto pComponent : pUiElement.second->GetComponents())
				{
					slth::IDrawableComponent* pDrawable = dynamic_cast<slth::IDrawableComponent*>(pComponent.second);
					if (pDrawable)
					{
						pDrawable->Draw(m_pGraphics);
					}
				}
			}
			
		}
	}

	m_pGraphics->EndDrawing();
}

void HumanView::SetInput(slth::IKeyboard * pKeyboard, slth::IMouse * pMouse)
{
	m_pKeyboard = pKeyboard;
	m_pMouse = pMouse;
}


