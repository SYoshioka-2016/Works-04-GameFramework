//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLTGATEXTURE_H_
#include "OGLTgaTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLTGATEXTURE_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



//==================================================================================================================================
// usingディレクティブ
//==================================================================================================================================

// リソース名前空間
using namespace NS_Resource;

// テクスチャ名前空間
using namespace NS_Texture;



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLTgaTexture::OGLTgaTexture()
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLTgaTexture::~OGLTgaTexture() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャの読み込み
//
// @param [in] / char* pcFileName : Targa画像ファイル名
//
// @return / HRESULT : テクスチャの読み込みに成功したか
//	
// @note : 
//
// 画像ファイルからデータの読み込み処理を行う。
// ファイル名はTargaファイル名を指定する。
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT OGLTgaTexture::Load( const char* pcFileName ) 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( pcFileName );



	// 既に読み込まれていれば処理しない
	if ( m_bLoadFlg ) 
	{ 
		DEBUG_CONSOLE_LOG( "\"%s\"は既に読み込まれています。", pcFileName ); 

		return E_FAIL;
	}



	// ファイルを開く
	FILE* pFile = nullptr;
	if ( fopen_s( &pFile, pcFileName, "rb" ) != 0 ) 
	{
		DEBUG_CONSOLE_LOG( "\"%s\"のファイルオープンに失敗しました。", pcFileName );

		return E_FAIL;
	}



	// Targaのファイルヘッダを読み込む
	unsigned char ucHeader[ 18 ] = { };
	fread( ucHeader, sizeof( ucHeader ), 1, pFile );



	// テクスチャのサイズを設定
	m_lWidth  = ( ucHeader[ 13 ] * 256 ) + ucHeader[ 12 ];
	m_lHeight = ( ucHeader[ 15 ] * 256 ) + ucHeader[ 14 ];
	
	// ビット深度
	unsigned int uiBitCount = ucHeader[ 16 ];

	// 1ピクセルあたりのバイト数
	unsigned int uiBytePerPixel = uiBitCount / 8;

	// フォーマットを設定
	switch ( uiBitCount )
	{
		// 24bit
		case 24: m_uiTextureFormat = GL_RGB; break;

		// 32bit
		case 32: m_uiTextureFormat = GL_RGBA; break;



	default:
		
		DEBUG_CONSOLE_LOG( "\"%s\"のビット深度は対応していません。", pcFileName );

		// ファイルを閉じる
		fclose( pFile );

		break;
	}

	// ピクセルデータのサイズ
	size_t uiPixelSize = m_lWidth * m_lHeight * uiBytePerPixel;



	// ピクセルデータのメモリを確保
	unsigned char* pucPixelData = new unsigned char [ uiPixelSize ];

	// ピクセルデータの読み込み
	fread( pucPixelData, uiPixelSize, 1, pFile );

	// ファイルを閉じる
	fclose( pFile );






	for ( unsigned int i = 0; i < uiPixelSize; i += uiBytePerPixel ) 
	{
		unsigned char ucTemp	= pucPixelData[ i ];
		pucPixelData[ i ]		= pucPixelData[ i + 2 ];
		pucPixelData[ i + 2 ]	= ucTemp;
	}

	for ( int i = 0; i < m_lHeight / 2; i++ )
	{
		for ( int j = 0; j < m_lWidth * (int)uiBytePerPixel; j++ )
		{
			// インデックス算出
			int iIdx1 = j + ( (int)uiBytePerPixel * m_lWidth * i );
			int iIdx2 = j + ( (int)uiBytePerPixel * m_lWidth * ( m_lHeight - 1 - i ) );
	
			// 点対称の位置にあるピクセルをスワップ
			unsigned char ucTemp	= pucPixelData[ iIdx1 ];
			pucPixelData[ iIdx1 ]	= pucPixelData[ iIdx2 ];
			pucPixelData[ iIdx2 ]	= ucTemp;
		}
	}

/*
	// ビット深度別にピクセルデータを変換
	switch ( uiBitCount )
	{
		// 24bit
		case 24: ConvertPixelsTo24BitColor( pucPixelData ); break;



		default: 

			DEBUG_CONSOLE_LOG( "\"%s\"は対応しないビット数です。", pcFileName );

			SAFE_DELETE_ARRAY( pucPixelData );

			// ファイルを閉じる
			fclose( pFile );

			return E_FAIL;
	}
*/


	// テクスチャの生成
	GenerateTexture( pucPixelData );

	// ピクセルデータを削除
	SAFE_DELETE_ARRAY( pucPixelData );



	// ファイル名を保存
	m_pFileName	= new FILE_NAME_STRUCTURE( pcFileName );

	// 読み込みフラグを立てる
	m_bLoadFlg = true;



	return S_OK;
}