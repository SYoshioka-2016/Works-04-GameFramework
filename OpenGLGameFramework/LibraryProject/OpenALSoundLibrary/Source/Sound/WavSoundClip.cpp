//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_
#include "WavSoundClip.h"
#endif	// #ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



//==================================================================================================================================
// 構造体定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : riff構造体
//
// @note : 
//
// 
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct 
{
	char			caRiffHeader[4];		// RIFFヘッダ
	unsigned int	uiFileSize;				// ファイルサイズ
	char			caWaveHeader[4];		// WAVEヘッダ
} WAV_RIFF_HEADER;



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : fmtチャンク構造体
//
// @note : 
//
// 
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct 
{
	unsigned char	ucaFmtChunk[4];			// fmtチャンク
	unsigned int	uiFmtChunkSize;			// fmtチャンクのサイズ
	unsigned short	usFormatID;				// フォーマットID
	unsigned short	usChannels;				// チャンネル数
	unsigned int	uiSamplingRate;			// サンプリングレート(周波数)
	unsigned int	uiBytesPerSecond;		// データ速度(Byte / sec)
	unsigned short	usBlockSize;			// ブロックサイズ
	unsigned short	usBitsPerSample;		// サンプルあたりのビット数
} WAV_FMTCHUNK_HEADER;



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : dataチャンク構造体
//
// @note : 
//
// 
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct 
{
	char			caDataChunk[4];			// dataチャンク
	unsigned int	uiChunkSize;			// 波形データのバイト数
} WAV_DATACHUNK_HEADER;



//==================================================================================================================================
// usingディレクティブ
//==================================================================================================================================

// サウンド名前空間
using namespace NS_Sound;



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
WavSoundClip::WavSoundClip() { }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
WavSoundClip::~WavSoundClip() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ファイル読み込み
//
// @param [in] / const char* pcFileName : WAVEフォーマットサウンドファイル名
//
// @return / HRESULT : 読み込みに成功したか
//	
// @note : 
//
// サウンドファイルからデータの読み込み処理を行う。
// ファイル名はWAVEフォーマットのファイル名を指定する。
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT WavSoundClip::Load( const char* pcFileName ) 
{
	// 既に読み込まれていれば処理しない
	if ( m_bIsLoaded ) { return ERROR_MESSAGE( "既に読み込まれています。" ); }

	// ポインタチェック
	ASSERT_POINTER_CHECK( pcFileName );



	// ファイル名を生成
	m_pFileName = new FILE_NAME_STRUCTURE( pcFileName );
	


	// ファイルを開く
	FILE* pFile = NULL;
	if ( fopen_s( &pFile, m_pFileName->GetFullPath().c_str(), "rb" ) != 0 ) 
	{
		return ERROR_MESSAGE( "ファイルオープンに失敗しました。" );
	}



	// riffの読み込み
	WAV_RIFF_HEADER wavRiffHeader;
	fread( &wavRiffHeader, sizeof(WAV_RIFF_HEADER), 1, pFile );

	if ( strncmp( wavRiffHeader.caRiffHeader, "RIFF", 4 ) != 0 ) 
	{
		// ファイルを閉じる
        fclose( pFile );

        return ERROR_MESSAGE( "RIFFチャンクではありません。" );
    }

	if ( strncmp( wavRiffHeader.caWaveHeader, "WAVE", 4 ) != 0 ) 
	{
		// ファイルを閉じる
        fclose( pFile );

        return ERROR_MESSAGE( "WAVEフォーマットではありません。" );
    }



	// fmtチャンクの読み込み
	WAV_FMTCHUNK_HEADER wavFmtchunkHeader;
	fread( &wavFmtchunkHeader, sizeof(WAV_FMTCHUNK_HEADER), 1, pFile );



	// dataチャンクの読み込み
	WAV_DATACHUNK_HEADER wavDatachunkHeader;
	fread( &wavDatachunkHeader, sizeof(WAV_DATACHUNK_HEADER), 1, pFile );
	
	if ( strncmp( wavDatachunkHeader.caDataChunk, "data", 4 ) != 0 ) 
	{
		// ファイルを閉じる
        fclose( pFile );

        return ERROR_MESSAGE( "データチャンクではありません。" );
    }



	// フォーマットを設定
	switch ( wavFmtchunkHeader.usChannels )
	{
	case 1: 

		switch ( wavFmtchunkHeader.usBitsPerSample )
		{
		case  8: m_Format = SOUND_FORMAT::MONAURAL_8;	break;
		case 16: m_Format = SOUND_FORMAT::MONAURAL_16;	break;

		default: return ERROR_MESSAGE( "サンプルのビット数が正しくありません。" );
		}
		break;
	
	case 2: 

		switch ( wavFmtchunkHeader.usBitsPerSample )
		{
		case  8: m_Format = SOUND_FORMAT::STEREO_8;		break;
		case 16: m_Format = SOUND_FORMAT::STEREO_16;	break;

		default: return ERROR_MESSAGE( "サンプルのビット数が正しくありません。" );
		}
		break;

	default: return ERROR_MESSAGE( "チャンネル数が正しくありません。" );
	}

	// サンプリングレートを設定
	m_uiSamplingRate = wavFmtchunkHeader.uiSamplingRate;

	// 波形データのサイズを設定
	m_puiWaveDataSize = wavDatachunkHeader.uiChunkSize;

	// 波形データの読み込み
	m_pucWaveData = new unsigned char [ m_puiWaveDataSize ];
	fread( m_pucWaveData, m_puiWaveDataSize, 1, pFile );



	// ファイルを閉じる
	fclose( pFile );
	


	// 読み込みフラグを立てる
	m_bIsLoaded = true;



	return S_OK;
}