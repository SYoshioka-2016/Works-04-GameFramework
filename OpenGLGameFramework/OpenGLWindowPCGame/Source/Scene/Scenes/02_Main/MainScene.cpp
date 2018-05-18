//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MAINSCENE_H_
#include "MainScene.h"
#endif	// #ifndef _INCLUDE_GUARD_MAINSCENE_H_

#ifndef _INCLUDE_GUARD_GAMEOVER_H_
#include "../03_GameOver/GameOver.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOVER_H_

#ifndef _INCLUDE_GUARD_CHASECAMERA_H_
#include "../../../Camera/Advanced/ChaseCamera/ChaseCamera.h"
#endif	// #ifndef _INCLUDE_GUARD_CHASECAMERA_H_

#ifndef _INCLUDE_GUARD_PLAYER_H_
#include "../../../GameObject/Element/Player/Player.h"
#endif	// #ifndef _INCLUDE_GUARD_PLAYER_H_

#ifndef _INCLUDE_GUARD_TARGET_H_
#include "../../../GameObject/Element/Target/Target.h"
#endif	// #ifndef _INCLUDE_GUARD_TARGET_H_

#ifndef _INCLUDE_GUARD_STAGE_H_
#include "../../../GameObject/Element/Stage/Stage.h"
#endif	// #ifndef _INCLUDE_GUARD_STAGE_H_

#ifndef _INCLUDE_GUARD_GAMETEXT_H_
#include "../../../GameObject/Element/GameText/GameText.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMETEXT_H_

#ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_
#include <WindowsAPIInputLib.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_

#ifndef _INCLUDE_GUARD_OPENALSOUNDLIB_H_
#include <OpenALSoundLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENALSOUNDLIB_H_

#ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_
#include <OpenGLResourceLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_



//==================================================================================================================================
// usingディレクティブ
//==================================================================================================================================

// ゲーム名前空間
using namespace NS_OpenGLWindowPCGame;



//==================================================================================================================================
// 関数定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
MainScene::MainScene() :
	m_pChaseCamera( nullptr ),
	m_pStage( nullptr ),
	m_uiPlayerModelResourceID( ERROR_RESOURCE_ID ),
	m_uiBulletModelResourceID( ERROR_RESOURCE_ID ),
	m_strBGMName( "MainBGM" ),
	m_strSEShotName( "ShotSE" ),
	m_strSEHitName( "HitSE" )
{ 
	VIEWPORT_DESC viewportDesc;
	glGetIntegerv( GL_VIEWPORT, (GLint*)&viewportDesc );

	CAMERA_DESC cameraDesc(
		45.0f,
		( (GLfloat)viewportDesc.width / viewportDesc.height ),
		0.1f,
		10000.0f,
		1,
		false,
		Color4F( 0, 0, 0, 1 ),
//		Color4F( 1, 1, 1, 1 ),
		viewportDesc,
		Vector3DF( 0, 5, 5 ), 
		Vector3DF( 0, 0, 0 ), 
		Vector3DF( 0, 1, 0 )
	);

	CHASE_CAMERA_DESC chaseCameraDesc;
	chaseCameraDesc.distance = 5;
	chaseCameraDesc.verticalAngle = 0;
//	chaseCameraDesc.offset = Vector3DF( 0, 1, 0 );
	
	m_pChaseCamera = new ChaseCamera( cameraDesc, chaseCameraDesc );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
MainScene::~MainScene() 
{
	// 終了処理
	Finish();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 初期化処理
//
// @note : 
//
// 初期化に関する処理はここで行う。
// シーン開始後のシーン切り替え時に1回行なわれる。
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::Initialize() 
{ 
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );



	// ゲームオブジェクトクラスを生成

	// プレイヤー
	Player* pPlayer	= 
		new Player( 
			m_pChaseCamera, 
			NS_Resource::NS_Model::GetModel( m_uiPlayerModelResourceID ),
			NS_Resource::NS_Model::GetModel( m_uiBulletModelResourceID ),
			m_pGameObjectManager,
			m_strSEShotName,
			m_strSEHitName
		);

	// 的
	for ( int i = 0; i < 7; i++ ) 
	{
		Target* pTarget	= new Target();

		float fScaleSize = Random::RandomFloat( 1, 3 );

		pTarget->Initialize( 
			40, 
			Vector3DF( Random::RandomFloat( -20, 20 ), Random::RandomFloat( 0, 10 ), Random::RandomFloat( -20, 20 ) ), 
			Vector3DF( 0, 0, 0 ), 
//			Vector3DF( Random::RandomFloat( -180, 180 ), Random::RandomFloat( -180, 180 ), Random::RandomFloat( -180, 180 ) ), 
//			Vector3DF( 1, 1, 1 )
			Vector3DF( fScaleSize, fScaleSize, fScaleSize )
		);

		m_pGameObjectManager->AddGameObject( pTarget );
	}

	// ステージ
	m_pStage	= new Stage();

	// ゲームテキスト
	m_pGameText	= new GameText();



	// ゲームオブジェクトクラスの初期化処理

	// プレイヤー
	pPlayer->Initialize( 
		10, 
		Vector3DF( 0, 2, 30 ), 
		Vector3DF( 0, 180, 0 ), 
		Vector3DF( 0.002f, 0.002f, 0.002f ),
		Vector3DF( 10, 60, 60 )
	);

	// ステージ
	m_pStage->Initialize();



	// ゲームオブジェクトを追加

	// プレイヤー
	m_pGameObjectManager->AddGameObject( pPlayer );




	// BGMの再生
	NS_Sound::Play( m_strBGMName, true );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 更新処理
//
// @note : 
//
// 更新に関する処理はここで行う。
// シーンが継続している間、描画処理の前に繰り返し行なわれる。
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::Update() 
{ 
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );
	ASSERT_POINTER_CHECK( m_pStage );
	ASSERT_POINTER_CHECK( m_pGameText );
	

/*
	if ( NS_Input::NS_Keyboard::GetKeyDown( 'Z' ) ) 
	{
		m_bSceneEndFlg = true;

		// BGMの停止
		NS_Sound::Stop( m_strBGMName );
	}
*/	

glDisable( GL_LIGHTING );

	// ゲームオブジェクトクラスの更新処理
	m_pGameObjectManager->Update();

	// ステージ
	m_pStage->Update();

	// ゲームテキスト
	m_pGameText->Update();



	// カメラの更新処理
	m_pChaseCamera->Update();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 描画処理
//
// @note : 
//
// 描画に関する処理はここで行う。
// シーンが継続している間、更新処理の後に繰り返し行なわれる。
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::Draw() 
{ 
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );
	ASSERT_POINTER_CHECK( m_pStage );
	ASSERT_POINTER_CHECK( m_pGameText );



	glPushAttrib( GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT );

	glEnable( GL_DEPTH_TEST );
	
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );


	

	// ゲームテキストの描画
	m_pGameText->Draw();


	



	m_pChaseCamera->Start();
	

	


	
	


	
	m_pGameObjectManager->Draw();

	m_pStage->Draw();



	m_pChaseCamera->End();



	glPopAttrib();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 終了処理
//
// @note : 
//
// 終了に関する処理はここで行う。
// シーン終了後のシーン切り替え時に1回行なわれる。
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::Finish() 
{ 
	// ゲームオブジェクトクラスを破棄
	
	// 追跡カメラ
	SAFE_DELETE( m_pChaseCamera );
	
	// ステージ
	SAFE_DELETE( m_pStage );
	
	// ゲームテキスト
	SAFE_DELETE( m_pGameText );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 次に遷移するシーンの生成
//
// @note : 
//
// 次に遷移するシーンを生成する。
// シーン切り替え時等の必要なタイミングで呼び出すように注意する。
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::CreateNextScene() 
{
	if ( !POINTER_CHECK( m_pNextScene ) ) 
	{
		m_pNextScene = new GameOver;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンテンツロード
//
// @note : 
//
// コンテンツの読み込み処理はここで行う。
// シーン開始後のシーン切り替え時に1回行なわれる。
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::LoadContent() 
{ 
	// プレイヤーモデルの読み込み

	m_uiPlayerModelResourceID = NS_Resource::NS_Model::LoadModel( "Resource/Graphic/Model/Low Poly Starship-SS01/AF-SS01.obj" );

	if ( m_uiPlayerModelResourceID == ERROR_RESOURCE_ID ) 
	{
		HALT( "リソースの読み込みに失敗しました。" );
	}
	
	
	// 弾モデルの読み込み

	m_uiBulletModelResourceID = NS_Resource::NS_Model::LoadModel( "Resource/Graphic/Model/Missile/missile.obj" );

	if ( m_uiBulletModelResourceID == ERROR_RESOURCE_ID ) 
	{
		HALT( "リソースの読み込みに失敗しました。" );
	}



	// BGMの読み込み
	NS_Sound::Load( "Resource/Sound/BGM/Example2.wav", m_strBGMName );

	// 発射のSEの読み込み
	NS_Sound::Load( "Resource/Sound/SE/se_shot.wav", m_strSEShotName );

	// 弾の衝突のSEの読み込み
	NS_Sound::Load( "Resource/Sound/SE/se_hit.wav", m_strSEHitName );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : コンテンツアンロード
//
// @note : 
//
// コンテンツの解放処理はここで行う。
// シーン終了後のシーン切り替え時に1回行なわれる。
//----------------------------------------------------------------------------------------------------------------------------------
void MainScene::UnloadContent() 
{
	NS_Resource::ClearResource();
}