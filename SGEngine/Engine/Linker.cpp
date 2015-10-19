#if defined(__LINUX__)
	#include <dlfcn.h>
#elif defined(__WIN32__)
	#include <windows.h>
#endif

#include "Linker.h"

#include <iostream>
#include <fstream>
#include <string>
#include "Logger.h"
#include "Interfaces/SGECORE.h"
#include "Interfaces/SGELIB.h"

using std::string;
using std::ifstream;
using std::vector;

Linker::Linker()
: corePath("")
, libPaths()
, libCore(0)
, libPointers()
, libNames()
, libraries()
{
}
		
bool Linker::loadConfig(const string& pConfig)
{
	// We don't have Lua support at this stage, so let's do some manual parsing...
	ifstream configFile;
	configFile.open(pConfig.c_str(), ifstream::in);
	if (configFile.good())  {
		string libName;
		string libPath;
		
		configFile >> libName >> corePath;		// SGECore SGECore.lib
		if ((libName.compare("SGECore") != 0) || (corePath.empty())) {
			std::cerr << "Cannot find path for SGECore ... it MUST be first." << std::endl;
			return false;
		}
		std::cout << "Storing path for '" << libName << "' as: " << corePath << std::endl;
		while(!configFile.eof()) {
			configFile >> libName >> libPath; 	// LibName libPath
			if (configFile.eof())
				break;
			std::cout << "Storing path for '" << libName << "' as: " << libPath << std::endl;
			libPaths.push_back(libPath);
			libNames.push_back(libName);
		}
		
		configFile.close();
		
		return true;
	}
	else {
		configFile.close();
		return false;
	}
}

SGECORE* Linker::loadCore()
{
	#if defined(__LINUX__)
		libCore = dlopen(corePath.c_str(), RTLD_LAZY);
		if (!libCore) {
			std::cerr << "Cannot load SGECore library: " << dlerror() << std::endl;
			return NULL;
		}
		
		// load the symbols ... we use create here, but we want to ensure we can destroy it too
		createSGECORE* create((createSGECORE*) dlsym(libCore, "create"));
		destroySGECORE* destroy((destroySGECORE*) dlsym(libCore, "destroy"));
		if (!create || !destroy) {
			std::cerr << "Cannot load SGECore init/deinit symbols: " << dlerror() << std::endl;
			dlclose(libCore);
			return NULL;
		}

		// return a new instance of the class
		return create();
	#elif defined(__WIN32__)
		libCore = LoadLibrary(corePath.c_str());
		if (!libCore) {
			std::cerr << "Cannot load SGECore library: " << GetLastError() << std::endl;
			return NULL;
		}
		
		// load the symbols ... we use create here, but we want to ensure we can destroy it too
		createSGECORE* create((createSGECORE*) GetProcAddress(libCore, "create"));
		destroySGECORE* destroy((destroySGECORE*) GetProcAddress(libCore, "destroy"));
		if (!create || !destroy) {
			std::cerr << "Cannot load SGECore init/deinit symbols: " << GetLastError() << std::endl;
			FreeLibrary(libCore);
			return NULL;
		}
		
		// return a new instance of the class
		return create();
	#else
		return NULL;
	#endif
}


void Linker::loadLibs()
{
	vector<string>::const_iterator libName(libNames.begin());
	for (vector<string>::const_iterator libPath(libPaths.begin()); libPath != libPaths.end(); ++libPath, ++libName) {
		loadLibrary((*libName), (*libPath));
	}
}

void Linker::loadLibrary(const string& pLibName, const string& pLibPath)
{
	#ifdef __LINUX__
		void* libPointer(dlopen((pLibPath).c_str(), RTLD_LAZY));
		if (!libPointer) {
			std::cerr << "Cannot load library: " << dlerror() << std::endl;
			return;
		}
			
		// load the symbols ... we don't use them but we want to ensure they exist first.
		createSGELIB* create((createSGELIB*) dlsym(libPointer, "create"));
		destroySGELIB* destroy((destroySGELIB*) dlsym(libPointer, "destroy"));
		if (!create || !destroy) {
			std::cerr << "Cannot load init/deinit symbols: " << dlerror() << std::endl;
			dlclose(libPointer);
		}

		// store the pointer
		libPointers.push_back(libPointer);
			
		// create and store this library too
		libraries.push_back(create());
		
		// store the name so we can retrieve it later
		libNames.push_back(pLibName);
	#endif
}

SGELIB* Linker::getLibrary(const string& pLibName)
{
	for (unsigned int index(0U); index < libNames.size(); ++index) {
		if (pLibName == libNames.at(index)) {
			return libraries.at(index);
		}
	}
	
	return NULL;
}

void Linker::bootstrapLibs(SGECORE* pSGECore)
{
	for (vector<SGELIB*>::const_iterator library(libraries.begin()); library != libraries.end(); ++library) {
		(*library)->bootstrap(pSGECore);
	}
}

void Linker::unloadLibs()
{
	#ifdef __LINUX__
		if (!libPointers.empty()) {
			for (vector<void*>::const_iterator libPointer(libPointers.end() - 1U); libPointer != libPointers.begin(); --libPointer) {
				destroySGELIB* destroy((destroySGELIB*) dlsym((*libPointer), "destroy"));
				libraries.pop_back();
				destroy((*libraries.end()));
			}
			
			libPointers.clear();
		}
	#endif
}

void Linker::unloadCore(SGECORE* pSGECore)
{
	#ifdef __LINUX__
		destroySGECORE* destroy((destroySGECORE*) dlsym(libCore, "destroy"));
		destroy(pSGECore);
	#endif
	
	pSGECore = 0;
}
