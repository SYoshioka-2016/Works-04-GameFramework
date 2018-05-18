#ifndef _INCLUDE_GUARD_CAMERA_H_
#define _INCLUDE_GUARD_CAMERA_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_CAMERADESC_H_
#include "../Desc/CameraDesc.h"
#endif	// #ifndef _INCLUDE_GUARD_CAMERADESC_H_



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
// クラス定義
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : カメラクラス
//
// @note : 
//
// カメラを表現するクラス。
//----------------------------------------------------------------------------------------------------------------------------------
class Camera 
{
public:

	// コンストラクタ
	Camera();

	// コンストラクタ
	Camera( const CAMERA_DESC& desc );
	
	// デストラクタ
	~Camera();



	// 撮影開始
	void Start();

	// 撮影終了
	void End();

	// 透視投影モードに変更
	void ChangeToPerspectiveGraphicMode();

	// 平行投影モードに変更
	void ChangeToOrthoGraphicMode();



	// 射影変換行列の取得
	Matrix4x4F GetProjectionMatrix();
	
	// 視野変換行列の取得
	Matrix4x4F GetViewMatrix();

	// 透視投影変換行列の取得
	Matrix4x4F GetPerspectiveMatrix();
	
	// 平行投影変換行列の取得
	Matrix4x4F GetOrthoMatrix();
	
	// 視点変換行列の取得
	Matrix4x4F GetLookAtMatrix();



	// 視点の取得
	const Vector3DF& GetEye() const;

	// 視点の設定
	void SetEye( const Vector3DF& vec3Eye );

	// 注視点の取得
	Vector3DF GetLookAt() const;

	// 注視点の設定
	void SetLookAt( const Vector3DF& vec3LookAt );

	// 上ベクトルの取得
	const Vector3DF& GetUp() const;

	// 上ベクトルの設定
	void SetUp( const Vector3DF& vec3Up );



	// カメラ記述子の取得
	const CAMERA_DESC& GetCameraDesc() const;
	
	// カメラ記述子の設定
	void SetCameraDesc( const CAMERA_DESC& desc );
	
	// 視野角の設定
	void SetFieldOfView( const float fFieldOfView );
	
	// アスペクト比の設定
	void SetAspect( const float fAspect );
	
	// Near面の設定
	void SetZNear( const float fZNear );
	
	// Far面の設定
	void SetZFar( const float fZFar );
	
	// 平行投影グラフィックの表示領域のサイズの設定
	void SetOrthoSize( const float fOrthoSize );
	
	// クリアカラーの設定
	void SetClearColor( const Color4F& clearColor );
	
	// ビューポートの設定
	void SetViewport( const VIEWPORT_DESC& viewport );

protected:

	// メンバ変数

	// カメラ記述子
	CAMERA_DESC			m_Desc;

	// 撮影開始フラグ
	bool				m_bStartedFlg;

	// 退避用ビューポートバッファ
	VIEWPORT_DESC		m_ViewportBuffer;

	// 退避用プロジェクション行列バッファ
	Matrix4x4F			m_mat4ProjectionMatrixBuffer;

	// 退避用モデルビュー行列バッファ
	Matrix4x4F			m_mat4ModelViewMatrixBuffer;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_CAMERA_H_