#ifndef _INCLUDE_GUARD_CAMERADESC_H_
#define _INCLUDE_GUARD_CAMERADESC_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_VIEWPORTDESC_H_
#include "ViewportDesc.h"
#endif	// #ifndef _INCLUDE_GUARD_VIEWPORTDESC_H_



//==================================================================================================================================
// 名前空間
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ゲーム名前空間
//
// @note : 
//
// ゲームアプリケーション関連の関数やクラスを管理する名前空間。
// ゲームを構成するクラスは全てこの名前空間に置くようにする。
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_OpenGLWindowPCGame
{



//==================================================================================================================================
// 構造体定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : カメラ記述子
//
// @note : 
//
// カメラの情報を管理する構造体。
//----------------------------------------------------------------------------------------------------------------------------------
struct CAMERA_DESC
{
	// 視野角
	float			fieldOfView;

	// アスペクト比
	float			aspect;

	// Near面
	float			zNear;

	// Far面
	float			zFar;

	// 平行投影グラフィックの表示領域のサイズ
	float			orthoSize;

	// 平行投影モードか?( true : 平行投影モード | false : 透視投影モード )
	bool			isOrthoGraphic;

	// クリアカラー
	Color4F			clearColor;

	// ビューポート記述子
	VIEWPORT_DESC	viewport;

	// 視点
	Vector3DF		eye;

	// 注視点
	Vector3DF		lookAt;

	// カメラの上ベクトル
	Vector3DF		up;



	// コンストラクタ
	CAMERA_DESC() :
		CAMERA_DESC( 
		0, 
		0, 
		0, 
		0, 
		0, 
		false, 
		Color4F(), 
		VIEWPORT_DESC(),
		Vector3DF( 0, 0, 0 ),
		Vector3DF( 0, 0,-1 ),
		Vector3DF( 0, 1, 0 ) 
	) 
	{ }

	// コンストラクタ
	CAMERA_DESC(
		const float				fFieldOfView,
		const float				fAspect,
		const float				fZNear,
		const float				fZFar,
		const float				fOrthoSize,
		const bool				bIsOrthoGraphic,
		const Color4F&			clearColor4,
		const VIEWPORT_DESC&	viewportDesc,
		const Vector3DF&		vec3Eye,
		const Vector3DF&		vec3LookAt,
		const Vector3DF&		vec3Up
	) :
		fieldOfView( fFieldOfView ),
		aspect( fAspect ),
		zNear( fZNear ),
		zFar( fZFar ),
		orthoSize( fOrthoSize ),
		isOrthoGraphic( bIsOrthoGraphic ),
		clearColor( clearColor4 ),
		viewport( viewportDesc ),
		eye( vec3Eye ),
		lookAt( vec3LookAt ),
		up( vec3Up )
	{ }
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_CAMERADESC_H_