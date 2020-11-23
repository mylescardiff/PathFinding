#pragma once
namespace glua
{
	int Foo_Test(lua_State* pState);
	int Foo_GetTestPointer(lua_State* pState);
	int Foo_FunctionThatDoesNothing(lua_State* pState);

}