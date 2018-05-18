//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_PLAYER_H_
#include "Player.h"
#endif	// #ifndef _INCLUDE_GUARD_PLAYER_H_

#ifndef _INCLUDE_GUARD_CHASECAMERA_H_
#include "../../../Camera/Advanced/ChaseCamera/ChaseCamera.h"
#endif	// #ifndef _INCLUDE_GUARD_CHASECAMERA_H_

#ifndef _INCLUDE_GUARD_GAMEOBJECTMANAGER_H_
#include "../../../GameObject/Manager/GameObjectManager.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECTMANAGER_H_

#ifndef _INCLUDE_GUARD_BULLET_H_
#include "../../../GameObject/Element/Player/Bullet/Bullet.h"
#endif	// #ifndef _INCLUDE_GUARD_BULLET_H_

#ifndef _INCLUDE_GUARD_GAMEOBJECTNAMEDEFINES_H_
#include "../../GameObjectNameDefines.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECTNAMEDEFINES_H_

#ifndef _INCLUDE_GUARD_FPS_H_
#include "../../../Time/FPS/Fps.h"
#endif	// #ifndef _INCLUDE_GUARD_FPS_H_

#ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_
#include <WindowsAPIInputLib.h>
#endif	// #ifndef _INCLUDE_GUARD_WINDOWSAPIINPUTLIB_H_

#ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_
#include <OpenGLResourceLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_

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
// @param [in] / ChaseCamera*							pChaseCamera		: 追跡カメラ
// @param [in] / const NS_Resource::NS_Model::OGLModel* pPlayerModel		: プレイヤーのモデル
// @param [in] / const NS_Resource::NS_Model::OGLModel* pBulletModel		: 弾のモデル
// @param [in] / GameObjectManager*						pGameObjectManager	: ゲームオブジェクト管理クラス
// @param [in] / const char*							strSEShotName		: 発射のSE名
// @param [in] / const char*							strSEHitName		: 弾の衝突のSE名
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Player::Player(
	ChaseCamera*							pChaseCamera,
	const NS_Resource::NS_Model::OGLModel*	pPlayerModel,
	const NS_Resource::NS_Model::OGLModel*	pBulletModel,
	GameObjectManager*						pGameObjectManager,
	const char*								strSEShotName,
	const char*								strSEHitName
) : 
	m_pChaseCamera( pChaseCamera ),
	m_pPlayerModel( pPlayerModel ),
	m_pBulletModel( pBulletModel ),
	m_pGameObjectManager( pGameObjectManager ),
	m_strSEShotName( strSEShotName )
{ 
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pPlayerModel );
	ASSERT_POINTER_CHECK( m_pBulletModel );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );



	SetName( PLAYER_NAME );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Player::~Player() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 初期化処理
//
// @param [in] / const float		fMoveSpeed				: 移動の速さ
// @param [in] / const Vector3DF&	vec3Position			: 座標
// @param [in] / const Vector3DF&	vec3Rotation			: 回転角
// @param [in] / const Vector3DF&	vec3Scale				: スケール値
// @param [in] / const Vector3DF&	vec3RotationAngleSpeed	: 回転の速さ
//
// @note : 
//
// 初期化処理を行う。
// シーンの初期化処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void Player::Initialize(
	const float			fMoveSpeed, 
	const Vector3DF&	vec3Position,
	const Vector3DF&	vec3Rotation, 
	const Vector3DF&	vec3Scale,
	const Vector3DF&	vec3RotationAngleSpeed
) 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pPlayerModel );



	m_fMoveSpeed				= fMoveSpeed;
	m_Transform.position		= vec3Position;
	m_Transform.rotation		= vec3Rotation;
	m_Transform.scale			= vec3Scale;
	m_vec3RotationAngleSpeed	= vec3RotationAngleSpeed;

	

	m_SphereCollider.SetRadius( 1 );


	// プレイヤーをカメラの追跡対象に設定する
	m_pChaseCamera->SetTarget( &m_Transform.position );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 更新処理
//
// @note : 
//
// 更新処理を行う。
// シーンの更新処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void Player::Update() 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pChaseCamera );

printf( "%f\n", Fps::Instance()->GetFPS() );
//printf( "%f %f %f\n", m_Transform.position.x, m_Transform.position.y, m_Transform.position.z );

	// 移動処理
	Move();
	
	// 弾発射開始処理
	ShootStart();


	
	// カメラの垂直方向回転角を設定する
	m_pChaseCamera->SetVerticalAngle( m_Transform.rotation.x + 0.0f );

	// カメラの水平方向回転角を設定する
	m_pChaseCamera->SetHorizontalAngle( -m_Transform.rotation.y + 180.0f ); 
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 描画処理
//
// @note : 
//
// 描画処理を行う。
// シーンの描画処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void Player::Draw()
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pPlayerModel );



	glPushMatrix();



	glTranslatef( m_Transform.position.x, m_Transform.position.y, m_Transform.position.z );

	glRotatef( m_Transform.rotation.y, 0, 1, 0 );
	glRotatef( m_Transform.rotation.x, 1, 0, 0 );
	glRotatef( m_Transform.rotation.z, 0, 0, 1 );

	
	glColor3f( 1.0, 0.0, 0.5 );
	NS_Graphic::NS_Graphic3D::DrawLine( 1, Vector3DF( 0, 0, -50 ), Vector3DF( 0, 0, 50 ) );

	glScalef( m_Transform.scale.x, m_Transform.scale.y, m_Transform.scale.z );
	


	// モデルを描画する
	glColor3f( 0.0, 0.5, 1.0 );
	glLineWidth( 2 );
	m_pPlayerModel->SimpleDrawMesh( GL_LINE_STRIP );


	

	
	glPopMatrix();
}




void Player::OnColliding( const GameObject& gameObject ) 
{ 
//	printf( "on hitting.\n" ); 
//	printf( "%s\n", gameObject.GetName() );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 前に移動する入力があったか?
//
// @return / bool : 前に移動する入力があったか?( true : 入力あり | false : 入力なし )
//
// @note : 
//
// 前に移動する入力があったか判定して結果を返す。
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputMoveForward() const 
{
	return NS_Input::NS_Keyboard::GetKey( 'W' );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 後ろに移動する入力があったか?
//
// @return / bool : 後ろに移動する入力があったか?( true : 入力あり | false : 入力なし )
//
// @note : 
//
// 後ろに移動する入力があったか判定して結果を返す。
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputMoveBack() const
{
	return NS_Input::NS_Keyboard::GetKey( 'S' );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 右に旋回する入力があったか?
//
// @return / bool : 右に旋回する入力があったか?( true : 入力あり | false : 入力なし )
//
// @note : 
//
// 右に旋回する入力があったか判定して結果を返す。
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputYawRotationRight() const
{
	return NS_Input::NS_Keyboard::GetKey( VK_RIGHT );
}
	


//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 左に旋回する入力があったか?
//
// @return / bool : 左に旋回する入力があったか?( true : 入力あり | false : 入力なし )
//
// @note : 
//
// 左に旋回する入力があったか判定して結果を返す。
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputYawRotationLeft() const
{
	return NS_Input::NS_Keyboard::GetKey( VK_LEFT );
}
	


//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 上にピッチ回転する入力があったか?
//
// @return / bool : 上にピッチ回転する入力があったか?( true : 入力あり | false : 入力なし )
//
// @note : 
//
// 上にピッチ回転する入力があったか判定して結果を返す。
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputPitchRotationUp() const
{
	return NS_Input::NS_Keyboard::GetKey( VK_DOWN );
}
	


//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 下にピッチ回転する入力があったか?
//
// @return / bool : 下にピッチ回転する入力があったか?( true : 入力あり | false : 入力なし )
//
// @note : 
//
// 下にピッチ回転する入力があったか判定して結果を返す。
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputPitchRotationDown() const
{
	return NS_Input::NS_Keyboard::GetKey( VK_UP );
}
	

	
//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 弾を発射する入力があったか?
//
// @return / bool : 弾を発射する入力があったか?( true : 入力あり | false : 入力なし )
//
// @note : 
//
// 弾を発射する入力があったか判定して結果を返す。
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputShoot() const 
{
	return NS_Input::NS_Keyboard::GetKeyDown( VK_SPACE );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 移動処理
//
// @note : 
//
// プレイヤーの座標を更新する。
//----------------------------------------------------------------------------------------------------------------------------------
void Player::Move() 
{
/*
	// 移動方向ベクトル
	m_vec3MoveDirection = Vector3DF();

	// 前に移動
	m_vec3MoveDirection.z -= ( IsInputMoveForward() ) ? 1 : 0;
	
	// 後ろに移動	
	m_vec3MoveDirection.z += ( IsInputMoveBack() ) ? 1 : 0;

	// 移動方向ベクトルを正規化
	m_vec3MoveDirection = ( 0 < m_vec3MoveDirection.Length() ) ? m_vec3MoveDirection.Normalized() : Vector3DF();
*/
	// 移動方向ベクトル
	m_vec3MoveDirection = Vector3DF( 0, 0, -1 );



	// ピッチ回転

	// ピッチ回転角
	const float fPitchRotationAngle = abs( m_vec3RotationAngleSpeed.x ) * Fps::Instance()->GetSPF();

	// 角度を下げる
	m_Transform.rotation.x -= ( IsInputPitchRotationUp() )		? fPitchRotationAngle : 0;
	
	// 角度を上げる
	m_Transform.rotation.x += ( IsInputPitchRotationDown() )	? fPitchRotationAngle : 0;

	// 角度の上げ下げに変化がなければピッチ回転角を基準に戻す
	if ( IsInputPitchRotationUp() == IsInputPitchRotationDown() ) 
	{
		m_Transform.rotation.x += fPitchRotationAngle * ( ( 0 > m_Transform.rotation.x ) ? 1 : -1 );
		if ( abs( m_Transform.rotation.x ) <= fPitchRotationAngle ) { m_Transform.rotation.x = 0; }
	}

	// ピッチ回転角を調整する
	m_Transform.rotation.x = (float)Clamp( m_Transform.rotation.x, -30.0f, 30.0f );

	// 移動方向ベクトルをピッチ回転する
	m_vec3MoveDirection = NS_Graphic::NS_GraphicMathematics::RotateVector( m_vec3MoveDirection, Vector3DF( 1, 0, 0 ), m_Transform.rotation.x );



	// ヨー回転
		
	// ヨー回転角
	const float fYawRotationAngle = abs( m_vec3RotationAngleSpeed.y ) * Fps::Instance()->GetSPF();

	// 角度を上げる
	m_Transform.rotation.y -= ( IsInputYawRotationRight() ) ? fYawRotationAngle : 0;

	// 角度を下げる
	m_Transform.rotation.y += ( IsInputYawRotationLeft() )	? fYawRotationAngle : 0;

	// 移動方向ベクトルをヨー回転する
	m_vec3MoveDirection = NS_Graphic::NS_GraphicMathematics::RotateVector( m_vec3MoveDirection, Vector3DF( 0, 1, 0 ), -m_Transform.rotation.y - 180.0f );
//m_vec3MoveDirection *= -1;



	// ロール回転

	// ロール回転角
	const float fRollRotationAngle = abs( m_vec3RotationAngleSpeed.z ) * Fps::Instance()->GetSPF();

	// 角度を上げる
	m_Transform.rotation.z += ( IsInputYawRotationRight() )	? fRollRotationAngle : 0;

	// 角度を下げる
	m_Transform.rotation.z -= ( IsInputYawRotationLeft() )	? fRollRotationAngle : 0;

	// 角度の上げ下げに変化がなければロール回転角を基準に戻す
	if ( IsInputYawRotationRight() == IsInputYawRotationLeft() ) 
	{
		m_Transform.rotation.z += fRollRotationAngle * ( ( 0 > m_Transform.rotation.z ) ? 1 : -1 );
		if ( abs( m_Transform.rotation.z ) <= fRollRotationAngle ) { m_Transform.rotation.z = 0; }
	}

	// ロール回転角を調整する
	m_Transform.rotation.z = (float)Clamp( m_Transform.rotation.z, -30.0f, 30.0f );



	// プレイヤーの座標に移動のベクトルを加算する
	m_Transform.position += m_vec3MoveDirection * abs( m_fMoveSpeed ) * Fps::Instance()->GetSPF();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 弾発射開始処理
//
// @note : 
//
// 弾を生成し、ゲームオブジェクトとしてシーンに追加する。
//----------------------------------------------------------------------------------------------------------------------------------
void Player::ShootStart() 
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pBulletModel );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );



	// 弾を発射する入力が無ければ処理しない
	if ( !IsInputShoot() ) { return; }



	// 弾を生成する
	Bullet* pBullet = new Bullet( m_pBulletModel, m_strSEShotName, m_strSEHitName );
	
	// 弾の回転値を設定
	Vector3DF vec3Rotation = Vector3DF( 90, 180, 0 ) + Vector3DF( m_Transform.rotation.x, m_Transform.rotation.y + 180, 0 );

	// 弾の進行方向を設定
	Vector3DF vec3Forward( 0, 0, -1 );
	vec3Forward = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Forward, VECTOR3DF_RIGHT, m_Transform.rotation.x );
	vec3Forward = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Forward, VECTOR3DF_UP, -( m_Transform.rotation.y + 180 ) );

	// 弾の初期化処理
	pBullet->Initialize( 
		50, 
		m_Transform.position, 
		vec3Rotation,
		Vector3DF( 0.008f, 0.008f, 0.008f ),
		vec3Forward
	);

	// ゲームオブジェクトを追加
	m_pGameObjectManager->AddGameObject( pBullet );
}