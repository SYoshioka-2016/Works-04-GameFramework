//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_SOUNDCLIP_H_
#include "SoundClip.h"
#endif	// #ifndef _INCLUDE_GUARD_SOUNDCLIP_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



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
SoundClip::SoundClip() :
	m_pFileName( NULL ),
	m_bIsLoaded( false ),
	m_Format( SOUND_FORMAT::UNKNOWN_SOUND_FORMAT ),
	m_uiSamplingRate( 0 ),
	m_puiWaveDataSize( 0 ),
	m_pucWaveData( NULL )
{ }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
SoundClip::~SoundClip() 
{
	SAFE_DELETE( m_pFileName );

	// データのクリア
	Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : データのクリア
//
// @note : 
//
// 波形データ等を解放する。
//----------------------------------------------------------------------------------------------------------------------------------
void SoundClip::Clear() 
{
	SAFE_DELETE_ARRAY( m_pucWaveData );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ファイル名の取得
//
// @return / const FILE_NAME_STRUCTURE* : ファイル名
//	
// @note : 
//
// ファイル名構造体を取得する。
//----------------------------------------------------------------------------------------------------------------------------------
const FILE_NAME_STRUCTURE* SoundClip::GetFileName() const 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pFileName );



	return m_pFileName;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドフォーマットの取得
//
// @return / const SOUND_FORMAT : サウンドフォーマット
//	
// @note : 
//
// サウンドフォーマットを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
const SOUND_FORMAT SoundClip::GetFormat() const 
{
	return m_Format;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サンプリングレートの取得
//
// @return / const unsigned int : サンプリングレート
//	
// @note : 
//
// サンプリングレートを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int SoundClip::GetSamplingRate() const 
{
	return m_uiSamplingRate;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 波形データのサイズの取得
//
// @return / const unsigned int : 波形データのサイズ
//	
// @note : 
//
// 波形データのサイズを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned int SoundClip::GetWaveDataSize() const 
{
	return m_puiWaveDataSize;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 波形データの取得
//
// @return / const unsigned char* : 波形データ
//	
// @note : 
//
// 波形データを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
const unsigned char* SoundClip::GetWaveData() const 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pucWaveData );



	return m_pucWaveData;
}