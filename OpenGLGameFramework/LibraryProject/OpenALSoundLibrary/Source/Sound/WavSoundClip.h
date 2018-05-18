#ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_
#define _INCLUDE_GUARD_WAVSOUNDCLIP_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_SOUNDCLIP_H_
#include "SoundClip.h"
#endif	// #ifndef _INCLUDE_GUARD_SOUNDCLIP_H_



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
// @purpose : WAVEフォーマットサウンドクリップクラス
//
// @extends / SoundClip : サウンドクリップ基底クラス
//
// @note : 
//
// WAVEフォーマットのサウンドクリップクラスクラス。
// WAVEフォーマット専用のファイル読み込みを実装する。
//----------------------------------------------------------------------------------------------------------------------------------
class WavSoundClip : public SoundClip
{
public:

	// コンストラクタ
	WavSoundClip();

	// デストラクタ
	~WavSoundClip();
	


	// ファイル読み込み
	HRESULT Load( const char* pcFileName );

private:

	// メンバ変数
};



}	// namespace NS_Sound



#endif	// #ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_