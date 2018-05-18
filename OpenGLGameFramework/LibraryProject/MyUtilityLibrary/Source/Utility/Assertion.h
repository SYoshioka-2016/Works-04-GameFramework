#ifndef _INCLUDE_GUARD_ASSERTION_H_
#define _INCLUDE_GUARD_ASSERTION_H_



//==================================================================================================================================
// インクルード
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
// マクロ定義
//==================================================================================================================================

// 強制アサート
//
// expは条件でtrueかfalseを問う。
//
// expがtrue(1)なら ( (!!(exp)) || (MyAssertion::Halt(), 0) )の
// (!!(exp))の部分でtrueとなり、(MyAssertion::Halt(), 0)を無視して通過するので
// プログラムは継続する。
//
// expがfalse(0)なら強制終了Halt()が実行され、プログラムを終えるようにする。
// Halt()はカンマ演算子で0を返すようにする。
//
// __FILE__はファイル名文字列を、__LINE__は行数の値を返すマクロである。
//
// #expの#は変数名を文字列にする。
#define STRONG_ASSERT( exp ) ( (!!(exp)) || ( MyAssertion::Halt(__FILE__, __LINE__, #exp), 0 ) )

// 強制終了
//
// プログラムを停止させたい場合に使用。
// デバッグ、リリース問わずプログラムをダウンさせる。
#define HALT( exp ) ( MyAssertion::Halt( __FILE__, __LINE__, #exp ), E_FAIL );

// エラーメッセージ
//
// エラーメッセージを表示する。
// 警告のみでプログラムを続行させる場合に使用する。
// 1フレームで複数回実行される場合は注意が必要。
#define ERROR_MESSAGE( exp ) ( MyAssertion::ErrorMessage( __FILE__, __LINE__, #exp ), E_FAIL );

// ポインタチェック
//
// ポインタの正当性の判定のみを行う。
#define POINTER_CHECK( p ) ( MyAssertion::PointerCheck( p ) )


#define NULL_CHECK( p ) ( MyAssertion::NullCheck( p ) )



// デバッグ時のマクロ
#ifndef NDEBUG

// アサート
//
// exp が true なら通過する。
// false ならプログラムを強制終了する。
#define ASSERT( exp ) ( (!!(exp)) || ( MyAssertion::Halt(__FILE__, __LINE__, #exp), 0 ) )

// アサート付きポインタチェック
//
// ポインタが正しければ通過する。
// 不正があればプログラムを強制終了する。
#define ASSERT_POINTER_CHECK( p ) { if ( !MyAssertion::PointerCheck( p ) ) ASSERT( 0 && L"不正なポインタです。" ); }

// アサート付きインデックスチェック
//
// 配列とそれに対応するインデックスを1つ指定し、
// インデックスが配列の範囲内であれば通過する。
#define ASSERT_INDEX_CHECK( Array, index )\
{\
	ASSERT_POINTER_CHECK( Array );\
\
	if ( ( 0 > index ) || ( ARRAYSIZE( Array ) <= index ) )\
	{\
		ASSERT( 0 && L"範囲外のインデックスです。" );\
	}\
}



// リリース時のマクロ
#else

// アサート(処理無し)
#define ASSERT( exp )

// アサート付きポインタチェック(処理無し)
#define ASSERT_POINTER_CHECK( p )

// アサート付きインデックスチェック(処理無し)
#define ASSERT_INDEX_CHECK( Array, index )

#endif	// #ifndef NDEBUG



namespace MyAssertion 
{



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 簡易エラーメッセージ表示
//
// @param [in] / LPCWSTR	filename		: 呼び出している(エラーが発生した)ファイル名
// @param [in] / UINT		line			: 呼び出している(エラーが発生した)ファイルの行番号
// @param [in] / LPCWSTR	messageText		: エラーのメッセージ内容
//
// @note : 
//
// Message() を使用してエラー用の簡易的なウィンドウを
// 作成してメッセージを表示する。
//----------------------------------------------------------------------------------------------------------------------------------
inline void ErrorMessage( LPCSTR filename, UINT line, LPCSTR messageText ) 
{
	// 文字列の長さ、エラー用
	size_t			len	= 0;
	errno_t			err	= 0;

	// 文字列バッファの長さ
	const size_t	sizeInWords	= 256;

	// 文字列編集、保存用バッファ
	WCHAR			wStr[ sizeInWords ] = { 0 };
	CHAR			str[ sizeInWords ]	= { 0 }, strBuf[ sizeInWords ] = { 0 };
	


	setlocale( LC_ALL, "japanese" );



	// ファイル名を保存
	err					= mbstowcs_s( &len, wStr, sizeInWords, filename, _TRUNCATE );
	err					= wcstombs_s( &len, str, sizeInWords, wStr, _TRUNCATE );

	strcat_s( str, "::line " );

	// 行番号を保存、連結
	_itoa_s( line, strBuf, 10 );
	strcat_s( str, strBuf );
	strcat_s( str, " >>> \n\n" );
	
	// メッセージを保存、連結
	err					= mbstowcs_s( &len, wStr, sizeInWords, messageText, _TRUNCATE );
	err					= wcstombs_s( &len, strBuf, sizeInWords, wStr, _TRUNCATE );
	strcat_s( str, strBuf );

	// 連結した文字列をワイド文字列に変換
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
// @purpose : プログラム停止
//
// @param [in] / LPCWSTR	filename		: 呼び出している(エラーが発生した)ファイル名
// @param [in] / UINT		line			: 呼び出している(エラーが発生した)ファイルの行番号
// @param [in] / LPCWSTR	messageText		: エラーのメッセージ内容
//
// @note : 
//
// エラー処理を想定。
// エラーメッセージを表示してプログラムを安全に終えるようにする。
// 引数の filename と line にはそれぞれ 
// __FILE__ 、__LINE__ マクロを使うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
inline void Halt( LPSTR filename, UINT line, LPSTR messageText ) 
{
	// エラーメッセージを表示
	ErrorMessage( filename, line, messageText );

	// プログラムを終了
	exit( 1 );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ポインタ正当性チェック
//
// @param [in] / T* t	: ポインタ
//
// @return / bool : ポインタが正当か
//
// @note : 
//
// ポインタの正当性を判定する。
// 正当ならtrueを返す。
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
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_MYMESSAGE_H_
#include "MyMessage.h"
#endif	// #ifndef _INCLUDE_GUARD_MYMESSAGE_H_



#endif	// #ifndef _INCLUDE_GUARD_ASSERTION_H_