#ifndef _LINKER_H_
#define _LINKER_H_

#include <string>
#include <vector>

#if defined(__LINUX__)
	typedef void* libraryINST;
#elif defined(__WIN32__)
	typedef HINSTANCE libraryINST;
#endif

class SGECORE;
class SGELIB;
class Linker {
	public:
		Linker();
		
		//! Loads a set of libraries via a configuration file
		bool loadConfig(const std::string& pConfig);
		
		//! Loads and returns the first Core
		SGECORE* loadCore();
		
		//! Loads all Libraries gathered from configuration files
		void loadLibs();
		
		//! Loads a specific library with the given name and path.
		void loadLibrary(const std::string& pLibName, const std::string& pLibPath);
		
		//! Returns a pointer to the specific named library
		SGELIB* getLibrary(const std::string& pLibName);
		
		//! Bootstraps the Libraries against this Core
		void bootstrapLibs(SGECORE* pSGECore);
		
		//! Unloads all Libraries
		void unloadLibs();
		
		//! Unloads this Core
		void unloadCore(SGECORE* pSGECore);
		
	private:
		std::string corePath;
		std::vector<std::string> libPaths;
		
		libraryINST libCore;
		std::vector<libraryINST> libPointers;
		
		std::vector<std::string> libNames;
		std::vector<SGELIB*> libraries;
};

#endif
