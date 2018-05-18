//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_
#include "TextureResourceLibrary.h"
#endif	// #ifndef _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_

#ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_
#include "../../Manager/ResourceManager.h"
#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X�̓ǂݍ���
//
// @param [in] / const char* strPath : ���\�[�X�t�@�C���̃p�X
//
// @return / const unsigned int : ���\�[�XID
//	
// @note : 
//
// �e�N�X�`�����\�[�X�t�@�C����ǂݍ��݁A�e�N�X�`�����\�[�X�𐶐�����B
// �����������\�[�X�ɑΉ����郊�\�[�XID��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern const unsigned int NS_Resource::NS_Texture::LoadTexture( const char* strPath )
{
	return NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->Load( strPath );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̎擾
//
// @param [in] / const unsigned int uiResourceID : ���\�[�XID
//
// @return / const OGLTexture* : �e�N�X�`��
//	
// @note : 
//
// �w��̃��\�[�XID�ɑΉ�����e�N�X�`����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern const NS_Resource::NS_Texture::OGLTexture* NS_Resource::NS_Texture::GetTexture( const unsigned int uiResourceID ) 
{
	return (OGLTexture*)NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->GetResource( uiResourceID );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`��ID�̎擾
//
// @param [in] / const unsigned int uiResourceID	: ���\�[�XID
// @param [in] / const bool			bEnableLog		: ���O�̗L���ݒ�
//
// @return / const unsigned int : �e�N�X�`��ID
//
// @note : 
//
// �w��̃��\�[�XID�ɑΉ�����e�N�X�`���̃e�N�X�`��ID��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern const unsigned int NS_Resource::NS_Texture::GetTextureID( const unsigned int uiResourceID, const bool bEnableLog ) 
{
	// �w��̃��\�[�XID�ɑΉ�����e�N�X�`�����擾
	OGLTexture* pTexture = (OGLTexture*)NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->GetResource( uiResourceID );

	// �e�N�X�`�����L��΂��̃e�N�X�`��ID��Ԃ�
	if ( POINTER_CHECK( pTexture ) ) 
	{
		return pTexture->GetTexture();
	}

	

	// ���O���L���ݒ�Ȃ烍�O���o�͂���
	if ( bEnableLog )
	{
		DEBUG_CONSOLE_LOG( "�w���ID\"%u\"�ɑΉ�����e�N�X�`��������܂���B", uiResourceID );
	}



	// �����o���Ȃ���΃G���[��ID��Ԃ�
	return 0;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̃N���A
//
// @note : 
//
// �Ǘ����Ă���e�N�X�`����S�č폜����B
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Resource::NS_Texture::ClearTexture()
{
	NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̃N���A
//
// @param [in] / const unsigned int uiResourceID : ���\�[�XID
//
// @note : 
//
// �Ǘ����Ă���e�N�X�`���̓��A�w��̃��\�[�XID�ɑΉ�����e�N�X�`�����폜����B
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Resource::NS_Texture::ClearTexture( const unsigned int uiResourceID )
{
	NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::TEXTURE )->Clear( uiResourceID );
}