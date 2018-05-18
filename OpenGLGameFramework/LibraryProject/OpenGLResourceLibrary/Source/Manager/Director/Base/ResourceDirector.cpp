//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_
#include "ResourceDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEDIRECTOR_H_

#ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_
#include "../../ResourceManager.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// ���\�[�X���O���
using namespace NS_Resource;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @param [in] / const eRESOURCE_TYPE& resourceType : ���\�[�X�^�C�v
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
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
ResourceDirector::~ResourceDirector()
{
	// ���\�[�X�̃N���A
	Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X�̃N���A
//
// @note : 
//
// �R���e�i���̃��\�[�X��S�č폜����B
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

	// �S�Ẵ��\�[�X���폜����
	for each ( auto resourceMapPair in m_ResourceMap ) 
	{
		SAFE_DELETE( resourceMapPair.second );
	}
	
	m_ResourceMap.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X�̃N���A
//
// @param [in] / const unsigned int uiResourceID : ���\�[�XID
//
// @note : 
//
// �R���e�i���̎w��̃��\�[�XID�ɑΉ����郊�\�[�X���폜����B
//----------------------------------------------------------------------------------------------------------------------------------
void ResourceDirector::Clear( const unsigned int uiResourceID )
{
	// �C�e���[�^�ő�������
	for ( 
		ResourceMap::iterator iterator = m_ResourceMap.begin();
		iterator != m_ResourceMap.end();
    )
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( iterator->second );



		// ���\�[�XID����v�����炻�̗v�f���폜����
		if ( iterator->second->resourceInfo.id == uiResourceID ) 
		{
			SAFE_DELETE( iterator->second );

			m_ResourceMap.erase( iterator++ );
		}

		// ��v���Ȃ���΂��̂܂܃C�e���[�^��i�߂�
		else
		{
			++iterator;
		}
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X�̎擾
//
// @param [in] / const unsigned int uiResourceID	: ���\�[�XID
// @param [in] / const bool			bEnableLog		: ���O�̗L���ݒ�
//
// @return / const void* : ���\�[�X�̃|�C���^
//	
// @note : 
//
// ���\�[�X�}�b�v�̒�����w��̃��\�[�XID�ɑΉ����郊�\�[�X��T���A
// ���̃��\�[�X��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
const void* ResourceDirector::GetResource( const unsigned int uiResourceID, const bool bEnableLog ) const
{
	if ( m_ResourceMap.count( uiResourceID ) >= 1 ) 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( m_ResourceMap.at( uiResourceID ) );
		ASSERT_POINTER_CHECK( m_ResourceMap.at( uiResourceID )->resource );



		return m_ResourceMap.at( uiResourceID )->resource;
	}



	// ���O���L���ݒ�Ȃ烍�O���o�͂���
	if ( bEnableLog )
	{
		DEBUG_CONSOLE_LOG( "�w���ID\"%u\"�ɑΉ����郊�\�[�X������܂���B", uiResourceID );
	}



	// �����o���Ȃ����NULL��Ԃ�
	return nullptr;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�XID�̎擾
//
// @param [in] / const char*	strPath		: ���\�[�X�t�@�C���̃p�X
// @param [in] / const bool		bEnableLog	: ���O�̗L���ݒ�
//
// @return / const unsigned int : ���\�[�XID
//	
// @note : 
//
// ���\�[�X�}�b�v�̒�����w��̃��\�[�X�t�@�C���̃p�X�ɑΉ����郊�\�[�X��T���A
// ���̃��\�[�X�̃��\�[�XID��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int ResourceDirector::GetResourceID( const char* strPath, const bool bEnableLog ) const
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( strPath );



	// ���\�[�X�}�b�v�𑖍�����
	for each ( auto resourceMapPair in m_ResourceMap ) 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( resourceMapPair.second );



		// ���\�[�X�t�@�C���̃p�X����v�����炻�̗v�f�̃��\�[�XID��Ԃ�
		if ( std::string( resourceMapPair.second->resourceInfo.path ) == std::string( strPath ) ) 
		{
			return resourceMapPair.second->resourceInfo.id;
		}
	}



	// ���O���L���ݒ�Ȃ烍�O���o�͂���
	if ( bEnableLog ) 
	{
		DEBUG_CONSOLE_LOG( "�w��̃p�X\"%s\"�ɑΉ����郊�\�[�X������܂���B", strPath );
	}



	// �����o���Ȃ���΃G���[�̃��\�[�XID��Ԃ�
	return ERROR_RESOURCE_ID;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X�̒ǉ�
//
// @param [in] / const char*	strPath		: ���\�[�X�t�@�C���̃p�X
// @param [in] / void*			pResource	: ���\�[�X
//
// @return / const unsigned int : ���\�[�XID
//	
// @note : 
//
// ���\�[�X�}�b�v�Ƀ��\�[�X��ǉ�����B
// �ǉ��������\�[�X��ID��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int ResourceDirector::PushResource( const char* strPath, void* pResource ) 
{
	// ���\�[�X���
	RESOURCE_INFO resourceInfo(
		ResourceManager::Instance()->IssueResourceID(),
		strPath,
		m_ResourceType
	);

	// ���\�[�X�f�[�^
	RESOURCE_DATA* pResourceData = new RESOURCE_DATA( resourceInfo, pResource );

	// ���\�[�X�}�b�v�Ƀ��\�[�X�f�[�^��ǉ�
	m_ResourceMap[ resourceInfo.id ] = pResourceData;



	return resourceInfo.id;
}