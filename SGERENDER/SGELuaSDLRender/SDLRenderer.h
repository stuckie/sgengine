#ifndef _SDL_RENDERER_H_
#define _SDL_RENDERER_H_

#include "../../SGECORE/SGELuaCore/Luna.h"
#include <SDL/SDL.h>
#include <string>

struct lua_State;
class SDLRenderer
{
	public:
		static const char className[];
        static const Luna<SDLRenderer>::RegType Register[];
	
		SDLRenderer(lua_State* pState);
		~SDLRenderer();
		
		//! void createWindow(Title, Width, Height, BPP, Flags);
		int createWindow(lua_State* pState);
		
	protected:
		
	private:
		SDL_Surface *screenSurface_;	//!< Pointer to our Screen
		SDL_Rect backBufferRect_;		//!< Our Back Buffer
};

#endif
