#pragma once
/** \file IKeyboard.h */
/** Detects and holds keys pressed and down from the keyboard. (This is not a true interface, but you could inherit and override it) */
// Created by Myles Cardiff

#include <stdint.h>
#include "KeyMap.h"
#include <Common.h>

//! \namespace Sloth
namespace slth
{
	constexpr u32 kNumKeys = 999;

/** \class IKeyboard */
/** Base keyboard interface, provides basic key press and key down data */
class IKeyboard
{
public:

	enum class KeyCode
	{
		A = 0, B, C,
		D, E, F, G,
		H, I, J, K,
		L, M, N, O,
		P, Q, R, S,
		T, U, V, W,
		X, Y, Z, Num0,
		Num1, Num2, Num3, Num4,
		Num5, Num6, Num7, Num8,
		Num9, Esc, LControl, LShift,
		LAlt, LSystem, RControl, RShift,
		RAlt, RSystem, Menu, LBracket,
		RBracket, Semicolon, Comma, Period,
		Quote, Slash, Backslash, Tilde,
		Equal, Hyphen, Space, Enter,
		Backspace, Tab, PageUp, PageDown,
		End, Home, Insert, Delete,
		Add, Subtract, Multiply, Divide,
		Left, Right, Up, Down,
		Numpad0, Numpad1, Numpad2, Numpad3,
		Numpad4, Numpad5, Numpad6, Numpad7,
		Numpad8, Numpad9, F1, F2,
		F3, F4, F5, F6,
		F7, F8, F9, F10,
		F11, F12, F13, F14,
		F15, Pause, KeyCount, Dash = Hyphen,
		BackSpace = Backspace, BackSlash = Backslash, SemiColon = Semicolon,
		NumberOfKeys
	};

	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	IKeyboard();

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	/** Register all necesary functions with lua state */
	SLTH_API void RegisterWithLuaState(lua_State* pState);

	/** Detects if a key is currently being held down */
	GLUA()
	SLTH_API bool IsKeyDown(KeyCode keyCode);

	/** Detects if a key was pressed during this frame */
	GLUA()
	SLTH_API bool IsKeyPressed(KeyCode keyCode);

	/** Clears a single key press data, leaves key down in place */
	SLTH_API void ClearKey(KeyCode keyCode);

	/** Clears all key pressed data, leaves key down in place */
	SLTH_API void ClearAllKeys();

	/** Sets the key state for a single key */
	SLTH_API void SetKey(KeyCode keyCode, bool down);

	

protected:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	struct KeyData
	{
		bool m_pressed;
		bool m_down;
		u32 m_pressedTime;
	};
	KeyData m_keyData[kNumKeys];

	//static bool s_anyPressed;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}