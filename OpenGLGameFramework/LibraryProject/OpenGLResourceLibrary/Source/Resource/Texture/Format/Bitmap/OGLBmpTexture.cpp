//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_
#include "OGLBmpTexture.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLBMPTEXTURE_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



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
OGLBmpTexture::OGLBmpTexture()
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLBmpTexture::~OGLBmpTexture() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�N�X�`���̓ǂݍ���
//
// @param [in] / char* pcFileName : Bitmap�摜�t�@�C����
//
// @return / HRESULT : �e�N�X�`���̓ǂݍ��݂ɐ���������
//	
// @note : 
//
// �摜�t�@�C������f�[�^�̓ǂݍ��ݏ������s���B
// �t�@�C������Bitmap�t�@�C�������w�肷��B
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT OGLBmpTexture::Load( const char* pcFileName ) 
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



	// �r�b�g�}�b�v�̃t�@�C���w�b�_��ǂݍ���
	BITMAPFILEHEADER bmpFileHeader;
	fread( &bmpFileHeader, sizeof( BITMAPFILEHEADER ), 1, pFile );

	if ( 0x4d42 != bmpFileHeader.bfType ) 
	{
		DEBUG_CONSOLE_LOG( "\"%s\"��Bitmap�t�@�C���ł͂���܂���B", pcFileName );

		// �t�@�C�������
		fclose( pFile );

		return E_FAIL;
	}
	


	// �r�b�g�}�b�v�̏��w�b�_��ǂݍ���
	BITMAPINFOHEADER bmpInfoHeader;
	fread( &bmpInfoHeader, sizeof( BITMAPINFOHEADER ), 1, pFile );
	
	if ( BI_RGB != bmpInfoHeader.biCompression ) 
	{ 
		DEBUG_CONSOLE_LOG( "\"%s\"�͈��k�ɑΉ����Ă��܂���B", pcFileName ); 

		// �t�@�C�������
		fclose( pFile );

		return E_FAIL;
	}


	// �摜�̃T�C�Y���擾
	m_lWidth	= bmpInfoHeader.biWidth;
	m_lHeight	= bmpInfoHeader.biHeight;



	// 1�s�N�Z��������̃r�b�g���ʂɃs�N�Z���f�[�^�̃T�C�Y��ݒ肷��
	size_t uiPixelSize = 0;
	switch ( bmpInfoHeader.biBitCount )
	{
		// 24bit
		case 24: //Load24BitColorPixels( pFile ); break;
			uiPixelSize = m_lWidth * m_lHeight * 3;

			break;



		default: 
		
			DEBUG_CONSOLE_LOG( "\"%s\"�͑Ή����Ȃ��r�b�g���ł��B", pcFileName );

			// �t�@�C�������
			fclose( pFile );

			return E_FAIL;
	}



	// �s�N�Z���f�[�^�̃��������m��
	unsigned char* pucPixelData = new unsigned char [ uiPixelSize ];

	// �s�N�Z���f�[�^�̓ǂݍ���
	fread( pucPixelData, uiPixelSize, 1, pFile );

	// �t�@�C�������
	fclose( pFile );



	// �r�b�g���ʂɃs�N�Z���f�[�^��ϊ�
	switch ( bmpInfoHeader.biBitCount )
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