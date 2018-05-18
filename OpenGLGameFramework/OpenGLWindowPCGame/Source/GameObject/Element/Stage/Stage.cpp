//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_STAGE_H_
#include "Stage.h"
#endif	// #ifndef _INCLUDE_GUARD_STAGE_H_

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
Stage::Stage()
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Stage::~Stage() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 初期化処理
//
// @note : 
//
// 初期化処理を行う。
// シーンの初期化処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void Stage::Initialize() 
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
void Stage::Update() 
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
void Stage::Draw()
{
	const int iLineWidth			= 1;
	const int iVerticalLineCount	= 71;
	const int iHorizontalLineCount	= 71;


	
	glColor3f( 1.0, 1.0, 1.0 );

	DrawStageVerticalLines( iLineWidth, iVerticalLineCount );

	DrawStageHorizontalLines( iLineWidth, iHorizontalLineCount );
}



void Stage::DrawStageVerticalLines( const float fLineWidth, const unsigned int uiLineCount ) const 
{
	const int iHalfLineCount = static_cast<int>( uiLineCount ) / 2;

	for ( int i = 0; i < static_cast<int>( uiLineCount ); i++ ) 
	{
		float fPositionX = i - iHalfLineCount;

		NS_Graphic::NS_Graphic3D::DrawLine(
			fLineWidth,
			Vector3DF( fPositionX, 0, -iHalfLineCount ),
			Vector3DF( fPositionX, 0,  iHalfLineCount )
		);
	}
}



void Stage::DrawStageHorizontalLines( const float fLineWidth, const unsigned int uiLineCount ) const 
{
	const int iHalfLineCount = static_cast<int>( uiLineCount ) / 2;

	for ( int i = 0; i < static_cast<int>( uiLineCount ); i++ ) 
	{
		float fPositionZ = i - iHalfLineCount;

		NS_Graphic::NS_Graphic3D::DrawLine(
			fLineWidth,
			Vector3DF( -iHalfLineCount, 0, fPositionZ ),
			Vector3DF(  iHalfLineCount, 0, fPositionZ )
		);
	}
}