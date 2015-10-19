#include "SGELuaCore.h"
#include "../../SGEngine/Engine/Logger.h"

#include <iostream>
extern "C" {
	#include <lua5.1/lua.h>
	#include <lua5.1/lauxlib.h>
	#include <lua5.1/lualib.h>
}

SGELuaCore::SGELuaCore()
: luaState(0)
{
	
}

SGELuaCore::~SGELuaCore()
{
	lua_close(luaState);
}

void SGELuaCore::bootstrap(Linker* pLinker)
{
	luaState = lua_open();
	luaL_openlibs(luaState);
	linker = pLinker;
}

void SGELuaCore::run(const char* script)
{
	Logger& logger(Logger::instance());
	
	logger.log("Running Script: " + std::string(script) + "\n");
	
	if (luaL_loadfile(luaState, script) != 0) {
		logger.log(lua_tostring(luaState, -1), Logger::LOG_TYPE_ERROR);
		return;
	}
	
	if (lua_pcall(luaState, 0, 0, 0) != 0) {
		logger.log(lua_tostring(luaState, -1), Logger::LOG_TYPE_ERROR);
		lua_pop(luaState, 1);
	}
}

extern "C" SGECORE* create() {
    return new SGELuaCore;
}

extern "C" void destroy(SGECORE* SGECore) {
    delete SGECore;
}