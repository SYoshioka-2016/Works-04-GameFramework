#ifndef _INCLUDE_GUARD_SAFEDELETE_H_
#define _INCLUDE_GUARD_SAFEDELETE_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_ASSERTION_H_
#include "Assertion.h"
#endif	// #ifndef _INCLUDE_GUARD_ASSERTION_H_



//==================================================================================================================================
// �}�N����`
//==================================================================================================================================

// �������폜
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
		HALT( "delete�Ɏ��s���܂����B" );\
	}\
}

// �z�񃁃����폜
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
		HALT( "delete�Ɏ��s���܂����B" );\
	}\
}



#endif	// #ifndef _INCLUDE_GUARD_SAFEDELETE_H_