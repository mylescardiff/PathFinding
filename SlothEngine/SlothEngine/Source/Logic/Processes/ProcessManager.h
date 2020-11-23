#pragma once
/** \file ProcessManager.h */

// Created by Myles Cardiff

#include <vector>
#include <Logic/Processes/IProcess.h>
#include <Common.h>

//! \namespace Sloth Engine
namespace slth
{
	class IGraphics;
	class AnimationProcess;
	class Actor;
/** \class ProcessManager */

class ProcessManager
{
	
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	SLTH_API ProcessManager();

	/** Default Destructor */
	SLTH_API ~ProcessManager();

	

	SLTH_API void AttachProcess(IProcess* pProcess) { m_processes.emplace_back(pProcess); }
	SLTH_API void UpdateProcesses(float deltaTime);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	std::vector<IProcess*> m_processes;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	void AbortAllProcesses();

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}