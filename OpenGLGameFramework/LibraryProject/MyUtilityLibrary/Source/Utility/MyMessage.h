#ifndef _INCLUDE_GUARD_MYMESSAGE_H_
#define _INCLUDE_GUARD_MYMESSAGE_H_



//==================================================================================================================================
// マクロ定義
//==================================================================================================================================

// デバッグ用簡易メッセージボックスを有効にするマクロ定義
#define DEBUG_MESSAGE_ON

#define MESSAGE( messageText, windowTitle ) { MyMessage::Message( messageText, windowTitle ); }
//#define MESSAGE( messageText ) { MyMessage::Message( messageText, "" ); }



// デバッグ用簡易メッセージボックス
//
// デバッグモードのみ有効の簡易メッセージボックス。
// 引数はLPSTR等のマルチバイト文字とする。
// DEBUG_MESSAGE_ONがマクロ定義されている場合に動作する。
#define DEBUG_MESSAGE( messageText ) { MyMessage::DebugMessage( messageText ); }



// デバッグ用簡易コンソールログ
//
// デバッグモードのみ有効の簡易コンソールログ。
// 引数はLPSTR等のマルチバイト文字とする。
// DEBUG_MESSAGE_ONがマクロ定義されている場合に動作する。
#define DEBUG_CONSOLE_LOG( ... ) { MyMessage::DebugConsoleLog( __FILE__, __LINE__, __VA_ARGS__ ); }



//==================================================================================================================================
// インクルード
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
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 簡易メッセージボックス表示
//
// @param [in] / LPCWSTR messageText : メッセージ内容
// @param [in] / LPCWSTR windowTitle : メッセージボックスウィンドウのタイトル
//
// @note : 
//
// MessageBoxマクロを使用し、ウィンドウハンドル無し、OKボタンのみの
// 簡易的なウィンドウを作成してメッセージを表示する。
//----------------------------------------------------------------------------------------------------------------------------------
inline void Message( LPCWSTR messageText, LPCWSTR windowTitle ) 
{
	MessageBox( NULL, messageText, windowTitle, MB_OK );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 簡易メッセージボックス表示
//
// @param [in] / LPCSTR messageText : メッセージ内容
// @param [in] / LPCSTR windowTitle : メッセージボックスウィンドウのタイトル
//
// @note : 
//
// MessageBoxマクロを使用し、ウィンドウハンドル無し、OKボタンのみの
// 簡易的なウィンドウを作成してメッセージを表示する。
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
// @purpose : デバッグ用簡易メッセージボックス表示
//
// @param [in] / LPCSTR messageText : メッセージ内容
//
// @note : 
//
// デバッグ用の簡易的なウィンドウを作成してメッセージを表示する。
// DEBUG_MESSAGE_ONがマクロ定義されている時に動作する。
// デバッグ時にメッセージ表示を省略したい場合は、
// DEBUG_MESSAGE_ONのマクロ定義行をコメントアウトする。
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
// @purpose : デバッグ用簡易コンソールログ表示
//
// @param [in] / LPCSTR filename			: ファイル名
// @param [in] / UINT line					: 行数
// @param [in] / LPCSTR messageTextFormat	: メッセージ( 可変長引数 )
//
// @note : 
//
// デバッグ用の簡易的なメッセージをコンソールで表示する。
// DEBUG_MESSAGE_ONがマクロ定義されている時に動作する。
// デバッグ時にメッセージ表示を省略したい場合は、
// DEBUG_MESSAGE_ONのマクロ定義行をコメントアウトする。
//----------------------------------------------------------------------------------------------------------------------------------
inline void DebugConsoleLog( LPCSTR filename, UINT line, LPCSTR messageTextFormat, ... ) 
{
#ifndef NDEBUG

#ifdef DEBUG_MESSAGE_ON
	
	// ポインタチェック
	if ( NULL_CHECK( filename ) ) 
	{ 
printf( "ファイル名が不明です。\n" );
		return; 
	}

	if ( NULL_CHECK( messageTextFormat ) ) 
	{ 
printf( "メッセージを取得出来ませんでした。\n" );
		return; 
	}



	// 文字列の最大文字数
	const unsigned int uiMaxStrSize		= 256;
	
	// 文字列の1行の最大の長さ
	const unsigned int uiMaxStrWidth	= 70;

	// 文字列用バッファ
	CHAR strBuf[ uiMaxStrSize ]			= { };

	// 表示するメッセージ
	std::string strMessage;
	
	// ファイル名構造体
	FILE_NAME_STRUCTURE fileNameStructure( filename );

	// 可変長引数リスト
	va_list list;



	// 表示するメッセージの長さが文字列の最大文字数以上なら調整する
	strMessage = messageTextFormat;
	if ( uiMaxStrSize <= strMessage.size() ) 
	{
		strMessage.erase( uiMaxStrSize - 1 );
	}



	// 可変長引数リストを初期化
	va_start( list, messageTextFormat );
	
	// 可変長引数リストのデータをバッファに書き込む
	vsprintf_s( strBuf, strMessage.c_str(), list );
	
	// 可変長引数リストを復帰
	va_end( list );

/*
	// 可変長引数リストを初期化
	va_start( list, messageTextFormat );
	
	// 可変長引数リストのデータをバッファに書き込む
	vsprintf_s( strBuf, sizeof( strBuf ), messageTextFormat, list );
	
	// 可変長引数リストを復帰
	va_end( list );
*/
	// 表示するメッセージを設定
	strMessage = strBuf;





/*

	// 表示するメッセージの行の長さを調整
	//
	// 表示するメッセージの各行の文字数が文字列の1行の最大の長さに収まるように、
	// 文字列中に改行を挿入する。
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



	
	// 行数を文字列に変換
	_itoa_s( line, strBuf, 10 );



	// メッセージを出力

	for ( unsigned int i = 0; i < uiMaxStrWidth; i++ ) { std::cout << "-"; }

	// ファイル名と行数を出力
	std::cout << 
		std::endl <<
		"file : " + fileNameStructure.GetFileName() + fileNameStructure.GetExtensions() <<
		std::endl <<
		"line : " << 
		strBuf <<
		std::endl <<
		std::endl;

	// 表示するメッセージを出力
	std::cout << strMessage << std::endl;

	for ( unsigned int i = 0; i < uiMaxStrWidth; i++ ) { std::cout << "-"; }

	std::cout << std::endl;

#endif	// #ifndef NDEBUG

#endif	// #ifdef DEBUG_MESSAGE_ON
}



}	// namespace MyMessage



#endif	// #ifndef _INCLUDE_GUARD_MYMESSAGE_H_