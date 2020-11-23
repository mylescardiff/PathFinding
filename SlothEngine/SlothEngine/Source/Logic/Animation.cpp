#include "Animation.h"
#include <Graphics/IGraphics.h>
#include <Logic/Processes/AnimationProcess.h>




void slth::Animation::Init(XmlData* pElement)
{
	m_name = pElement->Attribute("name");
	m_frameLength = (unsigned int)pElement->Int64Attribute("frame-length");
	m_frameTimer = pElement->FloatAttribute("frame-timer");
	m_loop = pElement->BoolAttribute("loop");
	m_numFrames = (int)pElement->Int64Attribute("num-frames");
	m_path = pElement->Attribute("path");
}

slth::AnimationProcess* slth::Animation::CreateProcess()
{
	return new AnimationProcess(m_name, m_frameLength, m_frameTimer, m_numFrames, m_loop);
}


