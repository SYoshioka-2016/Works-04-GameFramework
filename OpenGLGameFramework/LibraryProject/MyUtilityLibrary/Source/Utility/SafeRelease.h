#ifndef _INCLUDE_GUARD_SAFERELEASE_H_
#define _INCLUDE_GUARD_SAFERELEASE_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_ASSERTION_H_
#include "Assertion.h"
#endif	// #ifndef _INCLUDE_GUARD_ASSERTION_H_



//==================================================================================================================================
// �}�N����`
//==================================================================================================================================

// �����[�X
//#define SAFE_RELEASE( x ) { if ( !MySafeRelease::SafeRelease( x ) ) { HALT( "Release �Ɏ��s���܂����B" ); } }
#define SAFE_RELEASE( x ) \
{\
	try\
	{\
		if ( POINTER_CHECK( x ) )\
		{\
			x->Release();\
			x = nullptr;\
		}\
	}\
	catch ( ... )\
	{\
		HALT( "Release�Ɏ��s���܂����B" );\
	}\
}


/*
namespace MySafeRelease {

template<class Interface>
inline bool SafeRelease( Interface** ppInterface ) 
{
	try {
//		if ( *ppInterface ) {
		if ( POINTER_CHECK( pInterface ) ) {
	
			(*ppInterface)->Release();
			(*ppInterface) = NULL;

			return true;
		}
	}
	catch ( ... ) {
	
		return false;
	}



	return true;
}



template<class Interface>
inline bool SafeRelease( Interface* pInterface ) 
{
	try {
//		if ( pInterface ) {
		if ( POINTER_CHECK( pInterface ) ) {
	
			pInterface->Release();
			pInterface = NULL;

			return true;
		}
	}
	catch ( ... ) {
	
		return false;
	}



	return true;
}



}	// namespace MySafeRelease
*/


#endif	// #ifndef _INCLUDE_GUARD_SAFERELEASE_H_