#ifndef _INCLUDE_GUARD_ASSERTION_H_
#define _INCLUDE_GUARD_ASSERTION_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_LOCALE_H_
#define _INCLUDE_GUARD_LOCALE_H_
#include <locale.h>
#endif	// #ifndef _INCLUDE_GUARD_LOCALE_H_

#ifndef _INCLUDE_GUARD_STDLIB_H_
#define _INCLUDE_GUARD_STDLIB_H_
#include <stdlib.h>
#endif	// #ifndef _INCLUDE_GUARD_STDLIB_H_

#ifndef _INCLUDE_GUARD_WINDOWS_H_
#define _INCLUDE_GUARD_WINDOWS_H_
#include <Windows.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWS_H_



//==================================================================================================================================
// �}�N����`
//==================================================================================================================================

// �����A�T�[�g
//
// exp�͏�����true��false��₤�B
//
// exp��true(1)�Ȃ� ( (!!(exp)) || (MyAssertion::Halt(), 0) )��
// (!!(exp))�̕�����true�ƂȂ�A(MyAssertion::Halt(), 0)�𖳎����Ēʉ߂���̂�
// �v���O�����͌p������B
//
// exp��false(0)�Ȃ狭���I��Halt()�����s����A�v���O�������I����悤�ɂ���B
// Halt()�̓J���}���Z�q��0��Ԃ��悤�ɂ���B
//
// __FILE__�̓t�@�C������������A__LINE__�͍s���̒l��Ԃ��}�N���ł���B
//
// #exp��#�͕ϐ����𕶎���ɂ���B
#define STRONG_ASSERT( exp ) ( (!!(exp)) || ( MyAssertion::Halt(__FILE__, __LINE__, #exp), 0 ) )

// �����I��
//
// �v���O�������~���������ꍇ�Ɏg�p�B
// �f�o�b�O�A�����[�X��킸�v���O�������_�E��������B
#define HALT( exp ) ( MyAssertion::Halt( __FILE__, __LINE__, #exp ), E_FAIL );

// �G���[���b�Z�[�W
//
// �G���[���b�Z�[�W��\������B
// �x���݂̂Ńv���O�����𑱍s������ꍇ�Ɏg�p����B
// 1�t���[���ŕ�������s�����ꍇ�͒��ӂ��K�v�B
#define ERROR_MESSAGE( exp ) ( MyAssertion::ErrorMessage( __FILE__, __LINE__, #exp ), E_FAIL );

// �|�C���^�`�F�b�N
//
// �|�C���^�̐������̔���݂̂��s���B
#define POINTER_CHECK( p ) ( MyAssertion::PointerCheck( p ) )


#define NULL_CHECK( p ) ( MyAssertion::NullCheck( p ) )



// �f�o�b�O���̃}�N��
#ifndef NDEBUG

// �A�T�[�g
//
// exp �� true �Ȃ�ʉ߂���B
// false �Ȃ�v���O�����������I������B
#define ASSERT( exp ) ( (!!(exp)) || ( MyAssertion::Halt(__FILE__, __LINE__, #exp), 0 ) )

// �A�T�[�g�t���|�C���^�`�F�b�N
//
// �|�C���^����������Βʉ߂���B
// �s��������΃v���O�����������I������B
#define ASSERT_POINTER_CHECK( p ) { if ( !MyAssertion::PointerCheck( p ) ) ASSERT( 0 && L"�s���ȃ|�C���^�ł��B" ); }

// �A�T�[�g�t���C���f�b�N�X�`�F�b�N
//
// �z��Ƃ���ɑΉ�����C���f�b�N�X��1�w�肵�A
// �C���f�b�N�X���z��͈͓̔��ł���Βʉ߂���B
#define ASSERT_INDEX_CHECK( Array, index )\
{\
	ASSERT_POINTER_CHECK( Array );\
\
	if ( ( 0 > index ) || ( ARRAYSIZE( Array ) <= index ) )\
	{\
		ASSERT( 0 && L"�͈͊O�̃C���f�b�N�X�ł��B" );\
	}\
}



// �����[�X���̃}�N��
#else

// �A�T�[�g(��������)
#define ASSERT( exp )

// �A�T�[�g�t���|�C���^�`�F�b�N(��������)
#define ASSERT_POINTER_CHECK( p )

// �A�T�[�g�t���C���f�b�N�X�`�F�b�N(��������)
#define ASSERT_INDEX_CHECK( Array, index )

#endif	// #ifndef NDEBUG



namespace MyAssertion 
{



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �ȈՃG���[���b�Z�[�W�\��
//
// @param [in] / LPCWSTR	filename		: �Ăяo���Ă���(�G���[����������)�t�@�C����
// @param [in] / UINT		line			: �Ăяo���Ă���(�G���[����������)�t�@�C���̍s�ԍ�
// @param [in] / LPCWSTR	messageText		: �G���[�̃��b�Z�[�W���e
//
// @note : 
//
// Message() ���g�p���ăG���[�p�̊ȈՓI�ȃE�B���h�E��
// �쐬���ă��b�Z�[�W��\������B
//----------------------------------------------------------------------------------------------------------------------------------
inline void ErrorMessage( LPCSTR filename, UINT line, LPCSTR messageText ) 
{
	// ������̒����A�G���[�p
	size_t			len	= 0;
	errno_t			err	= 0;

	// ������o�b�t�@�̒���
	const size_t	sizeInWords	= 256;

	// ������ҏW�A�ۑ��p�o�b�t�@
	WCHAR			wStr[ sizeInWords ] = { 0 };
	CHAR			str[ sizeInWords ]	= { 0 }, strBuf[ sizeInWords ] = { 0 };
	


	setlocale( LC_ALL, "japanese" );



	// �t�@�C������ۑ�
	err					= mbstowcs_s( &len, wStr, sizeInWords, filename, _TRUNCATE );
	err					= wcstombs_s( &len, str, sizeInWords, wStr, _TRUNCATE );

	strcat_s( str, "::line " );

	// �s�ԍ���ۑ��A�A��
	_itoa_s( line, strBuf, 10 );
	strcat_s( str, strBuf );
	strcat_s( str, " >>> \n\n" );
	
	// ���b�Z�[�W��ۑ��A�A��
	err					= mbstowcs_s( &len, wStr, sizeInWords, messageText, _TRUNCATE );
	err					= wcstombs_s( &len, strBuf, sizeInWords, wStr, _TRUNCATE );
	strcat_s( str, strBuf );

	// �A����������������C�h������ɕϊ�
	err					= mbstowcs_s( &len, wStr, sizeInWords, str, _TRUNCATE );



//	MESSAGE( wStr, L"error" );
//	MyMessage::Message( wStr, L"error" );
	MessageBox( NULL, wStr, L"error", MB_OK | MB_ICONSTOP );
}



inline void ErrorMessage( LPCSTR filename, UINT line, LPCWSTR messageText ) 
{
	CHAR str[ 256 ];
	size_t len = 0;
	errno_t err = 0;

	setlocale( LC_ALL, "japanese" );

	err = wcstombs_s( &len, str, 256, messageText, _TRUNCATE );



	MyAssertion::ErrorMessage( filename, line, str );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �v���O������~
//
// @param [in] / LPCWSTR	filename		: �Ăяo���Ă���(�G���[����������)�t�@�C����
// @param [in] / UINT		line			: �Ăяo���Ă���(�G���[����������)�t�@�C���̍s�ԍ�
// @param [in] / LPCWSTR	messageText		: �G���[�̃��b�Z�[�W���e
//
// @note : 
//
// �G���[������z��B
// �G���[���b�Z�[�W��\�����ăv���O���������S�ɏI����悤�ɂ���B
// ������ filename �� line �ɂ͂��ꂼ�� 
// __FILE__ �A__LINE__ �}�N�����g���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
inline void Halt( LPSTR filename, UINT line, LPSTR messageText ) 
{
	// �G���[���b�Z�[�W��\��
	ErrorMessage( filename, line, messageText );

	// �v���O�������I��
	exit( 1 );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �|�C���^�������`�F�b�N
//
// @param [in] / T* t	: �|�C���^
//
// @return / bool : �|�C���^��������
//
// @note : 
//
// �|�C���^�̐������𔻒肷��B
// �����Ȃ�true��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
template<class T>
inline bool PointerCheck( T* t ) 
{
	return ( nullptr != t );
} 



template<class T>
inline bool NullCheck( T* t ) 
{
	return ( nullptr == t );
} 



}	// namespace MyAssertion



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_MYMESSAGE_H_
#include "MyMessage.h"
#endif	// #ifndef _INCLUDE_GUARD_MYMESSAGE_H_



#endif	// #ifndef _INCLUDE_GUARD_ASSERTION_H_