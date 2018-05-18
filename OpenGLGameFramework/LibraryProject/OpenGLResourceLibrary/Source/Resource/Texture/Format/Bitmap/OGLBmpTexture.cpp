//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_
#include "OGLBmpTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



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
OGLBmpTexture::OGLBmpTexture()
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLBmpTexture::~OGLBmpTexture() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャの読み込み
//
// @param [in] / char* pcFileName : Bitmap画像ファイル名
//
// @return / HRESULT : テクスチャの読み込みに成功したか
//	
// @note : 
//
// 画像ファイルからデータの読み込み処理を行う。
// ファイル名はBitmapファイル名を指定する。
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT OGLBmpTexture::Load( const char* pcFileName ) 
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



	// ビットマップのファイルヘッダを読み込む
	BITMAPFILEHEADER bmpFileHeader;
	fread( &bmpFileHeader, sizeof( BITMAPFILEHEADER ), 1, pFile );

	if ( 0x4d42 != bmpFileHeader.bfType ) 
	{
		DEBUG_CONSOLE_LOG( "\"%s\"はBitmapファイルではありません。", pcFileName );

		// ファイルを閉じる
		fclose( pFile );

		return E_FAIL;
	}
	


	// ビットマップの情報ヘッダを読み込む
	BITMAPINFOHEADER bmpInfoHeader;
	fread( &bmpInfoHeader, sizeof( BITMAPINFOHEADER ), 1, pFile );
	
	if ( BI_RGB != bmpInfoHeader.biCompression ) 
	{ 
		DEBUG_CONSOLE_LOG( "\"%s\"は圧縮に対応していません。", pcFileName ); 

		// ファイルを閉じる
		fclose( pFile );

		return E_FAIL;
	}


	// 画像のサイズを取得
	m_lWidth	= bmpInfoHeader.biWidth;
	m_lHeight	= bmpInfoHeader.biHeight;



	// 1ピクセルあたりのビット数別にピクセルデータのサイズを設定する
	size_t uiPixelSize = 0;
	switch ( bmpInfoHeader.biBitCount )
	{
		// 24bit
		case 24: //Load24BitColorPixels( pFile ); break;
			uiPixelSize = m_lWidth * m_lHeight * 3;

			break;



		default: 
		
			DEBUG_CONSOLE_LOG( "\"%s\"は対応しないビット数です。", pcFileName );

			// ファイルを閉じる
			fclose( pFile );

			return E_FAIL;
	}



	// ピクセルデータのメモリを確保
	unsigned char* pucPixelData = new unsigned char [ uiPixelSize ];

	// ピクセルデータの読み込み
	fread( pucPixelData, uiPixelSize, 1, pFile );

	// ファイルを閉じる
	fclose( pFile );



	// ビット数別にピクセルデータを変換
	switch ( bmpInfoHeader.biBitCount )
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