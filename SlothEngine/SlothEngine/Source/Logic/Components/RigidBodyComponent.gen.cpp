#pragma once
#include "RigidBodyComponent.gen.h"
#include "RigidBodyComponent.h"

int glua::RigidBodyComponent_ApplyLinearImpulse(lua_State* pState)
{
	using namespace slth;
	// there is currently a table on top of the stack...
	// ..this line takes a field called "this" from that table, which contains a memory address of the component...
	lua_getfield(pState, 1, "this");
	
	// ... this takes that pointer and casts it to a usable component
	slth::RigidBodyComponent* pRigidBodyComponent = reinterpret_cast<RigidBodyComponent*>(lua_touserdata(pState, -1)); 

	// .. this removes the pointer from the stack, becuase we don't need it anymore
	lua_pop(pState, 1);

	// ... now get the arguments (table is still on top of stack)
	float x = (float)lua_tonumber(pState, 2);
	float y = (float)lua_tonumber(pState, 3);
	pRigidBodyComponent->ApplyLinearImpulse(x, y);
	return 0;
}