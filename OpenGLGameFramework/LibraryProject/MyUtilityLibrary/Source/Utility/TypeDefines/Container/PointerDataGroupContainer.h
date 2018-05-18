#ifndef _INCLUDE_GUARD_POINTERDATAGROUPCONTAINER_H_
#define _INCLUDE_GUARD_POINTERDATAGROUPCONTAINER_H_



//==================================================================================================================================
// �C���N���[�h
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
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �|�C���^�f�[�^�^�O���[�v�R���e�i�N���X
//
// @note : 
//
// �O���[�v�R���e�i���Ǘ����A�����Ղ����삷��N���X�B
// �g�p����ۂɂ̓O���[�v�R���e�i�̃L�[�̌^�ƃO���[�v�̗v�f�̌^���w�肷��B
// 
// �e���v���[�g�̃N���X���w�肷��ۂ́A*��t�����Ɏw�肷��B
// �O���[�v�̗v�f�̌^T�̓|�C���^�^�Ƃ��Ĉ����B
//----------------------------------------------------------------------------------------------------------------------------------
template<class Key, class T>
class PointerDataGroupContainer 
{
private:

	typedef std::vector<T*>					Group;			// �O���[�v
	typedef typename std::map<Key, Group*>	Map;			// �}�b�v

	typedef typename Group::iterator		GroupIterator;	// �O���[�v�̃C�e���[�^
	typedef typename Map::iterator			MapIterator;	// �}�b�v�̃C�e���[�^

	typedef typename std::pair<Key, Group*>	MapPair;		// �}�b�v�̃y�A

public:

	// �R���X�g���N�^
	PointerDataGroupContainer() : m_pMapContainer( new Map() ) { }

	// �f�X�g���N�^
	~PointerDataGroupContainer() 
	{ 
		// �O���[�v�R���e�i�̍폜
		erase();

		// �O���[�v�R���e�i���폜
		SAFE_DELETE( m_pMapContainer );
	}



	// �O���[�v�̒ǉ�
	void addGroup( const Key& key ) 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );



		// �w��̃L�[���o�^����Ă��Ȃ���ΐV�K�̃O���[�v��ǉ�����
		if ( !isRegisteredKey( key ) ) 
		{
			m_pMapContainer->insert( MapPair( key, new Group() ) );
		}
	}



	// �w��O���[�v�ɗv�f��ǉ�
	void pushBack( const Key& key, T* element ) 
	{
		getGroup( key )->push_back( element );
	}



	// �w��O���[�v�̗v�f��
	unsigned int size( const Key& key ) 
	{
		return static_cast<unsigned int>( getGroup( key )->size() );
	}



	// �O���[�v�S�̗̂v�f��
	unsigned int size() const 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );



		// �O���[�v���ɗv�f�������Z���č��v�����߂�
		unsigned int uiSizeSum = 0;
		for each ( List group in m_pMapContainer ) { uiSizeSum += group->size(); }



		return uiSizeSum;
	}



	// �L�[�̓o�^����
	bool isRegisteredKey( const Key& key ) 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );

		// �w��̃L�[�̗v�f��1�ł��L��Γo�^����Ă���
		return 0 < m_pMapContainer->count( key );
	}



	// �w��O���[�v�̎Q��
	Group* getGroup( const Key& key ) //const 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );
		if ( !isRegisteredKey( key ) ) { HALT( "�w��̃O���[�v������܂���B" ); }
//		ASSERT_POINTER_CHECK( m_pMapContainer->at( key ) );

		return m_pMapContainer->at( key );
	}
	


	// �w��O���[�v�̃C�e���[�^�̈ʒu�̗v�f���폜
	GroupIterator erase( const Key& key, GroupIterator it ) 
	{
		SAFE_DELETE( (*it) );
		it = getGroup( key ).erase( it );

		return it;
	}



	// �w��O���[�v�̏����𖞂����v�f���폜
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



	// �O���[�v�S�̂̏����𖞂����v�f���폜
	template<class Func>
	void removeIf( Func fn ) 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );

		// �O���[�v���ɃO���[�v�̏����𖞂����v�f���폜
		for each ( MapPair* pair in m_pMapContainer ) { removeIf( pair->first, fn ); }
	}



	// �w��O���[�v�̑S�v�f���폜
	void clear( const Key& key ) 
	{
		for ( GroupIterator it = begin( key ); it != end( key ); it++ ) { SAFE_DELETE( (*it) ); }

		getGroup( key )->clear();
	}



	// �S�O���[�v�̑S�v�f���폜
	void clear() 
	{
		for ( MapIterator it = begin(); it != end(); it++ ) { clear( it->first ); }

		m_pMapContainer->clear();
	}



	// �w��O���[�v�̍폜
	void erase( const Key& key ) 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );



		// �w��O���[�v�̑S�v�f���폜
		clear( key );

		// �w��O���[�v���폜
		SAFE_DELETE( m_pMapContainer->at( key ) );	
		m_pMapContainer->erase( key );
	}



	// �O���[�v�R���e�i�̍폜
	void erase() 
	{
		// �O���[�v�R���e�i��������Ώ������Ȃ�
		if( !POINTER_CHECK( m_pMapContainer ) ) { return; };



		// �O���[�v���ɃO���[�v���폜
		MapIterator it = begin();
		while ( it != end() ) 
		{
			// ���݂̈ʒu��ۑ����A���̈ʒu�ɐi�߂�
			MapIterator tmp = it;
			tmp++;

			// ���݂̈ʒu�̃O���[�v���폜
			erase( it->first );

			// ���̈ʒu���擾
			it = tmp;
		}

		// �O���[�v�R���e�i���N���A
		m_pMapContainer->clear();

		// �O���[�v�R���e�i���폜
//		SAFE_DELETE( m_pMapContainer );
	}

private:

	// �w��O���[�v�̊J�n�ʒu
	GroupIterator begin( const Key& key ) 
	{
		return getGroup( key )->begin();
	}



	// �O���[�v�R���e�i�̊J�n�ʒu
	MapIterator begin() const 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );

		return m_pMapContainer->begin();
	}



	// �w��O���[�v�̏I���ʒu
	GroupIterator end( const Key& key )
	{
		return getGroup( key )->end();
	}


	
	// �O���[�v�R���e�i�̏I���ʒu
	MapIterator end() const 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );

		return m_pMapContainer->end();
	}

private:

	// �����o�ϐ�
	Map* m_pMapContainer;	// �O���[�v�R���e�i
};



#endif // #ifndef _INCLUDE_GUARD_POINTERDATAGROUPCONTAINER_H_