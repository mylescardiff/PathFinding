#pragma once
/** \file SFMLGraphics.h */

// Created by Myles Cardiff
#include <Graphics/IGraphics.h>
#include <Application/Window/IWindow.h>
#include <Graphics/SFMLTexture.h>
#include <Utilities/Color.h>
#include <Utilities/RectFloat.h>
#include <memory>

//! \namespace Sloth Engine
namespace slth
{
/** \class SFMLGraphics */
/** SFML version of the graphics system */
	class SFMLGraphics
	: public IGraphics
{
public:
	
	/** Default Destructor */
	virtual ~SFMLGraphics();

	/** Initializes the graphics system */
	virtual bool Init(IWindow* pWindow) override;

	/** Clears the screen */
	virtual void StartDrawing() override;

	/** Renders / presents the screen (flips the buffers) */
	virtual void EndDrawing() override;

	/** Creates the graphics system */
	virtual IGraphics* Create();

	/** Draws a pre-loaded texture */
	virtual void DrawTexture(const char* name, RectInt destinationRect, RectInt textureRect, bool flip, float rotation, Vector2f origin, bool repeat, float scaleFactor) const override;
	
	virtual void DrawSfTexture(sf::Texture& texture, RectInt destinationRect, RectInt textureRect);

	/** Draws a colored rectangle on the screen */
	virtual void DrawRect(RectInt rect, slth::Color fillColor, slth::Color outlineColor, float outlineWeight, float rotation) const;

	/** Draws a colored circle on the screen */
	virtual void DrawCircle(Vector2f center, float radius, slth::Color fillColor, slth::Color outlineColor, float outlineWeight) const;

	/** Draws a line */
	virtual void DrawLine(Vector2f pointA, Vector2f pointB, slth::Color color);

	/** Draws a colored polygon on the screen */
	virtual void DrawPolygon(Vector2f center, std::vector<Vector2f> points, slth::Color fillColor, slth::Color outlineColor, float outlineWeight) const;

	/** Draws a single pixel */
	virtual void DrawPoint(Vector2f center, slth::Color color);

	/** Write text on the screen */
	virtual void DrawText(const char* text, slth::Vector2f position, int size, slth::Color color) const override;

	/** Set the camera's center position */
	virtual void SetCameraPosition(float x, float y);

	/** Set the camera's zoom level*/
	virtual void SetCameraZoom(float level);

	/** Set the camera's size */
	virtual void SetCameraSize(slth::Vector2f size);

	/** Set the camera's viewport */
	virtual void SetCameraViewport(slth::RectFloat size);

	/** Set the camera's default view */
	virtual void SetCameraDefault();

	/** Loads a texture */
	void LoadTexture(const char* filename);

	SLTH_API void LoadTexture(sf::Image& image, const char* name);

	/** Get texture using the name it was loaded under */
	SFMLTexture* GetTextureByName(const char* name) const;

	IWindow* GetWindow() const { return m_pWindow; }

	

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	IWindow* m_pWindow = nullptr;
	std::map<size_t, SFMLTexture*> s_textureList;
	sf::Font m_font;
	sf::View m_cameraView;
	sf::RenderWindow* m_pNativeWindow;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}