
#include "IKeyboard.h"
#include "IKeyboard.gen.h"

int glua::IKeyboard_IsKeyDown(lua_State* pState)
{
	using namespace slth;
	slth::IKeyboard* pIKeyboard = reinterpret_cast<IKeyboard*>(lua_touserdata(pState, 1));
	int keyCode = (int)lua_tonumber(pState, 2);
	bool value = pIKeyboard->IsKeyDown((IKeyboard::KeyCode)keyCode);
	lua_pushboolean(pState, value);
	return 1;
}
int glua::IKeyboard_IsKeyPressed(lua_State* pState)
{
	using namespace slth;
	slth::IKeyboard* pIKeyboard = reinterpret_cast<IKeyboard*>(lua_touserdata(pState, 1));
	int keyCode = (int)lua_tonumber(pState, 2);
	bool value = pIKeyboard->IsKeyPressed((IKeyboard::KeyCode)keyCode);
	lua_pushboolean(pState, value);
	return 1;
}