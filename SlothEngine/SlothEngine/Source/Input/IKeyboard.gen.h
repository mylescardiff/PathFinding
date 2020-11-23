#pragma once

struct lua_State;

namespace glua
{
	int IKeyboard_IsKeyDown(lua_State* pState);
	int IKeyboard_IsKeyPressed(lua_State* pState);
	
}