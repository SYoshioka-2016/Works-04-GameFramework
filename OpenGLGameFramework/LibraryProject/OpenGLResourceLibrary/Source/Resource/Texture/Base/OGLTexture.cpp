//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLTEXTURE_H_
#include "OGLTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLTEXTURE_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



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
OGLTexture::OGLTexture() :
	m_bLoadFlg( false ),
	m_pFileName( nullptr ),
	m_uiTextureFormat( 0 ),
	m_uiTexture( 0 ),
	m_lWidth( 0 ),
	m_lHeight( 0 )
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLTexture::~OGLTexture() 
{
	// �e�N�X�`�����폜
	glDeleteTextures( 1, &m_uiTexture );

	SAFE_DELETE( m_pFileName );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �t�@�C�����̎擾
//
// @return / const char* : �f�B���N�g���Ɗg���q���܂܂Ȃ��t�@�C����
//	
// @note : 
//
// �f�B���N�g���Ɗg���q���܂܂Ȃ��t�@�C�������擾����B
//----------------------------------------------------------------------------------------------------------------------------------
const char* OGLTexture::GetFileName() const
{
	return m_pFileName->GetFileName().c_str();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̎擾
//
// @return / unsigned int : �e�N�X�`��
//	
// @note : 
//
// �e�N�X�`�����擾����B
//----------------------------------------------------------------------------------------------------------------------------------
unsigned int OGLTexture::GetTexture() const 
{
	return m_uiTexture;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̕��̎擾
//
// @return / int : �e�N�X�`���̕�
//	
// @note : 
//
// �e�N�X�`���̕����擾����B
//----------------------------------------------------------------------------------------------------------------------------------
int OGLTexture::GetWidth() const 
{
	return m_lWidth;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̍����̎擾
//
// @return / int : �e�N�X�`���̍���
//	
// @note : 
//
// �e�N�X�`���̍������擾����B
//----------------------------------------------------------------------------------------------------------------------------------
int OGLTexture::GetHeight() const 
{
	return m_lHeight;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̐���
//
// @param [in] / unsigned char* pucPixelData : �e�N�X�`���̃s�N�Z���f�[�^
//
// @note : 
//
// �e�N�X�`���𐶐����A�e��ݒ肷��B
//----------------------------------------------------------------------------------------------------------------------------------
void OGLTexture::GenerateTexture( unsigned char* pucPixelData ) 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( pucPixelData );



	// �e�N�X�`����L���ɂ���
	glEnable( GL_TEXTURE_2D );
	
	// �e�N�X�`���𐶐�
	glGenTextures( 1, &m_uiTexture );

	// �e�N�X�`�����o�C���h
	glBindTexture( GL_TEXTURE_2D, m_uiTexture );

	// �e�N�X�`���̓\�����ݒ�
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// �e�N�X�`���C���[�W���w��
	glTexImage2D( 
		GL_TEXTURE_2D, 
		0, 
		m_uiTextureFormat, 
		m_lWidth, 
		m_lHeight, 
		0, 
		m_uiTextureFormat, 
		GL_UNSIGNED_BYTE, 
		pucPixelData 
	);

	// �o�C���h����
	glBindTexture( GL_TEXTURE_2D, 0 );

	// �e�N�X�`���𖳌��ɂ���
	glDisable( GL_TEXTURE_2D );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 24bit�J���[�̃s�N�Z���f�[�^�ɕϊ�
//
// @param [in, out] / unsigned char* pucPixelData : �e�N�X�`���̃s�N�Z���f�[�^
//
// @note : 
//
// 
//----------------------------------------------------------------------------------------------------------------------------------
void OGLTexture::ConvertPixelsTo24BitColor( unsigned char* pucPixelData )
{
	// �s�N�Z����( ���~�����~3( RGB��3�� ) )
	size_t uiPixelSize	= m_lWidth * m_lHeight * 3;

	// RGB�t�H�[�}�b�g��ݒ�
	m_uiTextureFormat	= GL_RGB;



	unsigned char	ucTmp	= 0;	// �ۑ��p
	int				iIdx1	= 0;	// �C���f�b�N�X
	int				iIdx2	= 0;	// �C���f�b�N�X
	
	// �s�N�Z���f�[�^��B��R�̃X���b�s���O
	for ( unsigned int i = 0; i < uiPixelSize - 2; i += 3 ) 
	{
		// �C���f�b�N�X�Z�o
		iIdx1 = ( m_lWidth * ( i / m_lWidth ) ) + i % m_lWidth;
/*	
		// B��R���X���b�v( BGR �� RGB )
		ucTmp						= pucPixelData[ iIdx1 ];
		pucPixelData[ iIdx1 ]		= pucPixelData[ iIdx1 + 2 ];
		pucPixelData[ iIdx1 + 2 ]	= ucTmp;
*/
ucTmp						= pucPixelData[ iIdx1 + 1 ];
pucPixelData[ iIdx1 + 1 ]		= pucPixelData[ iIdx1  ];
pucPixelData[ iIdx1  ]	= ucTmp;
	}

	// �㉺���E���]
	for ( int y = 0; y < m_lHeight / 2; ++y )
	{
		for ( int x = 0; x < m_lWidth * 3; ++x )
		{
			// �C���f�b�N�X�Z�o
			iIdx1 = x + ( 3 * m_lWidth * y );
			iIdx2 = x + ( 3 * m_lWidth * ( m_lHeight - 1 - y ) );
	
			// �_�Ώ̂̈ʒu�ɂ���s�N�Z�����X���b�v
			ucTmp					= pucPixelData[ iIdx1 ];
			pucPixelData[ iIdx1 ]	= pucPixelData[ iIdx2 ];
			pucPixelData[ iIdx2 ]	= ucTmp;
		}
	}
}