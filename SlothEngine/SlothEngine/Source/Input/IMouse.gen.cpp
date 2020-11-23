
#include "IMouse.h"
#include "IMouse.gen.h"

int glua::IMouse_IsButtonDown(lua_State* pState)
{
	using namespace slth;
	slth::IMouse* pIKeyboard = reinterpret_cast<IMouse*>(lua_touserdata(pState, 1));
	int keyCode = (int)lua_tonumber(pState, 2);
	bool value = pIKeyboard->IsButtonDown((IMouse::MouseButton)keyCode);
	lua_pushboolean(pState, value);
	return 1;
}
int glua::IMouse_IsButtonPressed(lua_State* pState)
{
	using namespace slth;
	slth::IMouse* pIMouse = reinterpret_cast<IMouse*>(lua_touserdata(pState, 1));
	int keyCode = (int)lua_tonumber(pState, 2);
	bool value = pIMouse->IsButtonPressed((IMouse::MouseButton)keyCode);
	lua_pushboolean(pState, value);
	return 1;
}