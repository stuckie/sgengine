// Welcome to the brand spanky new SGEngine main.cpp file!
// If you're reading this, you've more time on your hands than I do...

#if defined(__LINUX__)
	#include <dlfcn.h>
#elif defined(__WIN32__)
	#include <windows.h>
#endif

#include <iostream>
#include <string>

#include "Linker.h"
#include "Logger.h"
#include "Interfaces/SGECORE.h"

int main(int argc, const char* argv[])
{
	Logger& logger(Logger::instance());
	logger.setFile(".html", Logger::LOG_FILE_HTML);
	logger.setOutput(Logger::LOG_OUTPUT_FILE_AND_TERMINAL);
	logger.setType(Logger::LOG_TYPE_INFO);
	
	// Check we've been given everything we need on the command line, and try defaults if possible
	std::string config("config.cfg");
	std::string script("main.lua");
	
	if (argc == 3) { // <engine> <script> <config>
		script = argv[1];
		config = argv[2];
	}
	else if (argc == 2) { // <engine> <script>
		script = argv[1];
		logger.log("No config file given, using default of config.cfg\n");
	}
	else if (argc < 2) { // <engine>
		logger.log("No parameters given, using defaults of config.cfg and main.lua\n");
	}
	
	Linker linker;
	if (false == linker.loadConfig(config)) {
		logger.log("Failed to load configuration file, either pass it as a parameter or ensure config.cfg exists..\n", Logger::LOG_TYPE_ERROR);
		return -1;
	}
	
	// We need to load up a few libraries, in order of priority, really... so we need CORE as everything depends on it.
	SGECORE* SGECore(linker.loadCore());
	if (!SGECore) {
		logger.log("Failed to load SGECore library.. this is absolutely needed so we're bailing now.\n", Logger::LOG_TYPE_ERROR);
		return -1;
	}
	else {
		logger.log("Loaded SGECore: " + std::string(SGECore->libName()) + "\n", Logger::LOG_TYPE_DEBUG);
	}
	
	// Load whatever else we found in the config.
	linker.loadLibs();
	
	// We then call CORE to bootstrap itself, and the other libraries, to our environment.
	// By this method, each library can expose literally whatever the hell it likes to Lua, it only needs to have a matching CORE.
	// This allows SGEngine to actually support a multitude of scripting languages at a later date.
	SGECore->bootstrap(&linker);
	linker.bootstrapLibs(SGECore);
	
	// Run the script we've been given - it controls our main loop.
	SGECore->run(script.c_str());
	
	// If our script is finished, we just shut down in reverse order..
	linker.unloadLibs();
	
	// Now eject the core!
	linker.unloadCore(SGECore);
	
	// Goodbye World
	return 0;
}
