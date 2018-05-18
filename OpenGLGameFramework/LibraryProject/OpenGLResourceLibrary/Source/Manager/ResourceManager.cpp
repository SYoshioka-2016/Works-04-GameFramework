//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_
#include "ResourceManager.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_

#ifndef _INCLUDE_GUARD_TEXTUREDIRECTOR_H_
#include "Director/Texture/TextureDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_TEXTUREDIRECTOR_H_

#ifndef _INCLUDE_GUARD_MODELDIRECTOR_H_
#include "Director/Model/ModelDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_MODELDIRECTOR_H_



//==================================================================================================================================
// usingディレクティブ
//==================================================================================================================================

// リソース名前空間
using namespace NS_Resource;

// テクスチャ名前空間
using namespace NS_Texture;

// モデル名前空間
using namespace NS_Model;



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
ResourceManager::ResourceManager() : m_ResourceDirectorMap( ResourceDirectorMap() )
{
	// リソースディレクタを生成

	// テクスチャディレクタ
	m_ResourceDirectorMap[ eRESOURCE_TYPE::TEXTURE ]	= new TextureDirector;

	// モデルディレクタ
	m_ResourceDirectorMap[ eRESOURCE_TYPE::MODEL ]		= new ModelDirector;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
ResourceManager::~ResourceManager() 
{
	// 全てのリソースディレクタを削除する
	for each ( auto resourceDirecterMapPair in m_ResourceDirectorMap ) 
	{
		SAFE_DELETE( resourceDirecterMapPair.second );
	}

	m_ResourceDirectorMap.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースディレクタの取得
//
// @param [in] / const eRESOURCE_TYPE& resourceType : リソースタイプ
//
// @return / ResourceDirector* : リソースディレクタのポインタ
//	
// @note : 
//
// 指定のリソースタイプに対応するリソースディレクタを返す。
//----------------------------------------------------------------------------------------------------------------------------------
ResourceDirector* ResourceManager::GetResourceDirector( const eRESOURCE_TYPE& resourceType ) 
{
	// 指定のリソースディレクタが無ければ処理しない
	if ( m_ResourceDirectorMap.count( resourceType ) <= 0 ) 
	{
		HALT( "指定のリソースディレクタがありません。" );

		return nullptr;
	}



	return m_ResourceDirectorMap.at( resourceType );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースIDの発行
//
// @return / const unsigned int : リソースID
//	
// @note : 
//
// 全てのリソースディレクタが管理するリソースを調べ、
// 存在していない唯一のリソースIDを発行して返す。
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int ResourceManager::IssueResourceID() 
{
	// リソースIDになるランダムな数値を発行する
	unsigned int uiRandomNumber = IssueRandomNumber();



if ( uiRandomNumber == ERROR_RESOURCE_ID ) 
{
	return IssueResourceID();
}



	// 全てのリソースディレクタから同じリソースIDがないか調べる
	for each ( auto resourceDirecterMapPair in m_ResourceDirectorMap ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( resourceDirecterMapPair.second );



		// 発行した乱数で何かリソースが取得出来ればもう一度発行し直す
		if ( resourceDirecterMapPair.second->GetResource( uiRandomNumber, false ) != nullptr ) 
		{
			// リソースIDを再発行する
			return IssueResourceID();
		}
	}



	// 発行した乱数をリソースIDとして返す
	return uiRandomNumber;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースのクリア
//
// @note : 
//
// 全てのリソースディレクタの全てのリソースを削除する。
//----------------------------------------------------------------------------------------------------------------------------------
void ResourceManager::ClearResource() 
{
	// リソースディレクタマップの要素が無ければ処理しない
	if ( m_ResourceDirectorMap.empty() ) { return; }



	// 全てのリソースディレクタのリソースをクリアする
	for each ( auto resourceDirecterMapPair in m_ResourceDirectorMap ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( resourceDirecterMapPair.second );



		// リソースをクリア
		resourceDirecterMapPair.second->Clear();
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 乱数の発行
//
// @return / const unsigned int : 乱数
//	
// @note : 
//
// リソースIDの元となる乱数を生成して返す。
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int ResourceManager::IssueRandomNumber() 
{
	return Random::RandomUInt( 1, UINT_MAX );
}