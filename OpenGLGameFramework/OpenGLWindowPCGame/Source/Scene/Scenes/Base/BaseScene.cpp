//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_BASESCENE_H_
#include "BaseScene.h"
#endif	// #ifndef _INCLUDE_GUARD_BASESCENE_H_

#ifndef _INCLUDE_GUARD_GAME_H_
#include "../../../Application/Game/Game.h"
#endif	// #ifndef _INCLUDE_GUARD_GAME_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



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
BaseScene::BaseScene() :
	m_bSceneEndFlg( false ),
	m_pNextScene( nullptr ),
	m_pGameObjectManager( new GameObjectManager )
{ 
	// カメラを生成する

	// ビューポートを設定
	VIEWPORT_DESC viewportDesc;
	glGetIntegerv( GL_VIEWPORT, (GLint*)&viewportDesc );

	// カメラ記述子を設定
	CAMERA_DESC desc(
		45.0f,
		( (GLfloat)viewportDesc.width / viewportDesc.height ),
		0.1f,
		100.0f,
		1,
		false,
		Color4F( 0, 0, 0, 1 ),
		viewportDesc,
		Vector3DF( 0, 5, 5 ), 
		Vector3DF( 0, 0, 0 ), 
		Vector3DF( 0, 1, 0 )
	);

	// カメラを生成
	m_pCamera = new Camera( desc );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
BaseScene::~BaseScene() 
{
	SAFE_DELETE( m_pGameObjectManager );
	SAFE_DELETE( m_pCamera );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : シーン終了か?
//
// @return / bool : シーン終了か?( true : 終了 | false : 継続 )
//	
// @note : 
//
// シーンが終了したか判定して、その情報を返す。
//----------------------------------------------------------------------------------------------------------------------------------
bool BaseScene::isEndScene() const { return m_bSceneEndFlg; }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 次に遷移するシーンの取得
//
// @return / BaseScene* : 次に遷移するシーン
//	
// @note : 
//
// 次に遷移するシーンを取得する。
// ここでシーンの生成も行われる為、頻繁に呼ばれないように注意する。
//----------------------------------------------------------------------------------------------------------------------------------
BaseScene* BaseScene::GetNextScene() 
{ 
	// 次に遷移するシーンの生成
	if ( !POINTER_CHECK( m_pNextScene ) ) { CreateNextScene(); }

	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pNextScene );



	return m_pNextScene; 
}