//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_
#include "TextureResourceLibrary.h"
#endif	// #ifndef _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_

#ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_
#include "../../Manager/ResourceManager.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

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
extern const unsigned int NS_Resource::NS_Texture::LoadTexture( const char* strPath )
{
	return NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->Load( strPath );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャの取得
//
// @param [in] / const unsigned int uiResourceID : リソースID
//
// @return / const OGLTexture* : テクスチャ
//	
// @note : 
//
// 指定のリソースIDに対応するテクスチャを返す。
//----------------------------------------------------------------------------------------------------------------------------------
extern const NS_Resource::NS_Texture::OGLTexture* NS_Resource::NS_Texture::GetTexture( const unsigned int uiResourceID ) 
{
	return (OGLTexture*)NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->GetResource( uiResourceID );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャIDの取得
//
// @param [in] / const unsigned int uiResourceID	: リソースID
// @param [in] / const bool			bEnableLog		: ログの有効設定
//
// @return / const unsigned int : テクスチャID
//
// @note : 
//
// 指定のリソースIDに対応するテクスチャのテクスチャIDを返す。
//----------------------------------------------------------------------------------------------------------------------------------
extern const unsigned int NS_Resource::NS_Texture::GetTextureID( const unsigned int uiResourceID, const bool bEnableLog ) 
{
	// 指定のリソースIDに対応するテクスチャを取得
	OGLTexture* pTexture = (OGLTexture*)NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->GetResource( uiResourceID );

	// テクスチャが有ればそのテクスチャIDを返す
	if ( POINTER_CHECK( pTexture ) ) 
	{
		return pTexture->GetTexture();
	}

	

	// ログが有効設定ならログを出力する
	if ( bEnableLog )
	{
		DEBUG_CONSOLE_LOG( "指定のID\"%u\"に対応するテクスチャがありません。", uiResourceID );
	}



	// 発見出来なければエラーのIDを返す
	return 0;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャのクリア
//
// @note : 
//
// 管理しているテクスチャを全て削除する。
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Resource::NS_Texture::ClearTexture()
{
	NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : テクスチャのクリア
//
// @param [in] / const unsigned int uiResourceID : リソースID
//
// @note : 
//
// 管理しているテクスチャの内、指定のリソースIDに対応するテクスチャを削除する。
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Resource::NS_Texture::ClearTexture( const unsigned int uiResourceID )
{
	NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->Clear( uiResourceID );
}