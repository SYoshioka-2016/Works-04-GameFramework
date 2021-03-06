//==================================================================================================================================
// インクルード
//==================================================================================================================================
#ifndef _INCLUDE_GUARD_BASEAPPLICATION_H_
#include "BaseApplication.h"
#endif	// #ifndef _INCLUDE_GUARD_BASEAPPLICATION_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_
#include <OpenGLGraphicLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLGRAPHICLIB_H_



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
BaseApplication::BaseApplication()
{ }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
BaseApplication::~BaseApplication() 
{

}


// ウィンドウの幅の取得
unsigned int BaseApplication::GetWindowWidth() 
{
	return glutGet( GLUT_WINDOW_WIDTH );
}

	// ウィンドウの高さの取得
unsigned int BaseApplication::GetWindowHeight() 
{
	return glutGet( GLUT_WINDOW_HEIGHT );
}