#include "SDLRenderer.h"
#include "../../SGEngine/Engine/Logger.h"

#include <cassert>
#include <SDL/SDL.h>

extern "C" {
	#include "lua5.1/lua.h"
	#include "lua5.1/lualib.h"
	#include "lua5.1/lauxlib.h"
}

SDLRenderer::SDLRenderer(lua_State*)
: screenSurface_(0)
, backBufferRect_()
{
}

SDLRenderer::~SDLRenderer()
{
	SDL_FreeSurface(screenSurface_);
	screenSurface_ = 0;
}

int SDLRenderer::createWindow(lua_State* pState)
// (const std::string& pTitle, const Uint32 pWidth, const Uint32 pHeight, const Uint32 pBPP, const Uint32 pFlags)
{
	/** This creates a window with the title named. */
	Logger& logger(Logger::instance());
	
	const int parameters(lua_gettop(pState));
	if (6 != parameters) { // we don't have 5 parameters.. something's obviously wrong here... extra parameter is the library
		logger.log("SDLRenderer::createWindow - we were not given 5 parameters.\n", Logger::LOG_TYPE_ERROR);
		lua_pop(pState, parameters);
		return 0;
	}
	
	assert(lua_isstring(pState, -5));
	assert(lua_isnumber(pState, -4));
	assert(lua_isnumber(pState, -3));
	assert(lua_isnumber(pState, -2));
	assert(lua_isnumber(pState, -1));
	
	const std::string title(lua_tostring(pState, -5));
	const Uint32 width(lua_tonumber(pState, -4));
	const Uint32 height(lua_tonumber(pState, -3));
	const Uint32 bpp(lua_tonumber(pState, -2));
	const Uint32 flags(lua_tonumber(pState, -1));
	
	/// Creating Window
	screenSurface_ = SDL_SetVideoMode(width, height, bpp, flags);
	if(!screenSurface_)
	{
		logger.log("Could not create SDL Screen.\n", Logger::LOG_TYPE_ERROR);
		logger.log(std::string(SDL_GetError()), Logger::LOG_TYPE_ERROR);
		return 0;
	}

	/// Set the Window Title
	SDL_WM_SetCaption(title.c_str(), title.c_str());

	/// Setup the Back Buffer Rect
	backBufferRect_.x=0U;
	backBufferRect_.y=0U;
	backBufferRect_.w=width;
	backBufferRect_.h=height;
	
	return 0;
}

const char SDLRenderer::className[] = "SDLRenderer";
const Luna<SDLRenderer>::RegType SDLRenderer::Register[] = {
	{ "createWindow", &SDLRenderer::createWindow },
	{ 0, 0 }
};
