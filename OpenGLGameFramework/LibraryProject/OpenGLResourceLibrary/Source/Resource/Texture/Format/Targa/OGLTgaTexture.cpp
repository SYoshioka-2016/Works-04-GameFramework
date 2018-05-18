//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLTGATEXTURE_H_
#include "OGLTgaTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLTGATEXTURE_H_

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
OGLTgaTexture::OGLTgaTexture()
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLTgaTexture::~OGLTgaTexture() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̓ǂݍ���
//
// @param [in] / char* pcFileName : Targa�摜�t�@�C����
//
// @return / HRESULT : �e�N�X�`���̓ǂݍ��݂ɐ���������
//	
// @note : 
//
// �摜�t�@�C������f�[�^�̓ǂݍ��ݏ������s���B
// �t�@�C������Targa�t�@�C�������w�肷��B
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT OGLTgaTexture::Load( const char* pcFileName ) 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( pcFileName );



	// ���ɓǂݍ��܂�Ă���Ώ������Ȃ�
	if ( m_bLoadFlg ) 
	{ 
		DEBUG_CONSOLE_LOG( "\"%s\"�͊��ɓǂݍ��܂�Ă��܂��B", pcFileName ); 

		return E_FAIL;
	}



	// �t�@�C�����J��
	FILE* pFile = nullptr;
	if ( fopen_s( &pFile, pcFileName, "rb" ) != 0 ) 
	{
		DEBUG_CONSOLE_LOG( "\"%s\"�̃t�@�C���I�[�v���Ɏ��s���܂����B", pcFileName );

		return E_FAIL;
	}



	// Targa�̃t�@�C���w�b�_��ǂݍ���
	unsigned char ucHeader[ 18 ] = { };
	fread( ucHeader, sizeof( ucHeader ), 1, pFile );



	// �e�N�X�`���̃T�C�Y��ݒ�
	m_lWidth  = ( ucHeader[ 13 ] * 256 ) + ucHeader[ 12 ];
	m_lHeight = ( ucHeader[ 15 ] * 256 ) + ucHeader[ 14 ];
	
	// �r�b�g�[�x
	unsigned int uiBitCount = ucHeader[ 16 ];

	// 1�s�N�Z��������̃o�C�g��
	unsigned int uiBytePerPixel = uiBitCount / 8;

	// �t�H�[�}�b�g��ݒ�
	switch ( uiBitCount )
	{
		// 24bit
		case 24: m_uiTextureFormat = GL_RGB; break;

		// 32bit
		case 32: m_uiTextureFormat = GL_RGBA; break;



	default:
		
		DEBUG_CONSOLE_LOG( "\"%s\"�̃r�b�g�[�x�͑Ή����Ă��܂���B", pcFileName );

		// �t�@�C�������
		fclose( pFile );

		break;
	}

	// �s�N�Z���f�[�^�̃T�C�Y
	size_t uiPixelSize = m_lWidth * m_lHeight * uiBytePerPixel;



	// �s�N�Z���f�[�^�̃��������m��
	unsigned char* pucPixelData = new unsigned char [ uiPixelSize ];

	// �s�N�Z���f�[�^�̓ǂݍ���
	fread( pucPixelData, uiPixelSize, 1, pFile );

	// �t�@�C�������
	fclose( pFile );






	for ( unsigned int i = 0; i < uiPixelSize; i += uiBytePerPixel ) 
	{
		unsigned char ucTemp	= pucPixelData[ i ];
		pucPixelData[ i ]		= pucPixelData[ i + 2 ];
		pucPixelData[ i + 2 ]	= ucTemp;
	}

	for ( int i = 0; i < m_lHeight / 2; i++ )
	{
		for ( int j = 0; j < m_lWidth * (int)uiBytePerPixel; j++ )
		{
			// �C���f�b�N�X�Z�o
			int iIdx1 = j + ( (int)uiBytePerPixel * m_lWidth * i );
			int iIdx2 = j + ( (int)uiBytePerPixel * m_lWidth * ( m_lHeight - 1 - i ) );
	
			// �_�Ώ̂̈ʒu�ɂ���s�N�Z�����X���b�v
			unsigned char ucTemp	= pucPixelData[ iIdx1 ];
			pucPixelData[ iIdx1 ]	= pucPixelData[ iIdx2 ];
			pucPixelData[ iIdx2 ]	= ucTemp;
		}
	}

/*
	// �r�b�g�[�x�ʂɃs�N�Z���f�[�^��ϊ�
	switch ( uiBitCount )
	{
		// 24bit
		case 24: ConvertPixelsTo24BitColor( pucPixelData ); break;



		default: 

			DEBUG_CONSOLE_LOG( "\"%s\"�͑Ή����Ȃ��r�b�g���ł��B", pcFileName );

			SAFE_DELETE_ARRAY( pucPixelData );

			// �t�@�C�������
			fclose( pFile );

			return E_FAIL;
	}
*/


	// �e�N�X�`���̐���
	GenerateTexture( pucPixelData );

	// �s�N�Z���f�[�^���폜
	SAFE_DELETE_ARRAY( pucPixelData );



	// �t�@�C������ۑ�
	m_pFileName	= new FILE_NAME_STRUCTURE( pcFileName );

	// �ǂݍ��݃t���O�𗧂Ă�
	m_bLoadFlg = true;



	return S_OK;
}