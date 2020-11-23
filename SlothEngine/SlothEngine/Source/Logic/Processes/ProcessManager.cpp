#include "ProcessManager.h"
#include <Logic/Processes/AnimationProcess.h>
#include <Graphics/IGraphics.h>


using slth::ProcessManager;

ProcessManager::ProcessManager()
{
	
}

ProcessManager::~ProcessManager()
{
	AbortAllProcesses();
}

void slth::ProcessManager::UpdateProcesses(float deltaTime)
{
	using State = IProcess::State;

	size_t processIndex = 0;

	while (processIndex != m_processes.size())
	{
		auto currentProcess = m_processes[processIndex];
		if (currentProcess->GetState() == IProcess::State::kRunning)
		{
			currentProcess->Update(deltaTime);
		}
		else if (currentProcess->GetState() == State::kUnintialized)
		{
			if (currentProcess->Init())
			{
				currentProcess->Resume();
			}
			else
			{
				// process has failed :(
				m_processes.erase(m_processes.begin() + processIndex); // pointer math; this slides down, so no need to increment
			}

		}

		if (currentProcess->IsDead())
		{
			if (currentProcess->GetState() == State::kSucceeded)
			{
				// process has succeeded :)
				currentProcess->OnSucceed();
				IProcess* pChild = currentProcess->RemoveChildProcess();
				if (pChild)
				{
					AttachProcess(pChild);
				}
			}
			else if (currentProcess->GetState() == State::kFailed)
			{
				currentProcess->OnFail();
			}
			else if (currentProcess->GetState() == State::kAborted)
			{
				currentProcess->OnAbort();
			}
			delete currentProcess;
			currentProcess = nullptr;
			m_processes.erase(m_processes.begin() + processIndex);
		}
		else
		{
			++processIndex;
		}

	}
}


void slth::ProcessManager::AbortAllProcesses()
{
	for (auto pProcess : m_processes)
	{
		pProcess->OnAbort();
		delete pProcess;
	}
	m_processes.clear();
}


