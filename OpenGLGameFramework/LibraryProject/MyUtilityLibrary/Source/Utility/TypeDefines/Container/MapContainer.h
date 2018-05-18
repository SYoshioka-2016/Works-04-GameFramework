#ifndef _INCLUDE_GUARD_MAPCONTAINER_H_
#define _INCLUDE_GUARD_MAPCONTAINER_H_



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
//----------------------------------------------------------------------------------------------------------------------------------
template<class Key, class T>
class MapContainer 
{
private:

	typedef std::map<Key, T>			Map;			// マップ
	typedef typename Map::iterator		MapIterator;	// マップのイテレータ
	typedef typename std::pair<Key, T>	MapPair;		// マップのペア

public:

	// コンストラクタ
	MapContainer() : m_pMapContainer( new Map() ) { }

	// デストラクタ
	~MapContainer() 
	{ 
		// マップの全要素を削除
		clear();

		// グループコンテナを削除
		SAFE_DELETE( m_pMapContainer );
	}



	// マップに要素を追加
	void addElement( const Key& key, T value ) 
	{
		GetMapContainer()->insert( MapPair( key, value ) );
	}



	// マップの要素の取得
	const T at( const Key& key ) const
	{
		// 指定のキーが登録されていなければならない
		ASSERT( isRegisteredKey( key ) && "登録されていないキーです。" );

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



	// マップの指定のキーに対応する値に代入
	void setValue( const Key& key, const T value ) 
	{
		MapIterator iterator = GetMapContainer()->find( key );
		if ( end() == iterator ) { HALT( "指定のキーがありません。" ); return; }

		( *iterator ).second = value;
	}



	// マップの指定の要素を削除
	void erase( const Key& key ) 
	{
		GetMapContainer()->erase( key );
	}



	// マップの全要素を削除
	void clear() 
	{
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



#endif // #ifndef _INCLUDE_GUARD_MAPCONTAINER_H_