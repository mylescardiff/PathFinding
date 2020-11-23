#pragma once
/** \file IGraphics.h */

// Created by Myles Cardiff

#include <memory>
#include <Application/Window/IWindow.h>
#include <Graphics/ITexture.h>
#include <Utilities/RectInt.h>
#include <Utilities/RectFloat.h>
#include <Utilities/Color.h>
#include <Utilities/Vector2f.h>

//! \namespace Sloth Engine
namespace slth
{
/** \class IGraphics */
/** Interface for all graphics systems */
class IGraphics
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	virtual ~IGraphics() {}

	/** Initializes the graphics system */
	virtual bool Init(IWindow* pWindow) = 0;
	
	/** Clears the screen */
	virtual void StartDrawing() = 0; 
	
	/** Renders / presents the screen (flips the buffers) */
	virtual void EndDrawing() = 0;
	
	/** Creates the graphics system */
	virtual IGraphics* Create() = 0;

	/** Loads a texture */
	virtual void LoadTexture(const char* filename) = 0; 

	/** Write text on the screen */
	virtual void DrawText(const char* text, slth::Vector2f position, int size, slth::Color color) const = 0;

	/** Draws a texture , with repeat */
	virtual void DrawTexture(const char* name, RectInt destinationRect, RectInt textureRect, bool flip, float rotation, Vector2f origin, bool repeat, float scaleFactor) const = 0;

	/** Draws a texture */
	SLTH_API virtual void DrawTexture(const char* name, RectInt destinationRect, RectInt textureRect, bool flip, float rotation, Vector2f origin) const
	{
		DrawTexture(name, destinationRect, textureRect, flip, rotation, origin, false, 1.f);
	}

	/** Draws a rectangle */
	virtual void DrawRect(RectInt rect, slth::Color fillColor, slth::Color outlineColor, float outlineWeight, float rotation) const = 0;

	/** Draws a circle */
	virtual void DrawCircle(Vector2f center, float radius, slth::Color fillColor, slth::Color outlineColor, float outlineWeight) const = 0;

	/** Draws a line */
	virtual void DrawLine(Vector2f pointA, Vector2f pointB, slth::Color color) = 0;
	
	/** Draws a polygon */
	virtual void DrawPolygon(Vector2f center, std::vector<Vector2f> points, slth::Color fillColor, slth::Color outlineColor, float outlineWeight) const = 0;

	/** Draws a single pixel */
	virtual void DrawPoint(Vector2f center, slth::Color color) = 0;

	/** Set the camera's center position */
	virtual void SetCameraPosition(float x, float y) = 0;

	/** Set the camera's zoom level*/
	virtual void SetCameraZoom(float level) = 0;
	
	/** Set the camera's size */
	virtual void SetCameraSize(slth::Vector2f size) = 0;

	/** Set the camera's viewport */
	virtual void SetCameraViewport(slth::RectFloat size) = 0;

	/** Set the camera's default view */
	virtual void SetCameraDefault() = 0;

	

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	IWindow* m_pWindow;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	SLTH_API virtual void* GetNativeWindow() { return m_pWindow->GetNativeWindow(); }
};
}