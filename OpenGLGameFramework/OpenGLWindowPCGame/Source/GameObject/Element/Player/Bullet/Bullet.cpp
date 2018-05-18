//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_BULLET_H_
#include "Bullet.h"
#endif	// #ifndef _INCLUDE_GUARD_BULLET_H_

#ifndef _INCLUDE_GUARD_GAMEOBJECTNAMEDEFINES_H_
#include "../../../GameObjectNameDefines.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECTNAMEDEFINES_H_

#ifndef _INCLUDE_GUARD_FPS_H_
#include "../../../../Time/FPS/Fps.h"
#endif	// #ifndef _INCLUDE_GUARD_FPS_H_

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
// @param [in] / const NS_Resource::NS_Model::OGLModel* pModel			: モデル
// @param [in] / const char*							strSEShotName	: 発射のSE名
// @param [in] / const char*							strSEHitName	: 弾の衝突のSE名
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Bullet::Bullet(
	const NS_Resource::NS_Model::OGLModel*	pModel,
	const char*								strSEShotName,
	const char*								strSEHitName
) :
	m_fMoveSpeed( 0 ),
	m_fTimer( 0 ),
	m_vec3MoveDirection( Vector3DF() ),
	m_pModel( pModel ),
	m_strSEShotName( strSEShotName ),
	m_strSEHitName( strSEHitName )
{ 
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pModel );



	SetName( BULLET_NAME );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : デストラクタ
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Bullet::~Bullet() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 初期化処理
//
// @param [in] / const float		fMoveSpeed				: 移動の速さ
// @param [in] / const Vector3DF&	vec3Position			: 座標
// @param [in] / const Vector3DF&	vec3Rotation			: 回転角
// @param [in] / const Vector3DF&	vec3Scale				: スケール値
// @param [in] / const Vector3DF&	vec3MoveDirection		: 移動方向
//
// @note : 
//
// 初期化処理を行う。
// シーンの初期化処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Initialize(
	const float			fMoveSpeed, 
	const Vector3DF&	vec3Position,
	const Vector3DF&	vec3Rotation, 
	const Vector3DF&	vec3Scale,
	const Vector3DF&	vec3MoveDirection
) 
{
	m_fMoveSpeed				= fMoveSpeed;
	m_Transform.position		= vec3Position;
	m_Transform.rotation		= vec3Rotation;
	m_Transform.scale			= vec3Scale;
	m_vec3MoveDirection			= vec3MoveDirection;

	

m_SphereCollider.SetRadius( 0.3f );

	// 発射のSEを再生する
	NS_Sound::Play( m_strSEShotName );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 更新処理
//
// @note : 
//
// 更新処理を行う。
// シーンの更新処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Update() 
{
	// 移動処理
	Move();

	// 破棄処理
	Destroy();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 描画処理
//
// @note : 
//
// 描画処理を行う。
// シーンの描画処理で行うようにする。
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Draw()
{
	// ポインタチェック
	ASSERT_POINTER_CHECK( m_pModel );



	glPushMatrix();



	glTranslatef( m_Transform.position.x, m_Transform.position.y, m_Transform.position.z );

	glRotatef( m_Transform.rotation.y, 0, 1, 0 );
	glRotatef( m_Transform.rotation.z, 0, 0, 1 );
	glRotatef( m_Transform.rotation.x, 1, 0, 0 );

	glScalef( m_Transform.scale.x, m_Transform.scale.y, m_Transform.scale.z );
	


	// モデルを描画する
	glColor3f( 0.0, 1.0, 0.5 );
//	glLineWidth( 1 );
//	m_pModel->SimpleDrawMesh( GL_LINE_STRIP );
	m_pModel->DrawMesh();


	
	glPopMatrix();
}





void Bullet::OnColliding( const GameObject& gameObject ) 
{ 
	if ( std::string( gameObject.GetName() ) != ( std::string( TARGET_NAME ) ) ) { return; }



	m_bDestroyFlg = true;



	// 弾の衝突のSEを再生する
	NS_Sound::Play( m_strSEHitName );
}






//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 移動処理
//
// @note : 
//
// プレイヤーの移動処理を行う。
// 座標、移動方向、回転角を更新する。
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Move() 
{
	m_Transform.position += m_vec3MoveDirection * m_fMoveSpeed * Fps::Instance()->GetSPF();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : 破棄処理
//
// @note : 
//
// 弾を破棄するフラグを立てる。
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Destroy() 
{
	// 破棄フラグが立っていれば処理しない
	if ( m_bDestroyFlg ) { return; }

	

	m_bDestroyFlg = ( m_fTimer >= 0.5f );

	m_fTimer += Fps::Instance()->GetSPF();
}