#include "SGELuaSDLRender.h"
#include "SDLRenderer.h"
#include "../../SGEngine/Engine/Logger.h"
#include "../../SGECORE/SGELuaCore/Luna.h"
#include "../../SGECORE/SGELuaCore/SGELuaCore.h"

#include <iostream>
#include <string>

extern "C" {
	#include <lua5.1/lua.h>
	#include <lua5.1/lauxlib.h>
	#include <lua5.1/lualib.h>
}

SGELuaSDLRender::SGELuaSDLRender()
{
	
}

SGELuaSDLRender::~SGELuaSDLRender()
{
}

void SGELuaSDLRender::bootstrap(SGECORE* SGECore)
{
	Logger& logger(Logger::instance());
	if (!SGECore) {
		logger.log("SGECore is a null pointer... something's gone very wrong.", Logger::LOG_TYPE_ERROR);
		return;
	}
	else if (SGECore->version() != 100) {
		logger.log("SGELuaSDLRender requires an SGECore of version 100.", Logger::LOG_TYPE_ERROR);
		return;
	}
	else if (std::string("SGELuaCore").compare(SGECore->libName()) != 0) {
		logger.log("SGELuaSDLRender currently only accepts SGELuaCore.", Logger::LOG_TYPE_ERROR);
		return;
	}
	else {
		logger.log("SGELuaSDLRender will bind with this SGECore.", Logger::LOG_TYPE_DEBUG);
		lua_State* luaState(static_cast<SGELuaCore*>(SGECore)->getLuaState());
		
		Luna<SDLRenderer>::Register(luaState);
	}
}

extern "C" SGELIB* create() {
    return new SGELuaSDLRender;
}

extern "C" void destroy(SGELIB* SGELib) {
    delete SGELib;
}