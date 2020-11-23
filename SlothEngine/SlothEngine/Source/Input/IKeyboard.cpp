#include "IKeyboard.h"
#include "IKeyboard.gen.h"
#include <cassert>
#include <Logger/Logger.h>

using slth::IKeyboard;

#define _CHECK_KEYCODE(keyCode) assert(keyCode >= 0 && keyCode <= kNumKeys)


//slth::KeyData slth::IKeyboard::m_keyData[kNumKeys];

slth::IKeyboard::IKeyboard()
{
	for (int i = 0; i < kNumKeys; ++i)
	{
		m_keyData[i].m_down = false;
		m_keyData[i].m_pressed = false;
	}

}

void slth::IKeyboard::RegisterWithLuaState(lua_State* pState)
{
	// push necessary functions to lua
	lua_pushlightuserdata(pState, this);
	lua_setglobal(pState, "keyboard");

	// get actor
	lua_pushcfunction(pState, &glua::IKeyboard_IsKeyDown);
	lua_setglobal(pState, "isKeyDown");

	// kill actor
	lua_pushcfunction(pState, &glua::IKeyboard_IsKeyPressed);
	lua_setglobal(pState, "isKeyPressed");
}

bool slth::IKeyboard::IsKeyDown(KeyCode keyCode)
{
	_CHECK_KEYCODE((int)keyCode);
	return m_keyData[(size_t)keyCode].m_down;
}

bool slth::IKeyboard::IsKeyPressed(KeyCode keyCode)
{
	_CHECK_KEYCODE((int)keyCode);
	return m_keyData[(size_t)keyCode].m_pressed;
}

void slth::IKeyboard::ClearKey(KeyCode keyCode)
{
	_CHECK_KEYCODE((int)keyCode);
	m_keyData[(size_t)keyCode].m_pressed = false;
}

void slth::IKeyboard::ClearAllKeys()
{
	for (size_t i = 0; i < kNumKeys; ++i)
	{
		m_keyData[i].m_pressed = false;
	}
}

void slth::IKeyboard::SetKey(KeyCode keyCode, bool down)
{
	_CHECK_KEYCODE((int)keyCode);
	m_keyData[(size_t)keyCode].m_pressed = down;
	m_keyData[(size_t)keyCode].m_down = down;

	//if (down)
	//	_LOGI("Key Press: " + std::to_string(keyCode));
	//else
	//	_LOGI("Key Released: " + std::to_string(keyCode));
	
	

}
