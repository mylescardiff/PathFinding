#pragma once
/** \file IWindow.h */

// Created by Myles Cardiff

#include <Common.h>
#include <memory>
#include <stdint.h>
#include <Input/IKeyboard.h>
#include <Input/IMouse.h>

//! \namespace Engine Contains all Engine code
namespace slth
{
/** \class IWindow */

class IWindow
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Destructor */
	SLTH_API virtual ~IWindow() {}

	SLTH_API virtual bool Init(const char* title, uint32_t width, uint32_t height, IKeyboard* pKeyboard, IMouse* pMouse) = 0;
	SLTH_API virtual bool ProcessEvents() const = 0;
	SLTH_API virtual void* GetNativeWindow() = 0;
	

	/** Keyboard and mouse store frame data for next frame */
	SLTH_API virtual void NextFrame() const = 0;

	
	/** Detects weather the SFML window is currently open or not */
	SLTH_API virtual bool IsOpen() = 0;

	/** Clear the screen */
	SLTH_API virtual void Clear() = 0;

	SLTH_API virtual void Display() = 0;

	SLTH_API virtual void Close() = 0;

protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //
	IKeyboard* m_pKeyboard;
	IMouse* m_pMouse;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
	


	/** Sets the title of the application window */ 
	SLTH_API virtual void SetTitle(const char* title) = 0;

};
}