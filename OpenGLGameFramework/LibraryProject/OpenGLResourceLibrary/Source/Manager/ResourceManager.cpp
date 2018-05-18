//==================================================================================================================================
// �C���N���[�h
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
// using�f�B���N�e�B�u
//==================================================================================================================================

// ���\�[�X���O���
using namespace NS_Resource;

// �e�N�X�`�����O���
using namespace NS_Texture;

// ���f�����O���
using namespace NS_Model;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
ResourceManager::ResourceManager() : m_ResourceDirectorMap( ResourceDirectorMap() )
{
	// ���\�[�X�f�B���N�^�𐶐�

	// �e�N�X�`���f�B���N�^
	m_ResourceDirectorMap[ eRESOURCE_TYPE::TEXTURE ]	= new TextureDirector;

	// ���f���f�B���N�^
	m_ResourceDirectorMap[ eRESOURCE_TYPE::MODEL ]		= new ModelDirector;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
ResourceManager::~ResourceManager() 
{
	// �S�Ẵ��\�[�X�f�B���N�^���폜����
	for each ( auto resourceDirecterMapPair in m_ResourceDirectorMap ) 
	{
		SAFE_DELETE( resourceDirecterMapPair.second );
	}

	m_ResourceDirectorMap.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X�f�B���N�^�̎擾
//
// @param [in] / const eRESOURCE_TYPE& resourceType : ���\�[�X�^�C�v
//
// @return / ResourceDirector* : ���\�[�X�f�B���N�^�̃|�C���^
//	
// @note : 
//
// �w��̃��\�[�X�^�C�v�ɑΉ����郊�\�[�X�f�B���N�^��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
ResourceDirector* ResourceManager::GetResourceDirector( const eRESOURCE_TYPE& resourceType ) 
{
	// �w��̃��\�[�X�f�B���N�^��������Ώ������Ȃ�
	if ( m_ResourceDirectorMap.count( resourceType ) <= 0 ) 
	{
		HALT( "�w��̃��\�[�X�f�B���N�^������܂���B" );

		return nullptr;
	}



	return m_ResourceDirectorMap.at( resourceType );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�XID�̔��s
//
// @return / const unsigned int : ���\�[�XID
//	
// @note : 
//
// �S�Ẵ��\�[�X�f�B���N�^���Ǘ����郊�\�[�X�𒲂ׁA
// ���݂��Ă��Ȃ��B��̃��\�[�XID�𔭍s���ĕԂ��B
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int ResourceManager::IssueResourceID() 
{
	// ���\�[�XID�ɂȂ郉���_���Ȑ��l�𔭍s����
	unsigned int uiRandomNumber = IssueRandomNumber();



if ( uiRandomNumber == ERROR_RESOURCE_ID ) 
{
	return IssueResourceID();
}



	// �S�Ẵ��\�[�X�f�B���N�^���瓯�����\�[�XID���Ȃ������ׂ�
	for each ( auto resourceDirecterMapPair in m_ResourceDirectorMap ) 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( resourceDirecterMapPair.second );



		// ���s���������ŉ������\�[�X���擾�o����΂�����x���s������
		if ( resourceDirecterMapPair.second->GetResource( uiRandomNumber, false ) != nullptr ) 
		{
			// ���\�[�XID���Ĕ��s����
			return IssueResourceID();
		}
	}



	// ���s�������������\�[�XID�Ƃ��ĕԂ�
	return uiRandomNumber;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X�̃N���A
//
// @note : 
//
// �S�Ẵ��\�[�X�f�B���N�^�̑S�Ẵ��\�[�X���폜����B
//----------------------------------------------------------------------------------------------------------------------------------
void ResourceManager::ClearResource() 
{
	// ���\�[�X�f�B���N�^�}�b�v�̗v�f��������Ώ������Ȃ�
	if ( m_ResourceDirectorMap.empty() ) { return; }



	// �S�Ẵ��\�[�X�f�B���N�^�̃��\�[�X���N���A����
	for each ( auto resourceDirecterMapPair in m_ResourceDirectorMap ) 
	{
		// �|�C���^�`�F�b�N
		ASSERT_POINTER_CHECK( resourceDirecterMapPair.second );



		// ���\�[�X���N���A
		resourceDirecterMapPair.second->Clear();
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �����̔��s
//
// @return / const unsigned int : ����
//	
// @note : 
//
// ���\�[�XID�̌��ƂȂ闐���𐶐����ĕԂ��B
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int ResourceManager::IssueRandomNumber() 
{
	return Random::RandomUInt( 1, UINT_MAX );
}