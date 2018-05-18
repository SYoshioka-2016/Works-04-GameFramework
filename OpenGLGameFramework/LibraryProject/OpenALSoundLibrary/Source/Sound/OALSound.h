#ifndef _INCLUDE_GUARD_OALSOUND_H_
#define _INCLUDE_GUARD_OALSOUND_H_



//==================================================================================================================================
// 名前空間
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンド名前空間
//
// @note : 
//
// サウンド関連の関数やクラス等を管理する名前空間。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_Sound 
{


	// OpenALの初期化
	void InitializeOpenAL();

	// サウンドの読み込み
	void Load( const char* pcFileName, const char* pcSetSoundName );

	// サウンドの再生
	void Play( const char* pcSoundName = 0, const bool bIsLoop = false );

	// サウンドの一時停止
	void Pause( const char* pcSoundName = 0 );

	// サウンドの停止
	void Stop( const char* pcSoundName = 0 );

	// 音量の変更
	void ChangeVolume( const float fVolume );
	
	// 音量の変更
	void ChangeVolume( const char* pcSoundName, const float fVolume );

	// ピッチの変更
	void ChangePitch( const float fPitch );

	// ピッチの設定
	void ChangePitch( const char* pcSoundName, const float fPitch );

	// サウンドのクリア
	void Clear();
	


}	// namespace NS_Sound



#endif	// #ifndef _INCLUDE_GUARD_OALSOUND_H_