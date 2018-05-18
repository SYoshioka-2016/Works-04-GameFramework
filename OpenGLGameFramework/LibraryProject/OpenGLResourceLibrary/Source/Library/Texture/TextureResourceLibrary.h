#ifndef _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_
#define _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_OGLTEXTURE_H_
#include "../../Resource/Texture/Base/OGLTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLTEXTURE_H_



//==================================================================================================================================
// 名前空間
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソース名前空間
//
// @note : 
//
// リソース関連の関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Resource
{


	
//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャ名前空間
//
// @note : 
//
// リソース関連の内、テクスチャ関連の関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Texture
{



	// テクスチャの読み込み
	const unsigned int LoadTexture( const char* strPath );

	// テクスチャの取得
	const OGLTexture* GetTexture( const unsigned int uiResourceID );

	// テクスチャIDの取得
	const unsigned int GetTextureID( const unsigned int uiResourceID, const bool bEnableLog = true );

	// テクスチャのクリア
	void ClearTexture();

	// テクスチャのクリア
	void ClearTexture( const unsigned int uiResourceID );



}	// namespace NS_Texture



}	// namespace NS_Resource 



#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_