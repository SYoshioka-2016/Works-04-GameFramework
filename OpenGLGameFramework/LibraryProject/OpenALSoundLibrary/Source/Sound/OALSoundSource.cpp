//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_
#include "OALSoundSource.h"
#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_

#ifndef _INCLUDE_GUARD_SOUNDCLIP_H_
#include "SoundClip.h"
#endif	// #ifndef _INCLUDE_GUARD_SOUNDCLIP_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_ALC_H_
#include "../AL/alc.h"
#endif	// #ifndef _INCLUDE_GUARD_ALC_H_

#ifndef _INCLUDE_GUARD_AL_H_
#include "../AL/al.h"
#endif	// #ifndef _INCLUDE_GUARD_AL_H_



//==================================================================================================================================
// usingディレクティブ
//==================================================================================================================================

// サウンド名前空間
using namespace NS_Sound;



//==================================================================================================================================
// 列挙定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンド状態列挙
//
// @note : 
//
// サウンドの再生状態の列挙。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Sound 
{
	enum SOUND_STATE
	{
		STANDBY,				// 待機
		PLAYING,				// 再生
		PAUSED,					// 一時停止
		STOPPED,				// 停止

		UNKNOWN_SOUND_STATE,
	};
}



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @param [in] / const SoundClip* soundClip : サウンドクリップ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OALSoundSource::OALSoundSource( SoundClip* soundClip ) :
	m_bIsCreatedBufferFlg( false ),
	m_bIsCreatedSourceFlg( false ),
	m_fVolume( 1.0f ),
	m_fPitch( 1.0f )
{ 
	// ポインタチェック
	ASSERT_POINTER_CHECK( soundClip );



	// バッファの生成
	GenerateBuffer( soundClip );

	// ソースの生成
	GenerateSource();

	// 音量の設定
	SetVolume( m_fVolume );

	// ピッチの設定
	SetPitch( m_fPitch );



SAFE_DELETE( soundClip );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OALSoundSource::~OALSoundSource() 
{
	// サウンドの停止
	Stop();

	// ソースを削除
	alDeleteSources( 1, &m_uiSource );

	// バッファを削除
	alDeleteBuffers( 1, &m_uiBuffer );

	

m_bIsCreatedBufferFlg = m_bIsCreatedSourceFlg = false;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドの再生
//
// @param [in] / const bool bIsLoop : ループするか?( true : ループする | false : ループしない )
//
// @note : 
//
// サウンドを1回再生する。
// 引数で無限ループ再生を設定出来る。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::Play( const bool bIsLoop ) 
{
	// 再生状態なら処理しない
	if ( SOUND_STATE::PLAYING == GetCurrentState() ) { return; }



	// ソースのループ設定
	alSourcei( m_uiSource, AL_LOOPING, ( bIsLoop ) ? AL_TRUE : AL_FALSE );

	// ソースの再生
	alSourcePlay( m_uiSource );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドの一時停止
//
// @note : 
//
// サウンドを一時停止する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::Pause() 
{
	// 再生状態でないなら処理しない
	if ( SOUND_STATE::PLAYING != GetCurrentState() ) { return; }



	// ソースの一時停止
	alSourcePause( m_uiSource );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドの停止
//
// @note : 
//
// サウンドを停止する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::Stop() 
{
	// 再生状態でないなら処理しない
	if ( SOUND_STATE::PLAYING != GetCurrentState() ) { return; }



	// ソースの停止
	alSourceStop( m_uiSource );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 音量の変更
//
// @param [in] / float fVolume : 設定する音量( 範囲は0.0～1.0 )
//
// @note : 
//
// 音量をソースに反映する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::ChangeVolume( float fVolume ) const
{
	// ソースが生成されていなければ処理しない
	if ( !m_bIsCreatedSourceFlg ) { return; }



	// 音量を調整
	if ( 0.0f > fVolume )		{ fVolume = 0.0f; }
	else if ( 1.0f < fVolume )	{ fVolume = 1.0f; }



	// ソースの音量を設定
	alSourcef( m_uiSource, AL_GAIN, fVolume );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ピッチの変更
//
// @param [in] / float fPitch : 設定するピッチ( 0.0以上 )
//
// @note : 
//
// ピッチをソースに反映する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::ChangePitch( float fPitch ) const
{
	// ソースが生成されていなければ処理しない
	if ( !m_bIsCreatedSourceFlg ) { return; }



	// ピッチを調整
	if ( 0.0f > fPitch ) { fPitch = 0.0f; }



	// ソースのピッチを設定
	alSourcef( m_uiSource, AL_PITCH, fPitch );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 音量の取得
//
// @note : 
//
// 音量を取得する。
//----------------------------------------------------------------------------------------------------------------------------------
float OALSoundSource::GetVolume() const 
{
	return m_fVolume;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 音量の設定
//
// @param [in] / const float fVolume : 設定する音量( 範囲は0.0～1.0 )
//
// @note : 
//
// 音量を設定する。
// ソースへの反映も行う。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::SetVolume( const float fVolume ) 
{
	// ソースが生成されていなければ処理しない
	if ( !m_bIsCreatedSourceFlg ) { return; }



	// 音量を設定
	if ( 0.0f > fVolume )		{ m_fVolume = 0.0f; }
	else if ( 1.0f < fVolume )	{ m_fVolume = 1.0f; }
	else						{ m_fVolume = fVolume; }

	// 音量の変更
	ChangeVolume( m_fVolume );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ピッチの取得
//
// @note : 
//
// ピッチを取得する。
//----------------------------------------------------------------------------------------------------------------------------------
float OALSoundSource::GetPitch() const 
{
	return m_fPitch;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ピッチの設定
//
// @param [in] / const float fPitch : 設定するピッチ( 0.0以上 )
//
// @note : 
//
// ピッチを設定する。
// ソースへの反映も行う。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::SetPitch( const float fPitch ) 
{
	// ソースが生成されていなければ処理しない
	if ( !m_bIsCreatedSourceFlg ) { return; }



	// ピッチを調整
	if ( 0.0f > fPitch )	{ m_fPitch = 0.0f; }
	else					{ m_fPitch = fPitch; }

	// ピッチの変更
	ChangePitch( m_fPitch );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : バッファの生成
//
// @param [in] / const SoundClip* soundClip : サウンドクリップ
//
// @note : 
//
// サウンドクリップのデータからバッファを生成する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::GenerateBuffer( const SoundClip* soundClip ) 
{
	// 既にバッファが生成されていれば処理しない
	if ( m_bIsCreatedBufferFlg ) { return; }

	// ポインタチェック
	ASSERT_POINTER_CHECK( soundClip );



	// フォーマットを設定
	ALenum format;
	switch ( soundClip->GetFormat() )
	{
	case SOUND_FORMAT::MONAURAL_8:	format = AL_FORMAT_MONO8;		break;

	case SOUND_FORMAT::MONAURAL_16: format = AL_FORMAT_MONO16;		break;

	case SOUND_FORMAT::STEREO_8:	format = AL_FORMAT_STEREO8;		break;

	case SOUND_FORMAT::STEREO_16:	format = AL_FORMAT_STEREO16;	break;

	default: 

		HALT( "対応しないフォーマットです。" ); 
		SAFE_DELETE( soundClip );
		break;
	}



	// バッファを作成
	alGenBuffers( 1, &m_uiBuffer );

	// バッファに波形データをセット
	alBufferData(
		m_uiBuffer,
		format,
		soundClip->GetWaveData(),
		soundClip->GetWaveDataSize(),
		soundClip->GetSamplingRate()
	);



	// バッファ生成フラグを立てる
	m_bIsCreatedBufferFlg = true;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ソースの生成
//
// @note : 
//
// バッファからソースを生成する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSource::GenerateSource() 
{
	// 既にソースが生成されていれば処理しない
	if ( m_bIsCreatedSourceFlg ) { return; }

	// バッファが生成されていなければ処理しない
	if ( !m_bIsCreatedBufferFlg ) { return; }



	// ソースを作成
	alGenSources( 1, &m_uiSource );

	// ソースを設定
	alSourcei( m_uiSource, AL_BUFFER, m_uiBuffer );



	// ソース生成フラグを立てる
	m_bIsCreatedSourceFlg = true;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 現在の再生状態の取得
//
// @return / SOUND_STATE : 現在の再生状態
//	
// @note : 
//
// サウンドの現在の再生状態を取得する。
//----------------------------------------------------------------------------------------------------------------------------------
SOUND_STATE OALSoundSource::GetCurrentState() const
{
	STRONG_ASSERT( m_bIsCreatedSourceFlg && "ソースが生成されていません。" );



	// ソースの状態を取得
	int state = 0;
	alGetSourcei( m_uiSource, AL_SOURCE_STATE, &state );
	
	// ソースの状態別に処理
	switch ( state )
	{

	// 待機状態
	case AL_INITIAL:	return SOUND_STATE::STANDBY;

	// 再生状態
	case AL_PLAYING:	return SOUND_STATE::PLAYING;

	// 一時停止状態
	case AL_PAUSED:		return SOUND_STATE::PAUSED;

	// 停止状態
	case AL_STOPPED:	return SOUND_STATE::STOPPED;



	default:			return SOUND_STATE::UNKNOWN_SOUND_STATE;
	}
}