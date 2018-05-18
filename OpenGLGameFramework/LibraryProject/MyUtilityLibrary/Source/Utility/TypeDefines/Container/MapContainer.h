#ifndef _INCLUDE_GUARD_MAPCONTAINER_H_
#define _INCLUDE_GUARD_MAPCONTAINER_H_



//==================================================================================================================================
// �C���N���[�h
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
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �|�C���^�f�[�^�^�}�b�v�R���e�i�N���X
//
// @note : 
//
// �}�b�v�R���e�i���Ǘ����A�����Ղ����삷��N���X�B
// �g�p����ۂɂ̓}�b�v�R���e�i�̃L�[�̌^�ƃf�[�^�̌^���w�肷��B
// 
// �e���v���[�g�̃N���X���w�肷��ۂ́A*��t�����Ɏw�肷��B
//----------------------------------------------------------------------------------------------------------------------------------
template<class Key, class T>
class MapContainer 
{
private:

	typedef std::map<Key, T>			Map;			// �}�b�v
	typedef typename Map::iterator		MapIterator;	// �}�b�v�̃C�e���[�^
	typedef typename std::pair<Key, T>	MapPair;		// �}�b�v�̃y�A

public:

	// �R���X�g���N�^
	MapContainer() : m_pMapContainer( new Map() ) { }

	// �f�X�g���N�^
	~MapContainer() 
	{ 
		// �}�b�v�̑S�v�f���폜
		clear();

		// �O���[�v�R���e�i���폜
		SAFE_DELETE( m_pMapContainer );
	}



	// �}�b�v�ɗv�f��ǉ�
	void addElement( const Key& key, T value ) 
	{
		GetMapContainer()->insert( MapPair( key, value ) );
	}



	// �}�b�v�̗v�f�̎擾
	const T at( const Key& key ) const
	{
		// �w��̃L�[���o�^����Ă��Ȃ���΂Ȃ�Ȃ�
		ASSERT( isRegisteredKey( key ) && "�o�^����Ă��Ȃ��L�[�ł��B" );

		return GetMapContainer()->at( key );
	}



	// �}�b�v�̗v�f���̎擾
	unsigned int size() const 
	{
		return GetMapContainer()->size();
	}



	// �L�[�̓o�^����
	bool isRegisteredKey( const Key& key ) const
	{
		// �w��̃L�[�̗v�f��1�ł��L��Γo�^����Ă���
		return 0 < GetMapContainer()->count( key );
	}



	// �}�b�v�̎w��̃L�[�ɑΉ�����l�ɑ��
	void setValue( const Key& key, const T value ) 
	{
		MapIterator iterator = GetMapContainer()->find( key );
		if ( end() == iterator ) { HALT( "�w��̃L�[������܂���B" ); return; }

		( *iterator ).second = value;
	}



	// �}�b�v�̎w��̗v�f���폜
	void erase( const Key& key ) 
	{
		GetMapContainer()->erase( key );
	}



	// �}�b�v�̑S�v�f���폜
	void clear() 
	{
		GetMapContainer()->clear();
	}

private:

	// �}�b�v�R���e�i�̐擪�C�e���[�^
	const MapIterator begin() const
	{
		return GetMapContainer()->begin();
	}

	// �}�b�v�R���e�i�̖����C�e���[�^
	const MapIterator end() const
	{
		return GetMapContainer()->end();
	}

	// �}�b�v�R���e�i
	Map* GetMapContainer() const
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_pMapContainer );

		return m_pMapContainer;
	}

private:

	// �����o�ϐ�
	Map* m_pMapContainer;	// �}�b�v�R���e�i
};



#endif // #ifndef _INCLUDE_GUARD_MAPCONTAINER_H_