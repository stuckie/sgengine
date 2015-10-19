#ifndef _SGELUACORE_H_
#define _SGELUACORE_H_

#include "../../SGEngine/Engine/Interfaces/SGECORE.h"

struct lua_State;
class Linker;
class SGELuaCore : public SGECORE
{
	public:
		SGELuaCore();
		~SGELuaCore();
		
		//! Return this version of SGELuaCore
		int version() const { return 100; };
		
		//! Return the name of this lib for checking against.
		const char* libName() const { return "SGELuaCore"; };
		
		//! Bootstrap the Core with this Linker
		void bootstrap(Linker* pLinker);
		
		//! Run a script through this Core
		void run(const char* script);
		
		// Core Specific Functions
		//! Return this Core's Lua State
		lua_State* getLuaState() const { return luaState; };
		
		//! This core provides access to the Linker.
		Linker* getLinker() const { return linker; };
		
	private:
		lua_State* luaState;
		Linker* linker;
};

#endif
