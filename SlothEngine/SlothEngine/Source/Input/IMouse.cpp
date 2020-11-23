#include "IMouse.h"
#include "IMouse.gen.h"
#include <cassert>
#include <Utilities/DateTime.h>

using slth::IMouse;
#define _CHECK_BUTTON(button) assert(button >= 0 && button <= (int)IMouse::MouseButton::kNumButtons)

slth::IMouse::IMouse()
{
	ClearAllButtons();
}

void slth::IMouse::RegisterWithLuaState(lua_State* pState)
{
	// push necessary functions to lua
	lua_pushlightuserdata(pState, this);
	lua_setglobal(pState, "mouse");

	// get actor
	lua_pushcfunction(pState, &glua::IMouse_IsButtonDown);
	lua_setglobal(pState, "isButtonDown");

	// kill actor
	lua_pushcfunction(pState, &glua::IMouse_IsButtonPressed);
	lua_setglobal(pState, "isButtonPressed");
}

bool slth::IMouse::IsDoubleClicked(MouseButton button)
{
	_CHECK_BUTTON((int)button);
	int timeDifference = m_buttonData[(size_t)button].m_pressedTimes[0] - m_buttonData[(size_t)button].m_pressedTimes[1];

	bool result = timeDifference > 0 && timeDifference < kDoubleClickThreshold;
	if (result)
	{
		m_buttonData[(size_t)button].m_pressedTimes[0] = 0;
		m_buttonData[(size_t)button].m_pressedTimes[1] = 0;
		m_buttonData[(size_t)button].m_pressedTimes[2] = 0;
	}
	return result;

}

bool slth::IMouse::IsTripleClicked(MouseButton button)
{
	_CHECK_BUTTON((int)button);
	int timeDifference = m_buttonData[(size_t)button].m_pressedTimes[0] - m_buttonData[(size_t)button].m_pressedTimes[2];

	// time is doubled here because two triple click is twice the double click threshold
	return timeDifference > 0 && timeDifference < (kDoubleClickThreshold * 2); 
	
}

void slth::IMouse::SetButton(MouseButton button, bool down)
{
	std::string buttonName = "Left";
	if ((int)button == 1)
	{
		buttonName = "Right";
	}
	std::string buttonAction = "clicked";
	if (!down)
	{
		buttonAction = "released";
	}

	if (down)
	{
		// move the pressed time recordings up one spot, so that the most recent one is always at position 0
		m_buttonData[(size_t)button].m_pressedTimes[1] = m_buttonData[(size_t)button].m_pressedTimes[0];
		m_buttonData[(size_t)button].m_pressedTimes[2] = m_buttonData[(size_t)button].m_pressedTimes[1];
		m_buttonData[(size_t)button].m_pressedTimes[0] = static_cast<u32>(DateTime::TickTimestamp());
		
	}
		
	else
	{
		// mouse released
	
	}

	_CHECK_BUTTON((int)button);
	m_buttonData[(size_t)button].m_pressed = down;
	if (down)
	{
		m_buttonData[(size_t)button].m_down = true;
		
	}
	else
	{
		m_buttonData[(size_t)button].m_down = false;
	}
}

void slth::IMouse::ClearAllButtons()
{
	for (size_t i = 0; i < (size_t)MouseButton::kNumButtons; ++i)
	{
		m_buttonData[i].m_pressed = false;
	
	}
}
