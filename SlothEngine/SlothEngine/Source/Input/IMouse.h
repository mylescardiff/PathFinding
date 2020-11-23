#pragma once
/** \file IMouse.h */
/** Detects and holds button pressed and down from the mouse. (This is not a true interface, but you could inherit and override it) */
// Created by Myles Cardiff

#include <stdint.h>
#include <Logger/Logger.h>
#include <Utilities/Vector2f.h>

//! \namespace Sloth
namespace slth
{
/** \class IMouse */
/** Base mouse interface, provides basic button press and button down data */
class IMouse
{

public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	enum class MouseButton
	{
		Left,
		Right,
		Middle,
		kNumButtons

	};

	struct MousePosition
	{
		u32 x;
		u32 y;

		slth::Vector2f ToVector2f()
		{
			return Vector2f((float)x, (float)y);
		}
		
	};

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Default Constructor */
	IMouse();

	/** Detect if the specified mouse button was pressed in this frame */
	GLUA()
	SLTH_API bool IsButtonPressed(MouseButton button) {
		return m_buttonData[(size_t)button].m_pressed; 
	}

	/** Detect if the specified mouse button is being held down */
	GLUA()
	SLTH_API bool IsButtonDown(MouseButton button) { return m_buttonData[(size_t)button].m_down; }

	void RegisterWithLuaState(lua_State* pState);

	/** Detect if the specified mouse button was double clicked in this frame */
	SLTH_API bool IsDoubleClicked(MouseButton button);

	/** Detect if the specified mouse button was triple clicked in this frame */
	SLTH_API bool IsTripleClicked(MouseButton button);

	/** Set the specified button's state */
	SLTH_API void SetButton(MouseButton button, bool down);

	/** Clear all the button's pressed states */
	SLTH_API void ClearAllButtons();

protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	struct ButtonData
	{
		bool m_pressed = false;
		bool m_down = false;
		u32 m_pressedTimes[3] = { 0, 0, 0 };
		
	};

	MousePosition m_position;
	ButtonData m_buttonData[(size_t)MouseButton::kNumButtons];
	constexpr static int kDoubleClickThreshold = 250;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	/** Return the current position of the mouse */
	MousePosition GetPosition() { return m_position; }

	/** Set the current position of the mouse */
	void SetPosition(u32 x, u32 y) { m_position.x = x; m_position.y = y; } // two lines but so simple I'm leaving it in .h file.

	
};

}