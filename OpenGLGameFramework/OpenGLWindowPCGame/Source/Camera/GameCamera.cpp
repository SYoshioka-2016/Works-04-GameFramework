//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_GAMECAMERA_H_
#include "GameCamera.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMECAMERA_H_

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
// @param [in] / const float fViewingAngle	: 視野角
// @param [in] / const float fAspect		: アスペクト比
// @param [in] / const float fNear			: Near面
// @param [in] / const float fFar			: Far面
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
GameCamera::GameCamera( 
		const float fViewingAngle, 
		const float fAspect,
		const float fNear, 
		const float fFar
) : 
	m_fDistance( 0 ),
	m_fVerticalAngle( 0 ),
	m_fHorizontalAngle( 0 ),
	m_fRollAngle( 0 ),
	m_pvec3LookTarget( nullptr )
{ 
/*
	// カメラの視野角を設定
	SetViewingAngle( fViewingAngle );

	// カメラのアスペクト比を設定
	m_fAspect = fAspect;

	// カメラのクリップ面を設定
	SetClippingPlane( 0.1f, 100.0f );
*/
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
GameCamera::~GameCamera() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 垂直方向回り込みトラック処理
//
// @param [in] / float fVerticalAngle	: カメラの垂直方向回転角
// @param [in] / float fDeltaAngle		: 1フレームの回転角
//
// @note : 
//
// カメラの垂直方向回転角を指定の数値になるまで変化させる。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackVerticalToward( float fVerticalAngle, float fDeltaAngle ) 
{
	// 指定の垂直方向回転角と現在の垂直方向回転角が一致したら処理しない
	if ( m_fVerticalAngle == fVerticalAngle ) { return; }



	// 1フレームの回転角を調整
	fDeltaAngle = abs( fDeltaAngle );
	fDeltaAngle *= ( m_fVerticalAngle > fVerticalAngle ) ? -1 : 1;

	// 現在の垂直方向回転角に1フレームの回転角を加算する
	m_fVerticalAngle += fDeltaAngle;

	// 指定の垂直方向回転角と現在の垂直方向回転角の差が小さくなったら回転終了
	if ( abs( m_fVerticalAngle - fVerticalAngle ) < fDeltaAngle ) {
	
		// 現在の垂直方向回転角に指定の垂直方向回転角を設定する
		m_fVerticalAngle = fVerticalAngle;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 水平方向回り込みトラック処理
//
// @param [in] / float fHorizontalAngle	: カメラの水平方向回転角
// @param [in] / float fDeltaAngle		: 1フレームの回転角
//
// @note : 
//
// カメラの水平方向回転角を指定の数値になるまで変化させる。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackHorizontalToward( float fHorizontalAngle, float fDeltaAngle ) 
{
//fHorizontalAngle *= -1;

	// 指定の水平方向回転角と現在の水平方向回転角が一致したら処理しない
	if ( m_fHorizontalAngle == fHorizontalAngle ) { return; }



	// 1フレームの回転角を調整
	fDeltaAngle = abs( fDeltaAngle );
	fDeltaAngle *= ( m_fHorizontalAngle > fHorizontalAngle ) ? -1 : 1;

	// 現在の水平方向回転角に1フレームの回転角を加算する
	m_fHorizontalAngle += fDeltaAngle;

	// 指定の水平方向回転角と現在の水平方向回転角の差が小さくなったら回転終了
	if ( abs( m_fHorizontalAngle - fHorizontalAngle ) < fDeltaAngle ) {
	
		// 現在の水平方向回転角に指定の水平方向回転角を設定する
		m_fHorizontalAngle = fHorizontalAngle;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 上回り込みトラック処理
//
// @param [in] / float fDeltaAngle : 1フレームの回転角
//
// @note : 
//
// カメラの垂直方向回転角を加算する。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackUpToward( float fDeltaAngle ) 
{
	// 現在の垂直方向回転角に1フレームの回転角を加算する
	m_fVerticalAngle += abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 下回り込みトラック処理
//
// @param [in] / float fDeltaAngle : 1フレームの回転角
//
// @note : 
//
// カメラの垂直方向回転角を減算する。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackDownToward( float fDeltaAngle ) 
{
	// 現在の垂直方向回転角に1フレームの回転角を減算する
	m_fVerticalAngle -= abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 右回り込みトラック処理
//
// @param [in] / float fDeltaAngle : 1フレームの回転角
//
// @note : 
//
// カメラの水平方向回転角を減算する。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackRightToward( float fDeltaAngle ) 
{
	// 現在の水平方向回転角に1フレームの回転角を減算する
	m_fHorizontalAngle -= abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 左回り込みトラック処理
//
// @param [in] / float fDeltaAngle : 1フレームの回転角
//
// @note : 
//
// カメラの水平方向回転角を加算する。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackLeftToward( float fDeltaAngle ) 
{
	// 現在の水平方向回転角に1フレームの回転角を加算する
	m_fHorizontalAngle += abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ズーム処理
//
// @param [in] / float fViewingAngle	: 視野角
// @param [in] / float fDeltaAngle		: 1フレームの視野角の変化量の大きさ
//
// @note : 
//
// カメラの視野角を指定の数値になるまで変化させる。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::ZoomToward( float fViewingAngle, float fDeltaAngle ) 
{
/*
	// 指定の視野角と現在の視野角が一致したら処理しない
	if ( m_fViewingAngle == fViewingAngle ) { return; }



	// 1フレームの視野角の変化量の大きさを調整
	fDeltaAngle = abs( fDeltaAngle );
	fDeltaAngle *= ( m_fViewingAngle > fViewingAngle ) ? -1 : 1;

	// 現在の視野角に1フレームの視野角の変化量の大きさを加算する
	m_fViewingAngle += fDeltaAngle;

	// 指定の視野角と現在の視野角の差が小さくなったら終了
	if ( abs( m_fViewingAngle - fViewingAngle ) < fDeltaAngle ) {
	
		// 現在の視野角に指定の視野角を設定する
		m_fViewingAngle = fViewingAngle;
	}
*/
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ズームイン処理
//
// @param [in] / float fDeltaAngle : 1フレームの視野角の変化量の大きさ
//
// @note : 
//
// カメラの視野角を狭くする。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::ZoomInToward( float fDeltaAngle ) 
{
	// 現在の視野角に1フレームの視野角の変化量の大きさを減算する
//	m_fViewingAngle -= abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ズームアウト処理
//
// @param [in] / float fDeltaAngle : 1フレームの視野角の変化量の大きさ
//
// @note : 
//
// カメラの視野角を広くする。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::ZoomOutToward( float fDeltaAngle ) 
{
	// 現在の視野角に1フレームの視野角の変化量の大きさを加算する
//	m_fViewingAngle += abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ズーム処理
//
// @param [in] / float fZoomInViewingAngle	: ズームインの視野角
// @param [in] / float fZoomOutViewingAngle	: ズームアウトの視野角
// @param [in] / float fDeltaAngle			: 1フレームの視野角の変化量の大きさ
//
// @note : 
//
// カメラの視野角を指定の数値になるまで変化させる。
// 追跡対象の移動方向とカメラの前方向によってズームを切り替える。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::ZoomToward( 
	float fZoomInViewingAngle, 
	float fZoomOutViewingAngle, 
	float fDeltaAngle 
) 
{
	// 注視ターゲットの位置が無ければ処理しない
	if ( NULL_CHECK( m_pvec3LookTarget ) ) { return; }



	// ターゲットの移動方向ベクトル
	Vector3DF vec3TargetMoveDirection = GetTergetMoveDirection();
	if ( vec3TargetMoveDirection.Length() <= 0 ) { return; }

	// カメラの前方向ベクトル
	Vector3DF vec3CameraForwardDirection = GetCameraForward();
	if ( vec3CameraForwardDirection.Length() <= 0 ) { return; }



	// ターゲットの移動方向ベクトルとカメラの前方向ベクトルの内積
	float fDot = Vector3DF::Dot( vec3TargetMoveDirection, vec3CameraForwardDirection );



	// 視野角の最小値を調整
	fZoomInViewingAngle = (float)Clamp( fZoomInViewingAngle, fZoomInViewingAngle, fZoomOutViewingAngle );



	// 内積の値によって視野角を設定する
	float fZoomViewingAngle = ( ( 0 <= fDot ) && ( 1 >= fDot ) ) ? fZoomOutViewingAngle : fZoomInViewingAngle;

	// ズームする
	ZoomToward( fZoomViewingAngle, fDeltaAngle * fDot );



	// 注視ターゲットの位置を保存
	m_vec3PrevLookTarget = *m_pvec3LookTarget;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ロール回転処理
//
// @param [in] / const float fRollAngle		: ロール回転角
// @param [in] / float		 fDeltaAngle	: 1フレームの回転角
//
// @note : 
//
// カメラのロール回転角を指定の数値になるまで変化させる。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::RollToward( const float fRollAngle, float fDeltaAngle ) 
{
	// 指定のロール回転角と現在のロール回転角が一致したら処理しない
	if ( m_fRollAngle == fRollAngle ) { return; }



	// 1フレームの回転角を調整
	fDeltaAngle *= ( m_fRollAngle > fRollAngle ) ? -1 : 1;

	// 現在のロール回転角に1フレームの回転角を加算する
	m_fRollAngle += fDeltaAngle;

	// 指定のロール回転角と現在のロール回転角の差が小さくなったら回転終了
	if ( abs( m_fRollAngle - fRollAngle ) < fDeltaAngle ) {
	
		// 現在のロール回転角に指定のロール回転角を設定する
		m_fRollAngle = fRollAngle;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 右ロール回転処理
//
// @param [in] / float fDeltaAngle : 1フレームの回転角
//
// @note : 
//
// カメラのロール回転角を加算する。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::RollRightToward( float fDeltaAngle ) 
{
	// 現在のロール回転角に1フレームの回転角を加算する
	m_fRollAngle += abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 左ロール回転処理
//
// @param [in] / float fDeltaAngle : 1フレームの回転角
//
// @note : 
//
// カメラのロール回転角を減算する。
// 更新処理の中で呼ぶようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::RollLeftToward( float fDeltaAngle )
{
	// 現在のロール回転角に1フレームの回転角を減算する
	m_fRollAngle -= abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 垂直方向回転角の取得
//
// @return / float : 垂直方向回転角
//	
// @note : 
//
// 垂直方向回転角を返す。
//----------------------------------------------------------------------------------------------------------------------------------
float GameCamera::GetVerticalAngle() const { return m_fVerticalAngle; }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 水平方向回転角の取得
//
// @return / float : 水平方向回転角
//	
// @note : 
//
// 水平方向回転角を返す。
//----------------------------------------------------------------------------------------------------------------------------------
float GameCamera::GetHorizontalAngle() const { return m_fHorizontalAngle; }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 移動ベクトルの取得
//
// @return / Vector3DF : 移動ベクトル
//	
// @note : 
//
// 移動ベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF GameCamera::GetMoveVector() const { return GetEye() - m_vec3PrevPosition; }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 垂直方向回転角の設定
//
// @param [in] / const float fVerticalAngle	: 垂直方向の回転角
//	
// @note : 
//
// カメラの垂直方向回転角を設定する。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::SetVerticalAngle( const float fVerticalAngle ) 
{ 
	m_fVerticalAngle = fVerticalAngle; 
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 水平方向回転角の設定
//
// @param [in] / const float fVerticalAngle	: 水平方向の回転角
//	
// @note : 
//
// カメラの水平方向回転角を設定する。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::SetHorizontalAngle( const float fHorizontalAngle ) 
{ 
	m_fHorizontalAngle = fHorizontalAngle; 
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 追跡対象の設定
//
// @param [in] / Vector3DF*		pvec3LookTarget				: 注視するターゲットの位置
// @param [in] / const float	fDistance					: 注視点から視点までの距離
//	
// @note : 
//
// 注視するターゲットの位置、追跡対象との距離を設定する。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::SetChaseTarget( 
	Vector3DF*		pvec3LookTarget, 
	const float		fDistance
)
{
	// 注視するターゲットの位置が無ければ処理しない
	if ( NULL_CHECK( pvec3LookTarget ) ) { return; }



	// 注視するターゲットの位置を設定
	m_pvec3LookTarget	= pvec3LookTarget;

	// ターゲットとカメラの距離を設定
	m_fDistance			= fDistance;



	// ターゲットの座標を保存する
	m_vec3PrevLookTarget = *m_pvec3LookTarget;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 更新処理
//
// @note : 
//
//
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::update() 
{
	// 視点を保存する
	m_vec3PrevPosition = GetEye();



	// カメラのセッティング
	SettingCamera();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : カメラのセッティング
//
// @note : 
//
// 視点、上ベクトル、注視点を設定する。
// 注視するターゲットの位置から後ろに指定の距離だけ移動し、
// 注視するターゲットの位置を中心に垂直、水平方向にそれぞれ指定の角度だけ回転した位置に視点を設定する。
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::SettingCamera() 
{
	// 注視するターゲットの位置が無ければ処理しない
	if ( NULL_CHECK( m_pvec3LookTarget ) ) { return; }

	
/*
	// 視点を指定の距離だけ離れて、x軸に指定の角度だけ回転した位置にする
	m_vec3Eye = Rotate( Vector3DF( 0, 0, m_fDistance ), Vector3DF( 1, 0, 0 ), m_fVerticalAngle );

	// 視点をy軸に指定の角度だけ回転した位置にする
	m_vec3Eye = Rotate( m_vec3Eye, Vector3DF( 0, 1, 0 ), m_fHorizontalAngle );
	
	

	// カメラの上ベクトルを真上からx軸に指定の角度だけ回転したベクトルにする
	m_vec3Up = Rotate( Vector3DF( 0, 1, 0 ), Vector3DF( 1, 0, 0 ), m_fVerticalAngle );
	
	// カメラの上ベクトルをy軸に指定の角度だけ回転したベクトルにする
	m_vec3Up = Rotate( m_vec3Up, Vector3DF( 0, 1, 0 ), m_fHorizontalAngle );



	// カメラをロール回転する
	RollCamera( m_fRollAngle );

	// 注視点に注視ターゲットの位置を設定する
	m_vec3LookAt = *m_pvec3LookTarget;

	// 視点の基準を原点から注視点に移動する
	m_vec3Eye += m_vec3LookAt;
	
	// 注視点の設定
	SetLookAt( m_vec3LookAt );
*/
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : カメラの前方向ベクトルの取得
//
// @return / Vector3DF : カメラの前方向ベクトル
//	
// @note : 
//
// カメラの前方向ベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF GameCamera::GetCameraForward() const
{
	// カメラの前方向ベクトル
	Vector3DF vec3CameraForwardDirection = GetLookAt() - GetEye();
	if ( vec3CameraForwardDirection.Length() <= 0 ) { return Vector3DF(); }



	// カメラの前方向ベクトルを正規化
	return vec3CameraForwardDirection.Normalized();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ターゲットの移動ベクトルの取得
//
// @return / Vector3DF : ターゲットの移動ベクトル
//	
// @note : 
//
// ターゲットの移動ベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF GameCamera::GetTergetMoveVector() const 
{
	// 注視ターゲットの位置が無ければ処理しない
	if ( NULL_CHECK( m_pvec3LookTarget ) ) { return Vector3DF(); }



	// ターゲットの移動ベクトル
	return *m_pvec3LookTarget - m_vec3PrevLookTarget;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ターゲットの移動方向ベクトルの取得
//
// @return / Vector3DF : ターゲットの移動方向ベクトル
//	
// @note : 
//
// ターゲットの移動方向ベクトルを返す。
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF GameCamera::GetTergetMoveDirection() const 
{
	// ターゲットの移動ベクトル
	Vector3DF vec3TerGetMoveVector = GetTergetMoveVector();
	if ( vec3TerGetMoveVector.Length() <= 0 ) { return Vector3DF(); }



	// ターゲットの移動ベクトルを正規化
	return vec3TerGetMoveVector.Normalized();
}