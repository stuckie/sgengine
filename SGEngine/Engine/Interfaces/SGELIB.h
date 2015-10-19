#ifndef _SGELIB_H_
#define _SGELIB_H_

class SGECORE;
class SGELIB
{
	public:
		SGELIB() {};
		virtual ~SGELIB() {};
		
		virtual int version() const = 0;
		virtual const char* libName() const = 0;
		
		virtual void bootstrap(SGECORE* SGECore) = 0;
};

// These are overloaded by the library...
typedef SGELIB* createSGELIB();
typedef void destroySGELIB(SGELIB*);

#endif
