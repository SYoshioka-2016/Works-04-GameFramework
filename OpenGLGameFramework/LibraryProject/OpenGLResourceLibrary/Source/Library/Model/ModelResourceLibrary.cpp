//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MODELRESOURCELIBRARY_H_
#include "ModelResourceLibrary.h"
#endif	// #ifndef _INCLUDE_GUARD_MODELRESOURCELIBRARY_H_

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
// モデルリソースファイルを読み込み、モデルリソースを生成する。
// 生成したリソースに対応するリソースIDを返す。
//----------------------------------------------------------------------------------------------------------------------------------
extern const unsigned int NS_Resource::NS_Model::LoadModel( const char* strPath )
{
	return NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::MODEL )->Load( strPath );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : モデルの取得
//
// @param [in] / const unsigned int uiResourceID : リソースID
//
// @return / const OGLModel* : モデル
//	
// @note : 
//
// 指定のリソースIDに対応するモデルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
extern const NS_Resource::NS_Model::OGLModel* NS_Resource::NS_Model::GetModel( const unsigned int uiResourceID ) 
{
	return (OGLModel*)NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::MODEL )->GetResource( uiResourceID );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : モデルのクリア
//
// @note : 
//
// 管理しているモデルを全て削除する。
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Resource::NS_Model::ClearModel()
{
	NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::MODEL )->Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : モデルのクリア
//
// @param [in] / const unsigned int uiResourceID : リソースID
//
// @note : 
//
// 管理しているモデルの内、指定のリソースIDに対応するモデルを削除する。
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Resource::NS_Model::ClearModel( const unsigned int uiResourceID )
{
	NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::MODEL )->Clear( uiResourceID );
}