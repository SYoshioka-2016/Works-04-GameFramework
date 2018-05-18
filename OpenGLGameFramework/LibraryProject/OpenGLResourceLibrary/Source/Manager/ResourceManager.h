#ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_
#define _INCLUDE_GUARD_RESOURCEMANAGER_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_
#include "Director/Base/ResourceDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_



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
// @purpose : リソース管理クラス
//
// @extends / Singleton	: シングルトンクラス
//
// @note : 
//
// シングルトンクラス。
// リソースディレクタクラスを管理するクラス。
//----------------------------------------------------------------------------------------------------------------------------------
class ResourceManager : public Singleton<ResourceManager>
{
private:

	// フレンドクラス指定

	// シングルトンクラス
	friend Singleton<ResourceManager>;

public:

	// リソースディレクタの取得
	ResourceDirector* GetResourceDirector( const eRESOURCE_TYPE& resourceType );

	// リソースIDの発行
	const unsigned int IssueResourceID();

	// リソースのクリア
	void ClearResource();

private:

	// コンストラクタ
	ResourceManager();

	// デストラクタ
	~ResourceManager();



	// 乱数の発行
	static const unsigned int IssueRandomNumber();

private:

	// リソースマップ型
	typedef std::map<eRESOURCE_TYPE, ResourceDirector*> ResourceDirectorMap;
	


	// メンバ変数
	
	// リソースディレクタマップ
	ResourceDirectorMap m_ResourceDirectorMap;
};



}	// namespace NS_Resource 



#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_