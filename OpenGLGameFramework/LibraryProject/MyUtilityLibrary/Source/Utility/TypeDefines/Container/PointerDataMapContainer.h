#ifndef _INCLUDE_GUARD_POINTERDATAMAPCONTAINER_H_
#define _INCLUDE_GUARD_POINTERDATAMAPCONTAINER_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_ASSERTION_H_
#include "Assertion.h"
#endif	// #ifndef _INCLUDE_GUARD_ASSERTION_H_

#ifndef _INCLUDE_GUARD_SAFEDELETE_H_
#include "SafeDelete.h"
#endif	// #ifndef _INCLUDE_GUARD_SAFEDELETE_H_

#ifndef _INCLUDE_GUARD_MAP_
#define _INCLUDE_GUARD_MAP_
#include <map>
#endif	// #ifndef _INCLUDE_GUARD_MAP_

#ifndef _INCLUDE_GUARD_ALGORITHM_
#define _INCLUDE_GUARD_ALGORITHM_
#include <algorithm>
#endif	// #ifndef _INCLUDE_GUARD_ALGORITHM_



//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ポインタデータ型マップコンテナクラス
//
// @note : 
//
// マップコンテナを管理し、扱い易く操作するクラス。
// 使用する際にはマップコンテナのキーの型とデータの型を指定する。
// 
// テンプレートのクラスを指定する際は、*を付けずに指定する。
// データの型Tはポインタ型として扱う。
//----------------------------------------------------------------------------------------------------------------------------------
template<class Key, class T>
class PointerDataMapContainer 
{
private:

	typedef std::map<Key, T*>			Map;			// マップ
	typedef typename Map::iterator		MapIterator;	// マップのイテレータ
	typedef typename std::pair<Key, T*>	MapPair;		// マップのペア

public:

	// コンストラクタ
	PointerDataMapContainer() : m_pMapContainer( new Map() ) { }

	// デストラクタ
	~PointerDataMapContainer() 
	{ 
		// マップの全要素を削除
		clear();

		// グループコンテナを削除
		SAFE_DELETE( m_pMapContainer );
	}



	// マップに要素を追加
	void addElement( const Key& key, T* element ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( element );

		GetMapContainer()->insert( MapPair( key, element ) );
	}



	// マップの要素の取得
	T* at( const Key& key ) const
	{
		// 指定のキーが登録されていなければならない
		ASSERT( isRegisteredKey( key ) && "登録されていないキーです。" );
		
		// ポインタチェック
		ASSERT_POINTER_CHECK( GetMapContainer()->at( key ) );



		return GetMapContainer()->at( key );
	}



	// マップの要素数の取得
	unsigned int size() const 
	{
		return GetMapContainer()->size();
	}



	// キーの登録判定
	bool isRegisteredKey( const Key& key ) const
	{
		// 指定のキーの要素が1つでも有れば登録されている
		return 0 < GetMapContainer()->count( key );
	}



	// マップの全要素を削除
	void clear() 
	{
		for ( MapIterator it = begin(); it != end(); ++it ) { SAFE_DELETE( (*it).second ); }

		GetMapContainer()->clear();
	}

private:

	// マップコンテナの先頭イテレータ
	const MapIterator begin() const
	{
		return GetMapContainer()->begin();
	}

	// マップコンテナの末尾イテレータ
	const MapIterator end() const
	{
		return GetMapContainer()->end();
	}

	// マップコンテナ
	Map* GetMapContainer() const
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );

		return m_pMapContainer;
	}

private:

	// メンバ変数
	Map* m_pMapContainer;	// マップコンテナ
};



#endif // #ifndef _INCLUDE_GUARD_POINTERDATAMAPCONTAINER_H_