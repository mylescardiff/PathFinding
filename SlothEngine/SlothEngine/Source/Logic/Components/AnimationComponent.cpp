#include "AnimationComponent.h"
#include <Logic/Animation.h>
#include <Logic/Processes/AnimationProcess.h>
#include <Logic/Processes/ProcessManager.h>
#include <Logger/Logger.h>

using slth::AnimationComponent;

AnimationComponent::AnimationComponent()
	: m_defaultAnimName("")
	, m_pDefaultAnimation(nullptr)
	, m_pRunningAnimation(nullptr)
{
	
}



AnimationComponent::~AnimationComponent()
{
	m_pRunningAnimation = nullptr;
}

bool slth::AnimationComponent::Init(XmlData* xmlElement)
{
	const char* animName = xmlElement->Attribute("defaultAnim");
	if (animName)
	{
		m_defaultAnimName = animName;
	}
	return true;
}

bool slth::AnimationComponent::PostInit()
{
	return true;
}

void slth::AnimationComponent::DoAnimation(Animation* pAnimation, ProcessManager& processManager)
{
	_LOGI("Started Animation");
	if (m_pRunningAnimation)
	{
		m_pRunningAnimation->Abort();
	}
	
	slth::AnimationProcess* pAnimationProcess = pAnimation->CreateProcess();
	pAnimationProcess->SetActor(m_pOwner);

	processManager.AttachProcess(pAnimationProcess);
	m_pRunningAnimation = pAnimationProcess;

	if (m_pDefaultAnimation)
	{
		slth::Animation* pDefaultAnimation = GetDefault();
		slth::AnimationProcess* pDefaultAnimationProcess = pDefaultAnimation->CreateProcess();
		pDefaultAnimationProcess->SetActor(m_pOwner);
		pAnimationProcess->SetChild(pDefaultAnimationProcess);
	}

}

void slth::AnimationComponent::ResumeDefault(ProcessManager& pProcessManager)
{
	DoAnimation(m_pDefaultAnimation, pProcessManager);
}

void slth::AnimationComponent::KillAll(ProcessManager& processManager)
{
	if (m_pRunningAnimation)
	{
		m_pRunningAnimation->Abort();
	}
	
}
