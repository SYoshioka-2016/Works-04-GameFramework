//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_
#include "ResourceDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_

#ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_
#include "../../ResourceManager.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_



//==================================================================================================================================
// usingディレクティブ
//==================================================================================================================================

// リソース名前空間
using namespace NS_Resource;



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const eRESOURCE_TYPE& resourceType : リソースタイプ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
ResourceDirector::ResourceDirector( const eRESOURCE_TYPE& resourceType ) :
	m_ResourceType( resourceType ),
	m_ResourceMap( ResourceMap() )
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
ResourceDirector::~ResourceDirector()
{
	// リソースのクリア
	Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースのクリア
//
// @note : 
//
// コンテナ内のリソースを全て削除する。
//----------------------------------------------------------------------------------------------------------------------------------
void ResourceDirector::Clear()
{
/*
	std::for_each( 
		m_ResourceMap.begin(), 
		m_ResourceMap.end(), 
		[&] ( std::pair<RESOURCE_ID, void*> pair ) { SAFE_DELETE( pair.second ); }
	);
*/

	// 全てのリソースを削除する
	for each ( auto resourceMapPair in m_ResourceMap ) 
	{
		SAFE_DELETE( resourceMapPair.second );
	}
	
	m_ResourceMap.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースのクリア
//
// @param [in] / const unsigned int uiResourceID : リソースID
//
// @note : 
//
// コンテナ内の指定のリソースIDに対応するリソースを削除する。
//----------------------------------------------------------------------------------------------------------------------------------
void ResourceDirector::Clear( const unsigned int uiResourceID )
{
	// イテレータで走査する
	for ( 
		ResourceMap::iterator iterator = m_ResourceMap.begin();
		iterator != m_ResourceMap.end();
    )
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( iterator->second );



		// リソースIDが一致したらその要素を削除する
		if ( iterator->second->resourceInfo.id == uiResourceID ) 
		{
			SAFE_DELETE( iterator->second );

			m_ResourceMap.erase( iterator++ );
		}

		// 一致しなければそのままイテレータを進める
		else
		{
			++iterator;
		}
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースの取得
//
// @param [in] / const unsigned int uiResourceID	: リソースID
// @param [in] / const bool			bEnableLog		: ログの有効設定
//
// @return / const void* : リソースのポインタ
//	
// @note : 
//
// リソースマップの中から指定のリソースIDに対応するリソースを探し、
// そのリソースを返す。
//----------------------------------------------------------------------------------------------------------------------------------
const void* ResourceDirector::GetResource( const unsigned int uiResourceID, const bool bEnableLog ) const
{
	if ( m_ResourceMap.count( uiResourceID ) >= 1 ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_ResourceMap.at( uiResourceID ) );
		ASSERT_POINTER_CHECK( m_ResourceMap.at( uiResourceID )->resource );



		return m_ResourceMap.at( uiResourceID )->resource;
	}



	// ログが有効設定ならログを出力する
	if ( bEnableLog )
	{
		DEBUG_CONSOLE_LOG( "指定のID\"%u\"に対応するリソースがありません。", uiResourceID );
	}



	// 発見出来なければNULLを返す
	return nullptr;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースIDの取得
//
// @param [in] / const char*	strPath		: リソースファイルのパス
// @param [in] / const bool		bEnableLog	: ログの有効設定
//
// @return / const unsigned int : リソースID
//	
// @note : 
//
// リソースマップの中から指定のリソースファイルのパスに対応するリソースを探し、
// そのリソースのリソースIDを返す。
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int ResourceDirector::GetResourceID( const char* strPath, const bool bEnableLog ) const
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( strPath );



	// リソースマップを走査する
	for each ( auto resourceMapPair in m_ResourceMap ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( resourceMapPair.second );



		// リソースファイルのパスが一致したらその要素のリソースIDを返す
		if ( std::string( resourceMapPair.second->resourceInfo.path ) == std::string( strPath ) ) 
		{
			return resourceMapPair.second->resourceInfo.id;
		}
	}



	// ログが有効設定ならログを出力する
	if ( bEnableLog ) 
	{
		DEBUG_CONSOLE_LOG( "指定のパス\"%s\"に対応するリソースがありません。", strPath );
	}



	// 発見出来なければエラーのリソースIDを返す
	return ERROR_RESOURCE_ID;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースの追加
//
// @param [in] / const char*	strPath		: リソースファイルのパス
// @param [in] / void*			pResource	: リソース
//
// @return / const unsigned int : リソースID
//	
// @note : 
//
// リソースマップにリソースを追加する。
// 追加したリソースのIDを返す。
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int ResourceDirector::PushResource( const char* strPath, void* pResource ) 
{
	// リソース情報
	RESOURCE_INFO resourceInfo(
		ResourceManager::Instance()->IssueResourceID(),
		strPath,
		m_ResourceType
	);

	// リソースデータ
	RESOURCE_DATA* pResourceData = new RESOURCE_DATA( resourceInfo, pResource );

	// リソースマップにリソースデータを追加
	m_ResourceMap[ resourceInfo.id ] = pResourceData;



	return resourceInfo.id;
}