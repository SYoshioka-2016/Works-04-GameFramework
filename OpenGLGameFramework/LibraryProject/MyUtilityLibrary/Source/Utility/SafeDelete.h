#ifndef _INCLUDE_GUARD_SAFEDELETE_H_
#define _INCLUDE_GUARD_SAFEDELETE_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_ASSERTION_H_
#include "Assertion.h"
#endif	// #ifndef _INCLUDE_GUARD_ASSERTION_H_



//==================================================================================================================================
// マクロ定義
//==================================================================================================================================

// メモリ削除
#define SAFE_DELETE( x ) \
{\
	try\
	{\
		if ( POINTER_CHECK( x ) )\
		{\
			delete x;\
			x = nullptr;\
		}\
	}\
	catch ( ... )\
	{\
		HALT( "deleteに失敗しました。" );\
	}\
}

// 配列メモリ削除
#define SAFE_DELETE_ARRAY( x ) \
{\
	try\
	{\
		if ( POINTER_CHECK( x ) )\
		{\
			delete [] x;\
			x = NULL;\
		}\
	}\
	catch ( ... )\
	{\
		HALT( "deleteに失敗しました。" );\
	}\
}



#endif	// #ifndef _INCLUDE_GUARD_SAFEDELETE_H_