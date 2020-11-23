#pragma once
/** \file Animation.h */
// Created by Myles Cardiff

#include <Common.h>
#include <string>
#include <unordered_map>

namespace slth
{
	class IGraphics;
	class IProcess;
	class AnimationProcess;

/// <summary>
/// Holds a single animation 
/// </summary>
class Animation
{
public:

	/// <summary>
	/// Initialize the Animation from an XML node
	/// </summary>
	/// <param name="pElement">Pointer to the XML node</param>
	SLTH_API void Init(XmlData* pElement);

	/// <summary>
	/// Creates an animation process to hand to the ProcessManager
	/// </summary>
	/// <returns>A pointer to the newly created process</returns>
	SLTH_API AnimationProcess* CreateProcess();


private:

	std::string m_name;
	std::string m_path;
	float m_frameTimer;
	unsigned short m_frameLength;
	unsigned short m_numFrames;
	bool m_loop;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API std::string& GetPath() { return m_path; }
	SLTH_API std::string& GetName() { return m_name; }

};
}