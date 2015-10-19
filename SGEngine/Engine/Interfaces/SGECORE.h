#ifndef _SGECORE_H_
#define _SGECORE_H_

class Linker;
class SGECORE
{
	public:
		SGECORE() {};
		virtual ~SGECORE() {};
		
		virtual int version() const = 0;
		virtual const char* libName() const = 0;
		
		virtual void bootstrap(Linker* pLinker) = 0;
		virtual void run(const char* script) = 0;
};

// These are overloaded by the library...
typedef SGECORE* createSGECORE();
typedef void destroySGECORE(SGECORE*);

#endif 
