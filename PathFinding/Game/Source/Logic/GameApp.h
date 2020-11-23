#pragma once

#include <Application/ApplicationLayer.h>

/// <summary>
/// Application layer for GAP 321 game project
/// </summary>
class GameApp : public  slth::ApplicationLayer
{
public: 

	/// <summary>
	/// Create the application
	/// </summary>
	/// <returns>A pointer to the newly created application Layer</returns>
	virtual slth::ApplicationLayer* Create() override;

	/// <summary>
	/// Initialize the application
	/// </summary>
	/// <returns>True if initialization succeeded, false if it fails</returns>
	virtual bool Init() override;
};