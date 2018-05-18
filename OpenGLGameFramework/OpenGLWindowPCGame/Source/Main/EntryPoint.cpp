//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_
#include <OpenGLResourceLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_

#ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_
#include <WindowsAPIInputLib.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_

#ifndef _INCLUDE_GUARD_OPENALSOUNDLIB_H_
#include <OpenALSoundLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENALSOUNDLIB_H_

#ifndef _INCLUDE_GUARD_GAME_H_
#include "../Application/Game/Game.h"
#endif	// #ifndef _INCLUDE_GUARD_GAME_H_



//==================================================================================================================================
// グローバル変数
//==================================================================================================================================

// メインクラス
static NS_OpenGLWindowPCGame::BaseApplication* g_pGame = nullptr;



//==================================================================================================================================
// 関数プロトタイプ宣言
//==================================================================================================================================

// ディスプレイコールバック関数
void DISPLAY_CALLBACK();

// アイドルコールバック関数
void IDLE_CALLBACK();

// exit関数による終了処理
void AtExit1();



int main( int argc, char *argv[] ) 
{
	// 終了処理の関数を登録
	atexit( AtExit1 );



	// GLUTを初期化
	glutInit( &argc, argv ); 

	// ディスプレイモードを初期化
	glutInitDisplayMode( GLUT_DOUBLE );

	// ウィンドウの位置を初期化
	glutInitWindowPosition( 0, 0 );

	// ウィンドウのサイズを初期化
	glutInitWindowSize( 800, 450 );
//	glutInitWindowSize( 1280, 720 );

	// ウィンドウを生成
//	glutCreateWindow( "OpenGLGame" );
	glutCreateWindow( "Game" );



	// 描画関数のコールバック関数登録
	glutDisplayFunc( DISPLAY_CALLBACK );

	// アイドル関数のコールバック関数登録
	glutIdleFunc( IDLE_CALLBACK );



	// OpenALの初期化
//	NS_Sound::InitializeOpenAL();



	// ゲームクラスを生成
	g_pGame = new NS_OpenGLWindowPCGame::Game;

	// ゲームの初期化処理
	g_pGame->Initialize();



	// メインループ
	glutMainLoop();



	// ゲームクラスが有れば破棄する
	if ( POINTER_CHECK( g_pGame ) ) 
	{
		// 終了処理
		g_pGame->Finish();

		SAFE_DELETE( g_pGame );
	}



	return 0;
}



void DISPLAY_CALLBACK() 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( g_pGame );



	// ゲームの描画処理
	g_pGame->Display();



	// バッファをスワップ
	glutSwapBuffers();
}



void IDLE_CALLBACK() 
{
	// キーボードの入力状態の更新
	NS_Input::NS_Keyboard::UpdateKeyState();

	

	// 指定の入力が有れば終了
	if ( NS_Input::NS_Keyboard::GetKeyDown( VK_ESCAPE ) ) { exit( 0 ); return; }



	// ポインタチェック
	ASSERT_POINTER_CHECK( g_pGame );



	// ゲームの更新処理
	g_pGame->Update();



	// 描画コールバック関数を呼ぶ
	glutPostRedisplay();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : exit関数による終了処理
//
// @note : 
//
// exit関数によってプログラムが終了する際に実行する終了処理を行う。
// 事前にatexitで終了処理の関数を登録しておく事で、
// exit関数の後に終了処理を実行出来る。
//----------------------------------------------------------------------------------------------------------------------------------
void AtExit1() 
{ 
	// ゲームクラスが無ければ処理しない
	if ( !POINTER_CHECK( g_pGame ) ) { return; }

	

	// 終了処理
	g_pGame->Finish();

	SAFE_DELETE( g_pGame );
}