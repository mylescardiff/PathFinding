#pragma once

struct lua_State;

namespace glua
{
	int IMouse_IsButtonDown(lua_State* pState);
	int IMouse_IsButtonPressed(lua_State* pState);

}