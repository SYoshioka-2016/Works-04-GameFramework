#ifndef _INCLUDE_GUARD_OGLTEXTURE_H_
#define _INCLUDE_GUARD_OGLTEXTURE_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_WINDOWS_H_
#define _INCLUDE_GUARD_WINDOWS_H_
#include <Windows.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWS_H_



//==================================================================================================================================
// �O���錾
//==================================================================================================================================
struct FILE_NAME_STRUCTURE;	// �t�@�C�����\����



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
// @purpose : �e�N�X�`���N���X
//
// @note : 
//
// �e�t�H�[�}�b�g�̃e�N�X�`���N���X�̃x�[�X�ƂȂ�N���X�B
// �摜�t�@�C������ǂݍ��񂾃f�[�^���Ǘ�����B
//----------------------------------------------------------------------------------------------------------------------------------
class OGLTexture 
{
protected:

	// �R���X�g���N�^
	OGLTexture();

public:

	// �f�X�g���N�^
	virtual ~OGLTexture();



	// �e�N�X�`���̓ǂݍ���
	HRESULT virtual Load( const char* pcFileName ) = 0;



	// �t�@�C�����̎擾
	const char* GetFileName() const;

	// �e�N�X�`���̎擾
	unsigned int GetTexture() const;

	// �e�N�X�`���̕��̎擾
	int GetWidth() const;

	// �e�N�X�`���̍����̎擾
	int GetHeight() const;

protected:

	// �e�N�X�`���̐���
	void GenerateTexture( unsigned char* pucPixelData );

	// 24bit�J���[�̃s�N�Z���f�[�^�ɕϊ�
	void ConvertPixelsTo24BitColor( unsigned char* pucPixelData );

protected:

	// �����o�ϐ�

	// �ǂݍ��݃t���O( true : �ǂݍ��� | false : �ǂݍ���łȂ� )
	bool					m_bLoadFlg;

	// �t�@�C����
	FILE_NAME_STRUCTURE*	m_pFileName;

	// �e�N�X�`���̃t�H�[�}�b�g
	unsigned int			m_uiTextureFormat;

	// �e�N�X�`��
	unsigned int			m_uiTexture;

	// �e�N�X�`���̕�
	long					m_lWidth;

	// �e�N�X�`���̍���
	long					m_lHeight;
};



}	// namespace NS_Texture



}	// namespace NS_Resource



#endif	// #ifndef _INCLUDE_GUARD_OGLTEXTURE_H_