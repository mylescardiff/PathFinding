#include "AnimationProcess.h"
#include <Graphics/IGraphics.h>

using slth::AnimationProcess;

AnimationProcess::AnimationProcess()
	: IProcess()
	, m_frameLength(0)
	, m_frameTimer(0)
	, m_loop(false)
	, m_frameCounter(0)
	
{
	
}

slth::AnimationProcess::AnimationProcess(std::string name, unsigned int frameLength, float frameTimer, int numFrames, bool loop)
	: IProcess()
	, m_name(name)
	, m_frameLength(frameLength)
	, m_frameSwitchTime(frameTimer)
	, m_frameTimer(frameTimer)
	, m_numFrames(numFrames)
	, m_loop(loop)
	, m_frameCounter(0)
{
	//
}

AnimationProcess::~AnimationProcess()
{
	
}


void slth::AnimationProcess::Update(float deltaTime)
{
	
	m_frameTimer -= deltaTime;
	if (m_frameTimer <= 0)
	{
		
		// check if the frame timer has reached zero, meaning it's time to switch frames..

		// ...reset the timer...
		m_frameTimer = m_frameSwitchTime;
		

		// ...get the texture rect from the sprite...
		RectInt textureRect = m_pSpriteComp->GetTextureRect();
		
		++m_frameCounter;
		if (m_frameCounter == m_numFrames)
		{
			if (m_loop)
			{
				// ... and reset if it it's reached the max frame length
				textureRect.left = 0;
				textureRect.right = m_frameLength;
				m_frameCounter = 0;
			
			}
			else
			{
				m_state = State::kSucceeded;
			}
		
		}
		else
		{
			// ... of move it over by one frame and advance the animation...
			textureRect.left = m_frameCounter * m_frameLength;
			textureRect.right = textureRect.left + m_frameLength;
		}

		// ... and finally set the texture rect
		m_pSpriteComp->SetTextureRect(textureRect);
	}
}

bool slth::AnimationProcess::Init()
{
	m_pSpriteComp = m_pActor->GetComponent<SpriteComponent>();
	return m_pSpriteComp;
}

bool slth::AnimationProcess::Init(XmlData* pElement, Actor* pActor)
{
	m_name = pElement->Attribute("name");
	m_frameLength = (unsigned int)pElement->Int64Attribute("frame-length");
	m_frameTimer = pElement->FloatAttribute("frame-timer");
	m_frameSwitchTime = m_frameTimer;
	m_loop = pElement->BoolAttribute("loop");
	m_path = pElement->Attribute("path");
	m_numFrames = (int)pElement->Int64Attribute("num-frames");
	m_pActor = pActor;
	
	
	return true;
}

void slth::AnimationProcess::Resume()
{
	
	// we're overriding the sprite's texture name so that it can be called
	// so we need to check if that's already the case, and if not, do it
	if (m_pSpriteComp->GetName() != m_name)
	{
		// ... and store what it was so that it can be restored when this process finishes
		m_previousName = m_pSpriteComp->GetName();
		//m_pSpriteComp->SetName(m_name);
	}

	m_state = State::kRunning;
	m_pActor->GetComponent<AnimationComponent>()->SetRunning(this);
	
}


