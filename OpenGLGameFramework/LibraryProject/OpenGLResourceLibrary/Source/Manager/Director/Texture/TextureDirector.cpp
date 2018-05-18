//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TEXTUREDIRECTOR_H_
#include "TextureDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_TEXTUREDIRECTOR_H_

#ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_
#include "../../../Resource/Texture/Format/Bitmap/OGLBmpTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_

#ifndef _INCLUDE_GUARD_OGLTGATEXTURE_H_
#include "../../../Resource/Texture/Format/Targa/OGLTgaTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLTGATEXTURE_H_



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
TextureDirector::TextureDirector() : ResourceDirector( eRESOURCE_TYPE::TEXTURE )
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
TextureDirector::~TextureDirector() 
{
	// リソースのクリア
	Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースの読み込み
//
// @param [in] / const char* strPath : リソースファイルのパス
//
// @return / const unsigned int : リソースID
//	
// @note : 
//
// テクスチャリソースファイルを読み込み、テクスチャリソースを生成する。
// 生成したリソースに対応するリソースIDを返す。
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int TextureDirector::Load( const char* strPath )
{
	// 同じリソースが既に読み込まれていないかチェックする

	unsigned int uiResourceID = GetResourceID( strPath, false );

	if ( uiResourceID != ERROR_RESOURCE_ID ) 
	{
		DEBUG_CONSOLE_LOG( "リソース\"%s\"は既に読み込まれています。", strPath );

		return uiResourceID;
	}



	// ファイル名構造体
	FILE_NAME_STRUCTURE filename( strPath );

	// テクスチャ
	OGLTexture*			pTexture = nullptr;



	// フォーマット別にテクスチャを生成

	// Bitmapファイル
	if ( strcmp( filename.GetExtensions().c_str(), ".bmp" ) == 0 ) 
	{
		// Bitmapフォーマットテクスチャを生成
		pTexture = new OGLBmpTexture;
	}

	// Targaファイル
	else if ( strcmp( filename.GetExtensions().c_str(), ".tga" ) == 0 ) 
	{
		// Targaフォーマットテクスチャを生成
		pTexture = new OGLTgaTexture;
	}

	// 対応していないフォーマットは読み込まない
	else 
	{
		DEBUG_CONSOLE_LOG( "\"%s\"は対応していないフォーマットです。", filename.GetExtensions().c_str() ); 
		
		return ERROR_RESOURCE_ID; 
	}



	// テクスチャを読み込む
	if ( FAILED( pTexture->Load( strPath ) ) ) 
	{
		SAFE_DELETE( pTexture );

		DEBUG_CONSOLE_LOG( "リソース\"%s\"の読み込みに失敗しました。", strPath ); 
		
		return ERROR_RESOURCE_ID; 
	};



	// リソースマップにテクスチャを追加
	return PushResource( strPath, pTexture );
}