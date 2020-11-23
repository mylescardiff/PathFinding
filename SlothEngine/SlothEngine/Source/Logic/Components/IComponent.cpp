#include "IComponent.h"





void slth::IComponent::RegisterWithLua(lua_State * pState, const char* name)
{
	// assumes that the component table of the owning actor is on the top of the stack
	lua_newtable(pState);

	lua_pushlightuserdata(pState, this);
	lua_setfield(pState, -2, "this");

	luaL_getmetatable(pState, name);
	lua_setmetatable(pState, -2);

	// Register on to the actor.component (You might wanna make a function or do this automagically)
	lua_setfield(pState, -2, name);

}