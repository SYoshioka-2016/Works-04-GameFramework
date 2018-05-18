#ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_
#define _INCLUDE_GUARD_OGLBMPTEXTURE_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLTEXTURE_H_
#include "../../Base/OGLTexture.h"
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



//==================================================================================================================================
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : Bitmap�t�H�[�}�b�g�e�N�X�`���N���X
//
// @extends / OGLTexture : �e�N�X�`���N���X
//
// @note : 
//
// Bitmap�t�H�[�}�b�g�̃e�N�X�`���N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class OGLBmpTexture : public OGLTexture
{
public:

	// �R���X�g���N�^
	OGLBmpTexture();

	// �f�X�g���N�^
	~OGLBmpTexture();

	

	// �e�N�X�`���̓ǂݍ���
	HRESULT Load( const char* pcFileName );

private:

	// �����o�ϐ�
};



}	// namespace NS_Texture



}	// namespace NS_Resource



#endif	// #ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_