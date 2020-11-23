#pragma once

struct lua_State;

namespace glua
{
	int IGameLayer_FindActor(lua_State* pState);
	int IGameLayer_KillActor(lua_State* pState);
}