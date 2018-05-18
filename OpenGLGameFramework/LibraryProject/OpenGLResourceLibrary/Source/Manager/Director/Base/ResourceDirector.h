#ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_
#define _INCLUDE_GUARD_RESOURCEDIRECTOR_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_RESOURCEDATA_H_
#include "../../../ResourceInfo/ResourceData.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEDATA_H_



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



//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : リソースディレクタクラス
//
// @note : 
//
// リソースを管理するクラス。
// テクスチャやサウンドなどのディレクタクラスのベースとなる。
//----------------------------------------------------------------------------------------------------------------------------------
class ResourceDirector
{
public:

	// コンストラクタ
	ResourceDirector( const eRESOURCE_TYPE& resourceType );

	// デストラクタ
	virtual ~ResourceDirector();



	// リソースの読み込み
	virtual const unsigned int Load( const char* strPath ) = 0;

	// リソースのクリア
	void Clear();

	// リソースのクリア
	void Clear( const unsigned int uiResourceID );

	

	// リソースの取得
	const void* GetResource( const unsigned int uiResourceID, const bool bEnableLog = true ) const;

	// リソースIDの取得
	const unsigned int GetResourceID( const char* strPath, const bool bEnableLog = true ) const;

protected:

	// リソースの追加
	const unsigned int PushResource( const char* strPath, void* pResource );

protected:

	// リソースマップ型
	typedef std::map<const unsigned int, RESOURCE_DATA*> ResourceMap;
	


	// メンバ変数

	// リソースタイプ
	eRESOURCE_TYPE		m_ResourceType;

	// リソースマップ
	ResourceMap			m_ResourceMap;
};



}	// namespace NS_Resource 



#endif	// #ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_