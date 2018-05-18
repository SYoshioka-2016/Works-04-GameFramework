//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MODELRESOURCELIBRARY_H_
#include "ModelResourceLibrary.h"
#endif	// #ifndef _INCLUDE_GUARD_MODELRESOURCELIBRARY_H_

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
// ���f�����\�[�X�t�@�C����ǂݍ��݁A���f�����\�[�X�𐶐�����B
// �����������\�[�X�ɑΉ����郊�\�[�XID��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern const unsigned int NS_Resource::NS_Model::LoadModel( const char* strPath )
{
	return NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::MODEL )->Load( strPath );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���f���̎擾
//
// @param [in] / const unsigned int uiResourceID : ���\�[�XID
//
// @return / const OGLModel* : ���f��
//	
// @note : 
//
// �w��̃��\�[�XID�ɑΉ����郂�f����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
extern const NS_Resource::NS_Model::OGLModel* NS_Resource::NS_Model::GetModel( const unsigned int uiResourceID ) 
{
	return (OGLModel*)NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::MODEL )->GetResource( uiResourceID );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���f���̃N���A
//
// @note : 
//
// �Ǘ����Ă��郂�f����S�č폜����B
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Resource::NS_Model::ClearModel()
{
	NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::MODEL )->Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���f���̃N���A
//
// @param [in] / const unsigned int uiResourceID : ���\�[�XID
//
// @note : 
//
// �Ǘ����Ă��郂�f���̓��A�w��̃��\�[�XID�ɑΉ����郂�f�����폜����B
//----------------------------------------------------------------------------------------------------------------------------------
extern void NS_Resource::NS_Model::ClearModel( const unsigned int uiResourceID )
{
	NS_Resource::ResourceManager::Instance()->GetResourceDirector( eRESOURCE_TYPE::MODEL )->Clear( uiResourceID );
}