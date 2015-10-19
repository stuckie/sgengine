#ifndef _SGELUASDLRENDER_H_
#define _SGELUASDLRENDER_H_

#include "../../SGEngine/Engine/Interfaces/SGELIB.h"

class SGECORE;
class SGELuaSDLRender : public SGELIB
{
	public:
		SGELuaSDLRender();
		~SGELuaSDLRender();
		
		int version() const { return 100; };
		const char* libName() const { return "SGELuaSDLRender"; };
		
		void bootstrap(SGECORE* SGECore);
};

#endif
