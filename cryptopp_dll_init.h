#ifndef _CRYPTOPP_DLL_INIT_HEADER_
#define _CRYPTOPP_DLL_INIT_HEADER_

#ifdef _MSC_VER
#pragma  warning(disable:4251 4275 4101)
//cryptlib.lib
//#pragma comment(lib, "cryptlib")
#define CRYPTOPP_IMPORTS_WINDOWS_DLL
#endif //_MSC_VER

#ifdef CRYPTOPP_IMPORTS_WINDOWS_DLL
#include <cryptopp/dll.h>

/************************************************************************/
/* Because it's possible for the Crypto++ DLL to delete objects allocated     */
/* by the calling application, they must use the same C++ memory heap.      */
/* The following code block to achieve this.                                                */
/************************************************************************/
#ifdef CRYPTOPP_IMPORTS
static CryptoPP::PNew s_pNew = NULL;
static CryptoPP::PDelete s_pDelete = NULL;

extern "C" __declspec(dllexport) void __cdecl SetNewAndDeleteFromCryptoPP(
	CryptoPP::PNew pNew,
	CryptoPP::PDelete pDelete,
	CryptoPP::PSetNewHandler pSetNewHandler
);
void *__cdecl operator new (size_t size);
void __cdecl operator delete (void *p);
#endif //CRYPTOPP_IMPORTS

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

#endif //CRYPTOPP_IMPORTS_WINDOWS_DLL

#endif //_CRYPTOPP_DLL_INIT_HEADER_

