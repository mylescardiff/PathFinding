#pragma once
#include "IGameLayer.gen.h"
#include "IGameLayer.h"

int glua::IGameLayer_FindActor(lua_State* pState)
{
	using namespace slth;
	//TODO: Removing std::string search messed this up, fix it
	slth::IGameLayer* pIGameLayer = reinterpret_cast<IGameLayer*>(lua_touserdata(pState, 1));
	Id32 id = (Id32)lua_tonumber(pState, 2);
	Actor * value = pIGameLayer->FindActor(id);
	lua_pushlightuserdata(pState, value);
	return 1;
}

int glua::IGameLayer_KillActor(lua_State* pState)
{
	using namespace slth;
	slth::IGameLayer* pIGameLayer = reinterpret_cast<IGameLayer*>(lua_touserdata(pState, 1));
	Id32 id = (int)lua_tonumber(pState, 2);
	pIGameLayer->KillActor(id);
	return 0;
}

