#ifndef _INCLUDE_GUARD_MYMESSAGE_H_
#define _INCLUDE_GUARD_MYMESSAGE_H_



//==================================================================================================================================
// �}�N����`
//==================================================================================================================================

// �f�o�b�O�p�ȈՃ��b�Z�[�W�{�b�N�X��L���ɂ���}�N����`
#define DEBUG_MESSAGE_ON

#define MESSAGE( messageText, windowTitle ) { MyMessage::Message( messageText, windowTitle ); }
//#define MESSAGE( messageText ) { MyMessage::Message( messageText, "" ); }



// �f�o�b�O�p�ȈՃ��b�Z�[�W�{�b�N�X
//
// �f�o�b�O���[�h�̂ݗL���̊ȈՃ��b�Z�[�W�{�b�N�X�B
// ������LPSTR���̃}���`�o�C�g�����Ƃ���B
// DEBUG_MESSAGE_ON���}�N����`����Ă���ꍇ�ɓ��삷��B
#define DEBUG_MESSAGE( messageText ) { MyMessage::DebugMessage( messageText ); }



// �f�o�b�O�p�ȈՃR���\�[�����O
//
// �f�o�b�O���[�h�̂ݗL���̊ȈՃR���\�[�����O�B
// ������LPSTR���̃}���`�o�C�g�����Ƃ���B
// DEBUG_MESSAGE_ON���}�N����`����Ă���ꍇ�ɓ��삷��B
#define DEBUG_CONSOLE_LOG( ... ) { MyMessage::DebugConsoleLog( __FILE__, __LINE__, __VA_ARGS__ ); }



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_FILENAMESTRUCTURE_H_
#include "TypeDefines/FileNameStructure.h"
#endif	// #ifndef _INCLUDE_GUARD_FILENAMESTRUCTURE_H_

#ifndef _INCLUDE_GUARD_ASSERTION_H_
#include "Assertion.h"
#endif	// #ifndef _INCLUDE_GUARD_ASSERTION_H_

#ifndef _INCLUDE_GUARD_STDIO_H_
#define _INCLUDE_GUARD_STDIO_H_
#include <stdio.h>
#endif	// #ifndef _INCLUDE_GUARD_STDIO_H_

#ifndef _INCLUDE_GUARD_IOSTREAM_
#define _INCLUDE_GUARD_IOSTREAM_
#include <iostream>
#endif	// #ifndef _INCLUDE_GUARD_IOSTREAM_

#ifndef _INCLUDE_GUARD_LOCALE_H_
#define _INCLUDE_GUARD_LOCALE_H_
#include <locale.h>
#endif	// #ifndef _INCLUDE_GUARD_LOCALE_H_

#ifndef _INCLUDE_GUARD_WINDOWS_H_
#define _INCLUDE_GUARD_WINDOWS_H_
#include <Windows.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWS_H_



namespace MyMessage 
{



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �ȈՃ��b�Z�[�W�{�b�N�X�\��
//
// @param [in] / LPCWSTR messageText : ���b�Z�[�W���e
// @param [in] / LPCWSTR windowTitle : ���b�Z�[�W�{�b�N�X�E�B���h�E�̃^�C�g��
//
// @note : 
//
// MessageBox�}�N�����g�p���A�E�B���h�E�n���h�������AOK�{�^���݂̂�
// �ȈՓI�ȃE�B���h�E���쐬���ă��b�Z�[�W��\������B
//----------------------------------------------------------------------------------------------------------------------------------
inline void Message( LPCWSTR messageText, LPCWSTR windowTitle ) 
{
	MessageBox( NULL, messageText, windowTitle, MB_OK );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �ȈՃ��b�Z�[�W�{�b�N�X�\��
//
// @param [in] / LPCSTR messageText : ���b�Z�[�W���e
// @param [in] / LPCSTR windowTitle : ���b�Z�[�W�{�b�N�X�E�B���h�E�̃^�C�g��
//
// @note : 
//
// MessageBox�}�N�����g�p���A�E�B���h�E�n���h�������AOK�{�^���݂̂�
// �ȈՓI�ȃE�B���h�E���쐬���ă��b�Z�[�W��\������B
//----------------------------------------------------------------------------------------------------------------------------------
inline void Message( LPCSTR messageText, LPCSTR windowTitle ) 
{
	WCHAR wStr1[ 256 ], wStr2[ 256 ];
	size_t len = 0;
	errno_t err = 0;

	setlocale( LC_ALL, "japanese" );

	err = mbstowcs_s( &len, wStr1, 256, messageText, _TRUNCATE );
	err = mbstowcs_s( &len, wStr2, 256, windowTitle, _TRUNCATE );
	MyMessage::Message( wStr1, wStr2 );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�o�b�O�p�ȈՃ��b�Z�[�W�{�b�N�X�\��
//
// @param [in] / LPCSTR messageText : ���b�Z�[�W���e
//
// @note : 
//
// �f�o�b�O�p�̊ȈՓI�ȃE�B���h�E���쐬���ă��b�Z�[�W��\������B
// DEBUG_MESSAGE_ON���}�N����`����Ă��鎞�ɓ��삷��B
// �f�o�b�O���Ƀ��b�Z�[�W�\�����ȗ��������ꍇ�́A
// DEBUG_MESSAGE_ON�̃}�N����`�s���R�����g�A�E�g����B
//----------------------------------------------------------------------------------------------------------------------------------
inline void DebugMessage( LPCSTR messageText ) 
{
#ifndef NDEBUG

#ifdef DEBUG_MESSAGE_ON

	WCHAR wStr[ 256 ];
	size_t len = 0;
	errno_t err = 0;

	setlocale( LC_ALL, "japanese" );

	err = mbstowcs_s( &len, wStr, 256, messageText, _TRUNCATE );
	MyMessage::Message( wStr, L"Debug Message" );

#endif	// #ifndef NDEBUG

#endif	// #ifdef DEBUG_MESSAGE_ON
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�o�b�O�p�ȈՃR���\�[�����O�\��
//
// @param [in] / LPCSTR filename			: �t�@�C����
// @param [in] / UINT line					: �s��
// @param [in] / LPCSTR messageTextFormat	: ���b�Z�[�W( �ϒ����� )
//
// @note : 
//
// �f�o�b�O�p�̊ȈՓI�ȃ��b�Z�[�W���R���\�[���ŕ\������B
// DEBUG_MESSAGE_ON���}�N����`����Ă��鎞�ɓ��삷��B
// �f�o�b�O���Ƀ��b�Z�[�W�\�����ȗ��������ꍇ�́A
// DEBUG_MESSAGE_ON�̃}�N����`�s���R�����g�A�E�g����B
//----------------------------------------------------------------------------------------------------------------------------------
inline void DebugConsoleLog( LPCSTR filename, UINT line, LPCSTR messageTextFormat, ... ) 
{
#ifndef NDEBUG

#ifdef DEBUG_MESSAGE_ON
	
	// �|�C���^�`�F�b�N
	if ( NULL_CHECK( filename ) ) 
	{ 
printf( "�t�@�C�������s���ł��B\n" );
		return; 
	}

	if ( NULL_CHECK( messageTextFormat ) ) 
	{ 
printf( "���b�Z�[�W���擾�o���܂���ł����B\n" );
		return; 
	}



	// ������̍ő啶����
	const unsigned int uiMaxStrSize		= 256;
	
	// �������1�s�̍ő�̒���
	const unsigned int uiMaxStrWidth	= 70;

	// ������p�o�b�t�@
	CHAR strBuf[ uiMaxStrSize ]			= { };

	// �\�����郁�b�Z�[�W
	std::string strMessage;
	
	// �t�@�C�����\����
	FILE_NAME_STRUCTURE fileNameStructure( filename );

	// �ϒ��������X�g
	va_list list;



	// �\�����郁�b�Z�[�W�̒�����������̍ő啶�����ȏ�Ȃ璲������
	strMessage = messageTextFormat;
	if ( uiMaxStrSize <= strMessage.size() ) 
	{
		strMessage.erase( uiMaxStrSize - 1 );
	}



	// �ϒ��������X�g��������
	va_start( list, messageTextFormat );
	
	// �ϒ��������X�g�̃f�[�^���o�b�t�@�ɏ�������
	vsprintf_s( strBuf, strMessage.c_str(), list );
	
	// �ϒ��������X�g�𕜋A
	va_end( list );

/*
	// �ϒ��������X�g��������
	va_start( list, messageTextFormat );
	
	// �ϒ��������X�g�̃f�[�^���o�b�t�@�ɏ�������
	vsprintf_s( strBuf, sizeof( strBuf ), messageTextFormat, list );
	
	// �ϒ��������X�g�𕜋A
	va_end( list );
*/
	// �\�����郁�b�Z�[�W��ݒ�
	strMessage = strBuf;





/*

	// �\�����郁�b�Z�[�W�̍s�̒����𒲐�
	//
	// �\�����郁�b�Z�[�W�̊e�s�̕��������������1�s�̍ő�̒����Ɏ��܂�悤�ɁA
	// �����񒆂ɉ��s��}������B
	for ( 
		unsigned int i = 1; 
		i <= ( strMessage.size() / uiMaxStrWidth ) && ( strMessage.size() - i * uiMaxStrWidth ) > 0; 
		i++ 
	) 
	{
		strMessage.insert( i * uiMaxStrWidth + i - 1, "\n" );
	}
*/

	unsigned int uiAsciiCount = 0, uiNotAsciiCount = 0;
	for ( unsigned int i = 0; i < strMessage.size(); i++ ) 
	{
		bool bIsAscii = isascii( strMessage[i] );


		


//		if ( ( ( i % ( uiMaxStrWidth + ( i / ( uiMaxStrWidth -1) ) - 1 ) ) == 0 ) ) 
		if ( ( ( i % uiMaxStrWidth ) == uiMaxStrWidth - 1 ) ) 
		{
			if ( bIsAscii ) 
			{
				strMessage.insert( i + 1, "\n" );
				i++;
			}




			else 
			{

				if ( ( uiAsciiCount % 2 ) ) 
				{
					strMessage.insert( i, "\n" );
					strMessage.insert( i + 1, "\r" );
				}
				else 
				{
					strMessage.insert( i + 1, "\n" );
					strMessage.insert( i + 2, "\r" );
				}

//				strMessage.insert( i + 1, "\n" );
			}
			

			uiAsciiCount = 0;
			uiNotAsciiCount = 0;
		}



		if ( bIsAscii ) 
		{
			uiAsciiCount++;
		}
		else 
		{
			uiNotAsciiCount++;
		}
	}



	
	// �s���𕶎���ɕϊ�
	_itoa_s( line, strBuf, 10 );



	// ���b�Z�[�W���o��

	for ( unsigned int i = 0; i < uiMaxStrWidth; i++ ) { std::cout << "-"; }

	// �t�@�C�����ƍs�����o��
	std::cout << 
		std::endl <<
		"file : " + fileNameStructure.GetFileName() + fileNameStructure.GetExtensions() <<
		std::endl <<
		"line : " << 
		strBuf <<
		std::endl <<
		std::endl;

	// �\�����郁�b�Z�[�W���o��
	std::cout << strMessage << std::endl;

	for ( unsigned int i = 0; i < uiMaxStrWidth; i++ ) { std::cout << "-"; }

	std::cout << std::endl;

#endif	// #ifndef NDEBUG

#endif	// #ifdef DEBUG_MESSAGE_ON
}



}	// namespace MyMessage



#endif	// #ifndef _INCLUDE_GUARD_MYMESSAGE_H_