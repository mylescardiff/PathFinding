#pragma once
/** \file AnimationComponent.h */

// Created by Myles Cardiff

#include ".\IComponent.h"
#include <unordered_map>
#include <Common.h>
#include <Utilities/Hasher.h>

//! \namespace Sloth Engine
namespace slth
{
	class Animation;
	class ProcessManager;
	class AnimationProcess;
	class IProcess;


/** \class AnimationComponent */
/** Adds animations to the actor (requires Sprite and Transform) */
class AnimationComponent
	: public IComponent
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	SLTH_API AnimationComponent();

	/** Copy Constructor */
	AnimationComponent(const AnimationComponent& clone)
		: m_pDefaultAnimation(clone.m_pDefaultAnimation)
		, m_defaultAnimName(clone.m_defaultAnimName)
		, m_pRunningAnimation(nullptr)
	{
		//
	}

	/** Copy the component */
	SLTH_API virtual IComponent* Copy(Actor* pNewOwner) override { return new AnimationComponent(*this); }

	/** Default Destructor */
	SLTH_API virtual ~AnimationComponent();

	/** Ideintifier Functions */
	static constexpr Id Identifier = Hasher::Hash32("Animation");
	SLTH_API virtual const char* GetName() const override { return "Animation"; }
	SLTH_API virtual const Id GetIdentifier() const override { return Identifier; }

	/** Initialization Functions */
	SLTH_API virtual bool Init(XmlData* xmlElement) override;
	SLTH_API virtual bool PostInit() override;

	/** Perform an animation */
	SLTH_API void DoAnimation(Animation* pAnimation, ProcessManager& pProcessManager);

	/** Resume the default animation, if there is one */
	SLTH_API void ResumeDefault(ProcessManager& pProcessManager);

	SLTH_API void KillAll(ProcessManager& pProcessManager);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	AnimationProcess* m_pRunningAnimation;
	Animation* m_pDefaultAnimation;
	std::unordered_map<Id, Animation*> m_animations;
	std::string m_defaultAnimName; 
	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
	SLTH_API std::string& GetDefaultName() { return m_defaultAnimName; }
	SLTH_API Animation* GetDefault() { return m_pDefaultAnimation;  }
	SLTH_API void SetDefault(Animation* pAnimation) { m_pDefaultAnimation = pAnimation; }
	SLTH_API void SetRunning(AnimationProcess* pAnimation) { m_pRunningAnimation = pAnimation; }
};
}