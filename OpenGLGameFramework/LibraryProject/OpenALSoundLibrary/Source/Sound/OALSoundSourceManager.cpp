//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_
#include "OALSoundSourceManager.h"
#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCEMANAGER_H_

#ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_
#include "OALSoundSource.h"
#endif	// #ifndef _INCLUDE_GUARD_OALSOUNDSOURCE_H_

#ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_
#include "WavSoundClip.h"
#endif	// #ifndef _INCLUDE_GUARD_WAVSOUNDCLIP_H_



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
OALSoundSourceManager::OALSoundSourceManager() :
	m_fVolume( 1.0f ),
	m_fPitch( 1.0f )
{ }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OALSoundSourceManager::~OALSoundSourceManager() 
{
	// サウンドのクリア
	Clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドの読み込み
//
// @param [in] / const char* pcFileName		: ディレクトリと拡張子を含むサウンドファイル名
// @param [in] / const char* pcSetSoundName : マップコンテナに登録するキーとなるサウンド名
//
// @note : 
//
// サウンドファイルを読み込み、サウンドを生成する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Load( const char* pcFileName, const char* pcSetSoundName ) 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( pcFileName );
	ASSERT_POINTER_CHECK( pcSetSoundName );



	// 既にキーが登録されている( サウンドが読み込まれている )なら処理しない
	if ( m_SoundSourceMap.count( pcSetSoundName ) >= 1 ) { HALT( "既に読み込まれています。" ); return; }



	// ファイル名構造体
	FILE_NAME_STRUCTURE filename( pcFileName );

	// 生成するサウンドクリップ
	SoundClip*			pSoundClip		= NULL;

	// コンテナに追加するサウンドソース
	OALSoundSource*		pSoundSource	= NULL;



	// フォーマット別にサウンドクリップを生成

	// WAVEファイルの場合
	if ( strcmp( filename.GetExtensions().c_str(), ".wav" ) == 0 ) 
	{
		// WAVEフォーマットサウンドクリップを生成
		pSoundClip = new WavSoundClip;
	}

	// 対応していないフォーマットは読み込まない
	else 
	{
		HALT( "対応していないフォーマットです。" ); return;
	}



	// サウンドを読み込む
	if ( FAILED( pSoundClip->Load( pcFileName ) ) ) 
	{
		SAFE_DELETE( pSoundClip );
		HALT( "サウンドの読み込みに失敗しました。" ); return;
	};

	// サウンドソースを生成
	pSoundSource = new OALSoundSource( pSoundClip );

	// サウンドソースの音量を変更
	pSoundSource->ChangeVolume( m_fVolume * pSoundSource->GetVolume() );

	// サウンドソースのピッチを変更
	pSoundSource->ChangePitch( m_fPitch * pSoundSource->GetPitch() );

	// コンテナにサウンドソースを追加
	m_SoundSourceMap[ pcSetSoundName ] = pSoundSource;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドの再生
//
// @param [in] / const char*	pcSoundName	: マップコンテナにある要素を指定するキーとなるサウンド名
// @param [in] / const bool		bIsLoop		: ループするか?( true : ループする | false : ループしない )( 省略するとfalseになる )
//
// @note : 
//
// ( 指定の )サウンドを再生する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Play( const char* pcSoundName, const bool bIsLoop ) 
{
	// 指定のサウンドが有る場合
	if ( POINTER_CHECK( pcSoundName ) ) 
	{
		// コンテナに指定の要素が無ければ処理しない
		if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "指定のサウンドがありません。" ); return; }



		// 指定のサウンドを再生
		m_SoundSourceMap.at( pcSoundName )->Play( bIsLoop );
	}
	// 指定のサウンドが無い場合
	else 
	{
		// コンテナ内の全てのサウンドを再生
		std::for_each( 
			m_SoundSourceMap.begin(), 
			m_SoundSourceMap.end(), 
			[&] ( std::pair<std::string, OALSoundSource*> pair ) { pair.second->Play( bIsLoop ); }
		);
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドの一時停止
//
// @param [in] / const char* pcSoundName	: マップコンテナにある要素を指定するキーとなるサウンド名
//
// @note : 
//
// ( 指定の )サウンドを一時停止する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Pause( const char* pcSoundName ) 
{
	// 指定のサウンドが有る場合
	if ( POINTER_CHECK( pcSoundName ) ) 
	{
		// コンテナに指定の要素が無ければ処理しない
		if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "指定のサウンドがありません。" ); return; }



		// 指定のサウンドを一時停止
		m_SoundSourceMap.at( pcSoundName )->Pause();
	}
	// 指定のサウンドが無い場合
	else 
	{
		// コンテナ内の全てのサウンドを一時停止
		std::for_each( 
			m_SoundSourceMap.begin(), 
			m_SoundSourceMap.end(), 
			[&] ( std::pair<std::string, OALSoundSource*> pair ) { pair.second->Pause(); }
		);
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドの停止
//
// @param [in] / const char* pcSoundName	: マップコンテナにある要素を指定するキーとなるサウンド名
//
// @note : 
//
// ( 指定の )サウンドを停止する。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Stop( const char* pcSoundName ) 
{
	// 指定のサウンドが有る場合
	if ( POINTER_CHECK( pcSoundName ) ) 
	{
		// コンテナに指定の要素が無ければ処理しない
		if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "指定のサウンドがありません。" ); return; }



		// 指定のサウンドを停止
		m_SoundSourceMap.at( pcSoundName )->Stop();
	}
	// 指定のサウンドが無い場合
	else 
	{
		// コンテナ内の全てのサウンドを停止
		std::for_each( 
			m_SoundSourceMap.begin(), 
			m_SoundSourceMap.end(), 
			[&] ( std::pair<std::string, OALSoundSource*> pair ) { pair.second->Stop(); }
		);
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 音量の設定
//
// @param [in] / const float fVolume : 設定する音量( 範囲は0.0～1.0 )
//
// @note : 
//
// サウンドソース全体の音量を設定する。
// 各サウンドソースの音量の変更も行う。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::SetVolume( const float fVolume ) 
{
	// 音量を設定
	if ( 0.0f > fVolume )		{ m_fVolume = 0.0f; }
	else if ( 1.0f < fVolume )	{ m_fVolume = 1.0f; }
	else						{ m_fVolume = fVolume; }



	// 各サウンドソースの音量に全体の音量を反映する
	std::for_each( 
		m_SoundSourceMap.begin(), 
		m_SoundSourceMap.end(), 
		[&] ( std::pair<std::string, OALSoundSource*> pair ) 
		{ 
			pair.second->ChangeVolume( m_fVolume * pair.second->GetVolume() ); 
		}
	);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 音量の設定
//
// @param [in] / const char* pcSoundName	: マップコンテナにある要素を指定するキーとなるサウンド名
// @param [in] / const float fVolume		: 設定する音量( 範囲は0.0～1.0 )
//
// @note : 
//
// 指定のサウンドソースの音量を設定する。
// 指定のサウンドソースの音量の変更も行う。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::SetVolume( const char* pcSoundName, const float fVolume ) 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( pcSoundName );



	// コンテナに指定の要素が無ければ処理しない
	if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "指定のサウンドがありません。" ); return; }

	

	// 指定のサウンドソースの音量を設定
	m_SoundSourceMap.at( pcSoundName )->SetVolume( fVolume );

	// 指定のサウンドソースの音量を変更
	m_SoundSourceMap.at( pcSoundName )->ChangeVolume( m_fVolume * m_SoundSourceMap.at( pcSoundName )->GetVolume() );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ピッチの設定
//
// @param [in] / const float fPitch : 設定するピッチ( 0.0以上 )
//
// @note : 
//
// サウンドソース全体のピッチを設定する。
// 各サウンドソースのピッチの変更も行う。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::SetPitch( const float fPitch ) 
{
	// ピッチを設定
	if ( 0.0f > fPitch )	{ m_fPitch = 0.0f; }
	else					{ m_fPitch = fPitch; }



	// 各サウンドソースのピッチに全体のピッチを反映する
	std::for_each( 
		m_SoundSourceMap.begin(), 
		m_SoundSourceMap.end(), 
		[&] ( std::pair<std::string, OALSoundSource*> pair ) 
		{ 
			pair.second->ChangePitch( m_fPitch * pair.second->GetPitch() ); 
		}
	);
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ピッチの設定
//
// @param [in] / const char* pcSoundName	: マップコンテナにある要素を指定するキーとなるサウンド名
// @param [in] / const float fPitch			: 設定するピッチ( 0.0以上 )
//
// @note : 
//
// 指定のサウンドソースのピッチを設定する。
// 指定のサウンドソースのピッチの変更も行う。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::SetPitch( const char* pcSoundName, const float fPitch ) 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( pcSoundName );



	// コンテナに指定の要素が無ければ処理しない
	if ( m_SoundSourceMap.count( pcSoundName ) <= 0 ) { HALT( "指定のサウンドがありません。" ); return; }

	

	// 指定のサウンドソースのピッチを設定
	m_SoundSourceMap.at( pcSoundName )->SetPitch( fPitch );

	// 指定のサウンドソースのピッチを変更
	m_SoundSourceMap.at( pcSoundName )->ChangePitch( m_fPitch * m_SoundSourceMap.at( pcSoundName )->GetPitch() );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : サウンドのクリア
//
// @note : 
//
// コンテナ内のサウンドをクリアする。
//----------------------------------------------------------------------------------------------------------------------------------
void OALSoundSourceManager::Clear() 
{
	std::for_each( 
		m_SoundSourceMap.begin(), 
		m_SoundSourceMap.end(), 
		[&] ( std::pair<std::string, OALSoundSource*> pair ) { SAFE_DELETE( pair.second ); }
	);

	m_SoundSourceMap.clear();
}