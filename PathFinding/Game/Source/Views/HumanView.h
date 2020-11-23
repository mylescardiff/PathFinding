#pragma once
/** \file HumanView.h */

// Created by Myles Cardiff

#include <Views/IView.h>
#include <Input/IKeyboard.h>
#include <Input/IMouse.h>
#include <Graphics/SFMLGraphics.h>
#include <Application/ApplicationLayer.h>
#include <Audio/SFMLAudioSystem.h>
#include <Logic/Actor.h>
#include <Utilities/Vector2.h>
#include <Logic/AnimationManager.h>
#include <Logic/IGameLayer.h>

/** \class HumanView */

class HumanView : public slth::IView
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //



	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	HumanView();

	bool Init(slth::IGameLayer* pGameLogic) override;
	void Update(float deltaTime) override;
	void ViewScene() override;
	

	void SetInput(slth::IKeyboard* pKeyboard, slth::IMouse* pMouse);

protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	slth::IGameLayer* m_pGameLogic;

	slth::IKeyboard* m_pKeyboard;
	slth::IMouse* m_pMouse;
	slth::IAudioSystem* m_pAudio;
	slth::IGraphics* m_pGraphics;
	slth::ProcessManager* m_pProcessManager;
	slth::AnimationManager* m_pAnimationManager;
	slth::EventDispatcher* m_pEventDispatcher;
	
	slth::Actor* m_pPlayer;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	
	sf::Font m_font;
		
public:

	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
