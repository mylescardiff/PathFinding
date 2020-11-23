#include "Foo.h"
#include "Foo.gen.h"

int Foo_Test(lua_State* pState)
{
	using namespace slth;
	tdp::Foo* pFoo = reinterpret_cast<Foo>(lua_touserdata(pState, -2);
	int _myInt = (int)lua_tonumber(pState, -3));
	int _someArg = (int)lua_tonumber(pState, -2));
	float _somethingElse = (float)lua_tonumber(pState, -1));
	int value = pFoo->Test(myInt, someArg, somethingElse);
	lua_pushnumber(lua_State, value);	return 1;
}

int Foo_GetTestPointer(lua_State* pState)
{
	using namespace slth;
	tdp::Foo* pFoo = reinterpret_cast<Foo>(lua_touserdata(pState, -2);
	int _myInt = (int)lua_tonumber(pState, -3));
	int _someArg = (int)lua_tonumber(pState, -2));
	float _somethingElse = (float)lua_tonumber(pState, -1));
	Test* value = pFoo->GetTestPointer(myInt, someArg, somethingElse);
	lua_pushlightuserdata(value);
	return 1;
}

int Foo_FunctionThatDoesNothing(lua_State* pState)
{
	using namespace slth;
	tdp::Foo* pFoo = reinterpret_cast<Foo>(lua_touserdata(pState, -2);
	int _myInt = (int)lua_tonumber(pState, -3));
	int _someArg = (int)lua_tonumber(pState, -2));
	float _somethingElse = (float)lua_tonumber(pState, -1));
	pFoo->FunctionThatDoesNothing(myInt, someArg, somethingElse);
	return 0;
}

