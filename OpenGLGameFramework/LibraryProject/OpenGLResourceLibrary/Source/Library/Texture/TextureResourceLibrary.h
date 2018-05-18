#ifndef _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_
#define _INCLUDE_GUARD_TEXTURERESOURCELIBRARY_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_OGLTEXTURE_H_
#include "../../Resource/Texture/Base/OGLTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLTEXTURE_H_



//==================================================================================================================================
// ���O���
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���\�[�X���O���
//
// @note : 
//
// ���\�[�X�֘A�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Resource
{


	
//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`�����O���
//
// @note : 
//
// ���\�[�X�֘A�̓��A�e�N�X�`���֘A�̊֐���N���X�����Ǘ����閼�O��ԁB
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Texture
{



	// �e�N�X�`���̓ǂݍ���
	const unsigned int LoadTexture( const char* strPath );

	// �e�N�X�`���̎擾
	const OGLTexture* GetTexture( const unsigned int uiResourceID );

	// �e�N�X�`��ID�̎擾
	const unsigned int GetTextureID( const unsigned int uiResourceID, const bool bEnableLog = true );

	// �e�N�X�`���̃N���A
	void ClearTexture();

	// �e�N�X�`���̃N���A
	void ClearTexture( const unsigned int uiResourceID );



}	// namespace NS_Texture



}	// namespace NS_Resource 



#endif	// #ifndef _INCLUDE_GUARD_RESOURCEMANAGER_H_