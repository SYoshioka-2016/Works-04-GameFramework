//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MODELDIRECTOR_H_
#include "ModelDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_MODELDIRECTOR_H_

#ifndef _INCLUDE_GUARD_OGLOBJMODEL_H_
#include "../../../Resource/Model/Format/WavefrontOBJ/OGLObjModel.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLOBJMODEL_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// ���\�[�X���O���
using namespace NS_Resource;

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
ModelDirector::ModelDirector() : ResourceDirector( eRESOURCE_TYPE::MODEL )
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
ModelDirector::~ModelDirector() 
{
	// ���\�[�X�̃N���A
	Clear();
}



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
const unsigned int ModelDirector::Load( const char* strPath )
{
	// �������\�[�X�����ɓǂݍ��܂�Ă��Ȃ����`�F�b�N����

	unsigned int uiResourceID = GetResourceID( strPath, false );

	if ( uiResourceID != ERROR_RESOURCE_ID ) 
	{
		DEBUG_CONSOLE_LOG( "���\�[�X\"%s\"�͊��ɓǂݍ��܂�Ă��܂��B", strPath );

		return uiResourceID;
	}



	// �t�@�C�����\����
	FILE_NAME_STRUCTURE filename( strPath );

	// ���f��
	OGLModel*			pModel = nullptr;



	// �t�H�[�}�b�g�ʂɃ��f���𐶐�

	// WavefrontOBJ�t�@�C��
	if ( strcmp( filename.GetExtensions().c_str(), ".obj" ) == 0 ) 
	{
		// WavefrontOBJ�t�H�[�}�b�g���f���𐶐�
		pModel = new OGLObjModel;
	}

	// �Ή����Ă��Ȃ��t�H�[�}�b�g�͓ǂݍ��܂Ȃ�
	else 
	{
		DEBUG_CONSOLE_LOG( "\"%s\"�͑Ή����Ă��Ȃ��t�H�[�}�b�g�ł��B", filename.GetExtensions().c_str() ); 
		
		return ERROR_RESOURCE_ID; 
	}



	// ���f����ǂݍ���
	if ( FAILED( pModel->Load( strPath ) ) ) 
	{
		SAFE_DELETE( pModel );

		DEBUG_CONSOLE_LOG( "���\�[�X\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", strPath ); 
		
		return ERROR_RESOURCE_ID; 
	};



	// ���\�[�X�}�b�v�Ƀ��f����ǉ�
	return PushResource( strPath, pModel );
}