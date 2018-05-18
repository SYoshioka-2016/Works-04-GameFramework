//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLTEXTURE_H_
#include "OGLTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLTEXTURE_H_

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
OGLTexture::OGLTexture() :
	m_bLoadFlg( false ),
	m_pFileName( nullptr ),
	m_uiTextureFormat( 0 ),
	m_uiTexture( 0 ),
	m_lWidth( 0 ),
	m_lHeight( 0 )
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLTexture::~OGLTexture() 
{
	// テクスチャを削除
	glDeleteTextures( 1, &m_uiTexture );

	SAFE_DELETE( m_pFileName );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ファイル名の取得
//
// @return / const char* : ディレクトリと拡張子を含まないファイル名
//	
// @note : 
//
// ディレクトリと拡張子を含まないファイル名を取得する。
//----------------------------------------------------------------------------------------------------------------------------------
const char* OGLTexture::GetFileName() const
{
	return m_pFileName->GetFileName().c_str();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャの取得
//
// @return / unsigned int : テクスチャ
//	
// @note : 
//
// テクスチャを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
unsigned int OGLTexture::GetTexture() const 
{
	return m_uiTexture;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャの幅の取得
//
// @return / int : テクスチャの幅
//	
// @note : 
//
// テクスチャの幅を取得する。
//----------------------------------------------------------------------------------------------------------------------------------
int OGLTexture::GetWidth() const 
{
	return m_lWidth;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャの高さの取得
//
// @return / int : テクスチャの高さ
//	
// @note : 
//
// テクスチャの高さを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
int OGLTexture::GetHeight() const 
{
	return m_lHeight;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャの生成
//
// @param [in] / unsigned char* pucPixelData : テクスチャのピクセルデータ
//
// @note : 
//
// テクスチャを生成し、各種設定する。
//----------------------------------------------------------------------------------------------------------------------------------
void OGLTexture::GenerateTexture( unsigned char* pucPixelData ) 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( pucPixelData );



	// テクスチャを有効にする
	glEnable( GL_TEXTURE_2D );
	
	// テクスチャを生成
	glGenTextures( 1, &m_uiTexture );

	// テクスチャをバインド
	glBindTexture( GL_TEXTURE_2D, m_uiTexture );

	// テクスチャの貼り方を設定
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// テクスチャイメージを指定
	glTexImage2D( 
		GL_TEXTURE_2D, 
		0, 
		m_uiTextureFormat, 
		m_lWidth, 
		m_lHeight, 
		0, 
		m_uiTextureFormat, 
		GL_UNSIGNED_BYTE, 
		pucPixelData 
	);

	// バインド解除
	glBindTexture( GL_TEXTURE_2D, 0 );

	// テクスチャを無効にする
	glDisable( GL_TEXTURE_2D );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 24bitカラーのピクセルデータに変換
//
// @param [in, out] / unsigned char* pucPixelData : テクスチャのピクセルデータ
//
// @note : 
//
// 
//----------------------------------------------------------------------------------------------------------------------------------
void OGLTexture::ConvertPixelsTo24BitColor( unsigned char* pucPixelData )
{
	// ピクセル数( 幅×高さ×3( RGBで3つ ) )
	size_t uiPixelSize	= m_lWidth * m_lHeight * 3;

	// RGBフォーマットを設定
	m_uiTextureFormat	= GL_RGB;



	unsigned char	ucTmp	= 0;	// 保存用
	int				iIdx1	= 0;	// インデックス
	int				iIdx2	= 0;	// インデックス
	
	// ピクセルデータのBとRのスワッピング
	for ( unsigned int i = 0; i < uiPixelSize - 2; i += 3 ) 
	{
		// インデックス算出
		iIdx1 = ( m_lWidth * ( i / m_lWidth ) ) + i % m_lWidth;
/*	
		// BとRをスワップ( BGR → RGB )
		ucTmp						= pucPixelData[ iIdx1 ];
		pucPixelData[ iIdx1 ]		= pucPixelData[ iIdx1 + 2 ];
		pucPixelData[ iIdx1 + 2 ]	= ucTmp;
*/
ucTmp						= pucPixelData[ iIdx1 + 1 ];
pucPixelData[ iIdx1 + 1 ]		= pucPixelData[ iIdx1  ];
pucPixelData[ iIdx1  ]	= ucTmp;
	}

	// 上下左右反転
	for ( int y = 0; y < m_lHeight / 2; ++y )
	{
		for ( int x = 0; x < m_lWidth * 3; ++x )
		{
			// インデックス算出
			iIdx1 = x + ( 3 * m_lWidth * y );
			iIdx2 = x + ( 3 * m_lWidth * ( m_lHeight - 1 - y ) );
	
			// 点対称の位置にあるピクセルをスワップ
			ucTmp					= pucPixelData[ iIdx1 ];
			pucPixelData[ iIdx1 ]	= pucPixelData[ iIdx2 ];
			pucPixelData[ iIdx2 ]	= ucTmp;
		}
	}
}