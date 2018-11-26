#include "cryptopp_dll_init.h"

#ifdef CRYPTOPP_IMPORTS_WINDOWS_DLL
#pragma  warning(disable:4251 4275 4101 4100)


#ifdef CRYPTOPP_IMPORTS
//static CryptoPP::PNew s_pNew = NULL;
//static CryptoPP::PDelete s_pDelete = NULL;

extern "C" __declspec(dllexport) void __cdecl SetNewAndDeleteFromCryptoPP(
	CryptoPP::PNew pNew, 
	CryptoPP::PDelete pDelete, 
	CryptoPP::PSetNewHandler pSetNewHandler
)
{
	(void)(pSetNewHandler);
	s_pNew = pNew;
	s_pDelete = pDelete;
}

void * __cdecl operator new (size_t size)
{
	return s_pNew(size);
}

void __cdecl operator delete (void * p)
{
	s_pDelete(p);
}

#endif //CRYPTOPP_IMPORTS

#endif //CRYPTOPP_IMPORTS_WINDOWS_DLL