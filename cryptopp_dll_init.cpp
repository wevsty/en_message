#ifdef _MSC_VER
typedef unsigned char byte;
#pragma  warning(push)
#pragma  warning(disable:4251 4275 4101)
#include "cryptopp_dll_init.h"
#endif

#pragma  warning(disable:4100)
//static CryptoPP::PNew s_pNew = NULL;
//static CryptoPP::PDelete s_pDelete = NULL;

extern "C" __declspec(dllexport)
void __cdecl SetNewAndDeleteFromCryptoPP(
	CryptoPP::PNew pNew,
	CryptoPP::PDelete pDelete,
	CryptoPP::PSetNewHandler pSetNewHandler)
{
	s_pNew = pNew;
	s_pDelete = pDelete;
}

void *__cdecl operator new (size_t size)
{
	return s_pNew(size);
}

void __cdecl operator delete (void *p)
{
	s_pDelete(p);
}


#ifdef _MSC_VER
#pragma  warning(  pop  )
#endif