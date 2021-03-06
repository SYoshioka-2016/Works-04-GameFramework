//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_GAMETEXT_H_
#include "GameText.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMETEXT_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_

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
GameText::GameText()
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
GameText::~GameText() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 更新処理
//
// @note : 
//
// 更新処理を行う。
// シーンの更新処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameText::Update() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 描画処理
//
// @note : 
//
// 描画処理を行う。
// シーンの描画処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameText::Draw()
{
	// ライティングを無効にする
	glDisable( GL_LIGHTING );



	glPushMatrix();

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();



	std::string strData[] =
	{
		"Action      | Keyboard", 
		"----------------------------",
		"Turn  Left  | Arrow Left  Key",
		"Turn  Right | Arrow Right Key",
		"Pitch Up    | Arrow Down  Key",
		"Pitch Down  | Arrow Up    Key",
		"Shoot       | Space       Key",
		"",
		"Exit : Escape Key",
	};

	Vector2DF vec2ShowPos( -1,  0.95 );

	// 文字列を表示
	for ( int i = 0; i < ARRAYSIZE( strData ); i++ )
	{
		DrawText2D( vec2ShowPos, strData[i] );
		
		vec2ShowPos.y -= .05; 
	}

	glPopMatrix();
}



void GameText::DrawText2D( const Vector2DF& vec2ShowPosition, const std::string& strShowText ) const
{
	// 表示する座標
	glRasterPos2f( vec2ShowPosition.x, vec2ShowPosition.y );

	// 文字列を表示
	for ( int i = 0; i < static_cast<int>( strShowText.size() ); i++ )
	{
		glutBitmapCharacter( GLUT_BITMAP_9_BY_15, strShowText.at( i ) );
	}
}