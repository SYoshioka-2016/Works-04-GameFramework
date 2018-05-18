//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TEXTUREDIRECTOR_H_
#include "TextureDirector.h"
#endif	// #ifndef _INCLUDE_GUARD_TEXTUREDIRECTOR_H_

#ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_
#include "../../../Resource/Texture/Format/Bitmap/OGLBmpTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_

#ifndef _INCLUDE_GUARD_OGLTGATEXTURE_H_
#include "../../../Resource/Texture/Format/Targa/OGLTgaTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLTGATEXTURE_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// ���\�[�X���O���
using namespace NS_Resource;

// �e�N�X�`�����O���
using namespace NS_Texture;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
TextureDirector::TextureDirector() : ResourceDirector( eRESOURCE_TYPE::TEXTURE )
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
TextureDirector::~TextureDirector() 
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
// �e�N�X�`�����\�[�X�t�@�C����ǂݍ��݁A�e�N�X�`�����\�[�X�𐶐�����B
// �����������\�[�X�ɑΉ����郊�\�[�XID��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int TextureDirector::Load( const char* strPath )
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

	// �e�N�X�`��
	OGLTexture*			pTexture = nullptr;



	// �t�H�[�}�b�g�ʂɃe�N�X�`���𐶐�

	// Bitmap�t�@�C��
	if ( strcmp( filename.GetExtensions().c_str(), ".bmp" ) == 0 ) 
	{
		// Bitmap�t�H�[�}�b�g�e�N�X�`���𐶐�
		pTexture = new OGLBmpTexture;
	}

	// Targa�t�@�C��
	else if ( strcmp( filename.GetExtensions().c_str(), ".tga" ) == 0 ) 
	{
		// Targa�t�H�[�}�b�g�e�N�X�`���𐶐�
		pTexture = new OGLTgaTexture;
	}

	// �Ή����Ă��Ȃ��t�H�[�}�b�g�͓ǂݍ��܂Ȃ�
	else 
	{
		DEBUG_CONSOLE_LOG( "\"%s\"�͑Ή����Ă��Ȃ��t�H�[�}�b�g�ł��B", filename.GetExtensions().c_str() ); 
		
		return ERROR_RESOURCE_ID; 
	}



	// �e�N�X�`����ǂݍ���
	if ( FAILED( pTexture->Load( strPath ) ) ) 
	{
		SAFE_DELETE( pTexture );

		DEBUG_CONSOLE_LOG( "���\�[�X\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", strPath ); 
		
		return ERROR_RESOURCE_ID; 
	};



	// ���\�[�X�}�b�v�Ƀe�N�X�`����ǉ�
	return PushResource( strPath, pTexture );
}