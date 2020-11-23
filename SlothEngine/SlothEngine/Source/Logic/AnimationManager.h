#pragma once
/** \file AnimationManager.h */

// Created by Myles Cardiff

#include <Common.h>
#include <unordered_map>

//! \namespace Sloth Engine
namespace slth
{
	class Animation;
	class IGraphics;

/// <summary>
/// Holds, starts, and managers all animations in the game
/// </summary>
class AnimationManager
{
public:

	/// <summary>
	/// Default Constructor
	/// </summary>
	AnimationManager();

	/// <summary>
	/// Default Destructor
	/// </summary>
	~AnimationManager();

	/// <summary>
	/// Finds an animation by thier id (int)
	/// </summary>
	/// <param name="id">Integer ID</param>
	/// <returns>A pointer to the animation if found, nullptr if not</returns>
	SLTH_API Animation* Find(Id id);

	/// <summary>
	/// Finds an animation by thier name (string)
	/// </summary>
	/// <param name="id">String name</param>
	/// <returns>A pointer to the animation if found, nullptr if not</returns>
	SLTH_API Animation* Find(std::string& name) { return Find((HASH(name))); }

	/// <summary>
	/// Loads animations from XML
	/// </summary>
	/// <param name="filename">The string name of the file</param>
	/// <param name="pGraphics">A pointer to the Graphics system</param>
	SLTH_API void LoadAnimations(const char* filename, IGraphics* pGraphics);

private:
	
	std::unordered_map<Id, Animation*> m_animations;

};
}