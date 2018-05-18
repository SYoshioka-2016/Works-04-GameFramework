#ifndef _INCLUDE_GUARD_POINTERDATAGROUPCONTAINER_H_
#define _INCLUDE_GUARD_POINTERDATAGROUPCONTAINER_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_SAFEDELETE_H_
#include "../MyUtility/SafeDelete.h"
#endif	// #ifndef _INCLUDE_GUARD_SAFEDELETE_H_

#ifndef _INCLUDE_GUARD_VECTOR_
#define _INCLUDE_GUARD_VECTOR_
#include <vector>
#endif	// #ifndef _INCLUDE_GUARD_VECTOR_

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
// @purpose : ポインタデータ型グループコンテナクラス
//
// @note : 
//
// グループコンテナを管理し、扱い易く操作するクラス。
// 使用する際にはグループコンテナのキーの型とグループの要素の型を指定する。
// 
// テンプレートのクラスを指定する際は、*を付けずに指定する。
// グループの要素の型Tはポインタ型として扱う。
//----------------------------------------------------------------------------------------------------------------------------------
template<class Key, class T>
class PointerDataGroupContainer 
{
private:

	typedef std::vector<T*>					Group;			// グループ
	typedef typename std::map<Key, Group*>	Map;			// マップ

	typedef typename Group::iterator		GroupIterator;	// グループのイテレータ
	typedef typename Map::iterator			MapIterator;	// マップのイテレータ

	typedef typename std::pair<Key, Group*>	MapPair;		// マップのペア

public:

	// コンストラクタ
	PointerDataGroupContainer() : m_pMapContainer( new Map() ) { }

	// デストラクタ
	~PointerDataGroupContainer() 
	{ 
		// グループコンテナの削除
		erase();

		// グループコンテナを削除
		SAFE_DELETE( m_pMapContainer );
	}



	// グループの追加
	void addGroup( const Key& key ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );



		// 指定のキーが登録されていなければ新規のグループを追加する
		if ( !isRegisteredKey( key ) ) 
		{
			m_pMapContainer->insert( MapPair( key, new Group() ) );
		}
	}



	// 指定グループに要素を追加
	void pushBack( const Key& key, T* element ) 
	{
		getGroup( key )->push_back( element );
	}



	// 指定グループの要素数
	unsigned int size( const Key& key ) 
	{
		return static_cast<unsigned int>( getGroup( key )->size() );
	}



	// グループ全体の要素数
	unsigned int size() const 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );



		// グループ毎に要素数を加算して合計を求める
		unsigned int uiSizeSum = 0;
		for each ( List group in m_pMapContainer ) { uiSizeSum += group->size(); }



		return uiSizeSum;
	}



	// キーの登録判定
	bool isRegisteredKey( const Key& key ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );

		// 指定のキーの要素が1つでも有れば登録されている
		return 0 < m_pMapContainer->count( key );
	}



	// 指定グループの参照
	Group* getGroup( const Key& key ) //const 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );
		if ( !isRegisteredKey( key ) ) { HALT( "指定のグループがありません。" ); }
//		ASSERT_POINTER_CHECK( m_pMapContainer->at( key ) );

		return m_pMapContainer->at( key );
	}
	


	// 指定グループのイテレータの位置の要素を削除
	GroupIterator erase( const Key& key, GroupIterator it ) 
	{
		SAFE_DELETE( (*it) );
		it = getGroup( key ).erase( it );

		return it;
	}



	// 指定グループの条件を満たす要素を削除
	template<class Func>
	void removeIf( const Key& key, Func fn ) 
	{
		ListIT begin	= begin( key );
		ListIT end		= end( key );
		ListIT it		= getGroup( key )->remove_if( begin, end, fn );

		end = end( key );
		while ( it != end ) 
		{
			SAFE_DELETE( *it );
			it = getGroup( key )->erase( it );
		}
	}



	// グループ全体の条件を満たす要素を削除
	template<class Func>
	void removeIf( Func fn ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );

		// グループ毎にグループの条件を満たす要素を削除
		for each ( MapPair* pair in m_pMapContainer ) { removeIf( pair->first, fn ); }
	}



	// 指定グループの全要素を削除
	void clear( const Key& key ) 
	{
		for ( GroupIterator it = begin( key ); it != end( key ); it++ ) { SAFE_DELETE( (*it) ); }

		getGroup( key )->clear();
	}



	// 全グループの全要素を削除
	void clear() 
	{
		for ( MapIterator it = begin(); it != end(); it++ ) { clear( it->first ); }

		m_pMapContainer->clear();
	}



	// 指定グループの削除
	void erase( const Key& key ) 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );



		// 指定グループの全要素を削除
		clear( key );

		// 指定グループを削除
		SAFE_DELETE( m_pMapContainer->at( key ) );	
		m_pMapContainer->erase( key );
	}



	// グループコンテナの削除
	void erase() 
	{
		// グループコンテナが無ければ処理しない
		if( !POINTER_CHECK( m_pMapContainer ) ) { return; };



		// グループ毎にグループを削除
		MapIterator it = begin();
		while ( it != end() ) 
		{
			// 現在の位置を保存し、次の位置に進める
			MapIterator tmp = it;
			tmp++;

			// 現在の位置のグループを削除
			erase( it->first );

			// 次の位置を取得
			it = tmp;
		}

		// グループコンテナをクリア
		m_pMapContainer->clear();

		// グループコンテナを削除
//		SAFE_DELETE( m_pMapContainer );
	}

private:

	// 指定グループの開始位置
	GroupIterator begin( const Key& key ) 
	{
		return getGroup( key )->begin();
	}



	// グループコンテナの開始位置
	MapIterator begin() const 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );

		return m_pMapContainer->begin();
	}



	// 指定グループの終了位置
	GroupIterator end( const Key& key )
	{
		return getGroup( key )->end();
	}


	
	// グループコンテナの終了位置
	MapIterator end() const 
	{
		// ポインタチェック
		ASSERT_POINTER_CHECK( m_pMapContainer );

		return m_pMapContainer->end();
	}

private:

	// メンバ変数
	Map* m_pMapContainer;	// グループコンテナ
};



#endif // #ifndef _INCLUDE_GUARD_POINTERDATAGROUPCONTAINER_H_