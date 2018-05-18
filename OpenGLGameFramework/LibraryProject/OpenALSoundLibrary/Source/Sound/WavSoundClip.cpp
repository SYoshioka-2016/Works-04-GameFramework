//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_
#include "WavSoundClip.h"
#endif	// #ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



//==================================================================================================================================
// �\���̒�`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : riff�\����
//
// @note : 
//
// 
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct 
{
	char			caRiffHeader[4];		// RIFF�w�b�_
	unsigned int	uiFileSize;				// �t�@�C���T�C�Y
	char			caWaveHeader[4];		// WAVE�w�b�_
} WAV_RIFF_HEADER;



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : fmt�`�����N�\����
//
// @note : 
//
// 
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct 
{
	unsigned char	ucaFmtChunk[4];			// fmt�`�����N
	unsigned int	uiFmtChunkSize;			// fmt�`�����N�̃T�C�Y
	unsigned short	usFormatID;				// �t�H�[�}�b�gID
	unsigned short	usChannels;				// �`�����l����
	unsigned int	uiSamplingRate;			// �T���v�����O���[�g(���g��)
	unsigned int	uiBytesPerSecond;		// �f�[�^���x(Byte / sec)
	unsigned short	usBlockSize;			// �u���b�N�T�C�Y
	unsigned short	usBitsPerSample;		// �T���v��������̃r�b�g��
} WAV_FMTCHUNK_HEADER;



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : data�`�����N�\����
//
// @note : 
//
// 
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct 
{
	char			caDataChunk[4];			// data�`�����N
	unsigned int	uiChunkSize;			// �g�`�f�[�^�̃o�C�g��
} WAV_DATACHUNK_HEADER;



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// �T�E���h���O���
using namespace NS_Sound;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
WavSoundClip::WavSoundClip() { }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
WavSoundClip::~WavSoundClip() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �t�@�C���ǂݍ���
//
// @param [in] / const char* pcFileName : WAVE�t�H�[�}�b�g�T�E���h�t�@�C����
//
// @return / HRESULT : �ǂݍ��݂ɐ���������
//	
// @note : 
//
// �T�E���h�t�@�C������f�[�^�̓ǂݍ��ݏ������s���B
// �t�@�C������WAVE�t�H�[�}�b�g�̃t�@�C�������w�肷��B
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT WavSoundClip::Load( const char* pcFileName ) 
{
	// ���ɓǂݍ��܂�Ă���Ώ������Ȃ�
	if ( m_bIsLoaded ) { return ERROR_MESSAGE( "���ɓǂݍ��܂�Ă��܂��B" ); }

	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( pcFileName );



	// �t�@�C�����𐶐�
	m_pFileName = new FILE_NAME_STRUCTURE( pcFileName );
	


	// �t�@�C�����J��
	FILE* pFile = NULL;
	if ( fopen_s( &pFile, m_pFileName->GetFullPath().c_str(), "rb" ) != 0 ) 
	{
		return ERROR_MESSAGE( "�t�@�C���I�[�v���Ɏ��s���܂����B" );
	}



	// riff�̓ǂݍ���
	WAV_RIFF_HEADER wavRiffHeader;
	fread( &wavRiffHeader, sizeof(WAV_RIFF_HEADER), 1, pFile );

	if ( strncmp( wavRiffHeader.caRiffHeader, "RIFF", 4 ) != 0 ) 
	{
		// �t�@�C�������
        fclose( pFile );

        return ERROR_MESSAGE( "RIFF�`�����N�ł͂���܂���B" );
    }

	if ( strncmp( wavRiffHeader.caWaveHeader, "WAVE", 4 ) != 0 ) 
	{
		// �t�@�C�������
        fclose( pFile );

        return ERROR_MESSAGE( "WAVE�t�H�[�}�b�g�ł͂���܂���B" );
    }



	// fmt�`�����N�̓ǂݍ���
	WAV_FMTCHUNK_HEADER wavFmtchunkHeader;
	fread( &wavFmtchunkHeader, sizeof(WAV_FMTCHUNK_HEADER), 1, pFile );



	// data�`�����N�̓ǂݍ���
	WAV_DATACHUNK_HEADER wavDatachunkHeader;
	fread( &wavDatachunkHeader, sizeof(WAV_DATACHUNK_HEADER), 1, pFile );
	
	if ( strncmp( wavDatachunkHeader.caDataChunk, "data", 4 ) != 0 ) 
	{
		// �t�@�C�������
        fclose( pFile );

        return ERROR_MESSAGE( "�f�[�^�`�����N�ł͂���܂���B" );
    }



	// �t�H�[�}�b�g��ݒ�
	switch ( wavFmtchunkHeader.usChannels )
	{
	case 1: 

		switch ( wavFmtchunkHeader.usBitsPerSample )
		{
		case  8: m_Format = SOUND_FORMAT::MONAURAL_8;	break;
		case 16: m_Format = SOUND_FORMAT::MONAURAL_16;	break;

		default: return ERROR_MESSAGE( "�T���v���̃r�b�g��������������܂���B" );
		}
		break;
	
	case 2: 

		switch ( wavFmtchunkHeader.usBitsPerSample )
		{
		case  8: m_Format = SOUND_FORMAT::STEREO_8;		break;
		case 16: m_Format = SOUND_FORMAT::STEREO_16;	break;

		default: return ERROR_MESSAGE( "�T���v���̃r�b�g��������������܂���B" );
		}
		break;

	default: return ERROR_MESSAGE( "�`�����l����������������܂���B" );
	}

	// �T���v�����O���[�g��ݒ�
	m_uiSamplingRate = wavFmtchunkHeader.uiSamplingRate;

	// �g�`�f�[�^�̃T�C�Y��ݒ�
	m_puiWaveDataSize = wavDatachunkHeader.uiChunkSize;

	// �g�`�f�[�^�̓ǂݍ���
	m_pucWaveData = new unsigned char [ m_puiWaveDataSize ];
	fread( m_pucWaveData, m_puiWaveDataSize, 1, pFile );



	// �t�@�C�������
	fclose( pFile );
	


	// �ǂݍ��݃t���O�𗧂Ă�
	m_bIsLoaded = true;



	return S_OK;
}