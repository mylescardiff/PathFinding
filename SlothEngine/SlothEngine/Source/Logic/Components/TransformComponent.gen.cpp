#pragma once
#include "TransformComponent.gen.h"
#include "TransformComponent.h"

int glua::TransformComponent_Move(lua_State* pState)
{
	using namespace slth;
	lua_getfield(pState, 1, "this");
	slth::TransformComponent* pTransformComponent = reinterpret_cast<TransformComponent*>(lua_touserdata(pState, -1));
	lua_pop(pState, 1);
	float x = (float)lua_tonumber(pState, 2);
	float y = (float)lua_tonumber(pState, 3);
	pTransformComponent->Move(x, y);
	return 0;
}