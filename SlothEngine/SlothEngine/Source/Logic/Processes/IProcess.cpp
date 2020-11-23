#include "IProcess.h"

using slth::IProcess;

IProcess::IProcess()
	: m_state(State::kUnintialized)
{
	
}

IProcess::~IProcess()
{
	
}



IProcess* slth::IProcess::RemoveChildProcess()
{

	return m_pChild;
}

bool slth::IProcess::IsDead() const
{
	 return (m_state == State::kAborted || 
		 m_state == State::kFailed || 
		 m_state == State::kSucceeded); 
}
