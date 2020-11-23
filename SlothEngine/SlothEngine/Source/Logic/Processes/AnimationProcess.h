#pragma once
/** \file AnimationProcess.h */

// Created by Myles Cardiff

#include ".\IProcess.h"
#include <Logic/Actor.h>
#include <Graphics/ITexture.h>
#include <memory>
#include <Common.h>
#include <Logic/Components/SpriteComponent.h>
#include <Logic/Components/AnimationComponent.h>
//! \namespace Sloth Engine
namespace slth
{

	class IGraphics;

/** \class AnimationProcess */

class AnimationProcess
	: public IProcess
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	AnimationProcess();

	AnimationProcess(std::string name, unsigned int frameLength, float frameTimer, int numFrames, bool loop);

	/** Default Destructor */
	~AnimationProcess();

	virtual void Update(float deltaTime);
	
	virtual bool Init() override;
	virtual bool Init(XmlData* pElement, Actor* pActor);

	virtual void Resume() override;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	// direcly set when construcuted
	Actor* m_pActor;
	float m_frameTimer;
	unsigned int m_frameLength;
	int m_numFrames;
	bool m_loop;
	std::string m_name;
	std::string m_path;
	
	// used by the process
	std::string m_previousName;
	float m_delay;
	int m_frameCounter;
	float m_frameSwitchTime;

	// cached components
	SpriteComponent* m_pSpriteComp;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	std::string& GetName() { return m_name; }
	std::string& GetPath() { return m_path; }
	void SetActor(Actor* pActor) { m_pActor = pActor; }
	

};
}