#pragma once
/** \file SFMLWindow.h */

// Created by Myles Cardiff

#include <stdint.h>
#include "IWindow.h"
#include <SFML/Graphics.hpp>

//! \namespace Engine Contains all Engine code
namespace slth
{
/** \class SFMLWindow */

class SFMLWindow : public IWindow
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	SFMLWindow();

	/** Default Destructor */
	~SFMLWindow();

	/** Creates the SFML Window */
	virtual bool Init(const char* title, u32 width, uint32_t height, IKeyboard* pKeyboard, IMouse* pMouse) override;

	/** Polls events like clicks, keyboard presses, etc */
	virtual bool ProcessEvents() const override;

	/** Returns the pointer to the SFML window */
	virtual void* GetNativeWindow() override { return m_pWindow; }

	/** Goes to the next frame */
	virtual void NextFrame() const override;

	/** Detects weather the SFML window is currently open or not */
	virtual bool IsOpen() override;

	/** Clear the screen */
	virtual void Clear() override;

	/** Display the render window / flip buffer */
	virtual void Display() override;

	sf::RenderWindow* GetRenderWindow() { return m_pWindow;  }

	virtual void Close() override;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	sf::RenderWindow* m_pWindow;
	
	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


	/** Sets the title of the application window */
	SLTH_API virtual void SetTitle(const char* title);

};
}