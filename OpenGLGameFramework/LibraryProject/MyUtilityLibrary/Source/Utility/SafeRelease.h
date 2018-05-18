#ifndef _INCLUDE_GUARD_SAFERELEASE_H_
#define _INCLUDE_GUARD_SAFERELEASE_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_ASSERTION_H_
#include "Assertion.h"
#endif	// #ifndef _INCLUDE_GUARD_ASSERTION_H_



//==================================================================================================================================
// マクロ定義
//==================================================================================================================================

// リリース
//#define SAFE_RELEASE( x ) { if ( !MySafeRelease::SafeRelease( x ) ) { HALT( "Release に失敗しました。" ); } }
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
		HALT( "Releaseに失敗しました。" );\
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