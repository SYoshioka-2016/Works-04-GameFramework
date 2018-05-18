#ifndef _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_
#define _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_MAP_
#include <map>
#endif	// #ifndef _INCLUDE_GUARD_MAP_



//==================================================================================================================================
// 前方宣言
//==================================================================================================================================

// サウンドソースクラス
namespace NS_Sound { class OALSoundSource; }



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



//==================================================================================================================================
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドソース管理クラス
//
// @extends / Singleton	: シングルトンクラス
//
// @note : 
//
// シングルトンクラス。
// サウンドソースを管理するクラス。
//----------------------------------------------------------------------------------------------------------------------------------
class OALSoundSourceManager : public Singleton<OALSoundSourceManager>
{
private:

	// フレンドクラス指定

	// シングルトンクラス
	friend Singleton<OALSoundSourceManager>;

public:

	// サウンドの読み込み
	void Load( const char* pcFileName, const char* pcSetSoundName );

	// サウンドの再生
	void Play( const char* pcSoundName = NULL, const bool bIsLoop = false );

	// サウンドの一時停止
	void Pause( const char* pcSoundName = NULL );

	// サウンドの停止
	void Stop( const char* pcSoundName = NULL );

	// 音量の設定
	void SetVolume( const float fVolume );

	// 音量の設定
	void SetVolume( const char* pcSoundName, const float fVolume );

	// ピッチの設定
	void SetPitch( const float fPitch );

	// ピッチの設定
	void SetPitch( const char* pcSoundName, const float fPitch );

	// サウンドのクリア
	void Clear();

private:
	
	// コンストラクタ
	OALSoundSourceManager();

	// デストラクタ
	~OALSoundSourceManager();

private:
	
	// メンバ変数

	// 音量
	float									m_fVolume;

	// ピッチ
	float									m_fPitch;

	// サウンドソースマップ
	std::map<std::string, OALSoundSource*>	m_SoundSourceMap;
};



}	// namespace NS_Sound 



#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_