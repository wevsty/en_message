#ifndef CRYPTOPP_DLL_INIT_HEADER_
#define CRYPTOPP_DLL_INIT_HEADER_

#ifdef _MSC_VER
#define CRYPTOPP_IMPORTS
#endif //_MSC_VER

#ifdef CRYPTOPP_IMPORTS
#include <cryptopp/dll.h>

//USING_NAMESPACE(CryptoPP)
//USING_NAMESPACE(std)
static CryptoPP::PNew s_pNew = NULL;
static CryptoPP::PDelete s_pDelete = NULL;

extern "C" __declspec(dllexport)
void __cdecl SetNewAndDeleteFromCryptoPP(
	CryptoPP::PNew pNew,
	CryptoPP::PDelete pDelete,
	CryptoPP::PSetNewHandler pSetNewHandler
);
void *__cdecl operator new (size_t size);
void __cdecl operator delete (void *p);

#endif


/*******************************************************************************/
/* Note: You may be using a weak algorithm that has been retained for backwards */
/* compatibility. Please '#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1' before */
/* including this .h file and prepend the class name with 'Weak::' to remove this */
/* warning." */
/******************************************************************************/
#if 0
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <arc4.h>
#include <md2.h>
#include <md4.h>
#include <md5.h>
#endif

#endif //CRYPTOPP_DLL_INIT_HEADER_