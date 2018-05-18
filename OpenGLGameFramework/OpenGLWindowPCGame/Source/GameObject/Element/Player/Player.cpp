//==================================================================================================================================
// �C���N���[�h
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
// using�f�B���N�e�B�u
//==================================================================================================================================

// �Q�[�����O���
using namespace NS_OpenGLWindowPCGame;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @param [in] / ChaseCamera*							pChaseCamera		: �ǐՃJ����
// @param [in] / const NS_Resource::NS_Model::OGLModel* pPlayerModel		: �v���C���[�̃��f��
// @param [in] / const NS_Resource::NS_Model::OGLModel* pBulletModel		: �e�̃��f��
// @param [in] / GameObjectManager*						pGameObjectManager	: �Q�[���I�u�W�F�N�g�Ǘ��N���X
// @param [in] / const char*							strSEShotName		: ���˂�SE��
// @param [in] / const char*							strSEHitName		: �e�̏Փ˂�SE��
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
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pPlayerModel );
	ASSERT_POINTER_CHECK( m_pBulletModel );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );



	SetName( PLAYER_NAME );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Player::~Player() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������
//
// @param [in] / const float		fMoveSpeed				: �ړ��̑���
// @param [in] / const Vector3DF&	vec3Position			: ���W
// @param [in] / const Vector3DF&	vec3Rotation			: ��]�p
// @param [in] / const Vector3DF&	vec3Scale				: �X�P�[���l
// @param [in] / const Vector3DF&	vec3RotationAngleSpeed	: ��]�̑���
//
// @note : 
//
// �������������s���B
// �V�[���̏����������ōs���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void Player::Initialize(
	const float			fMoveSpeed, 
	const Vector3DF&	vec3Position,
	const Vector3DF&	vec3Rotation, 
	const Vector3DF&	vec3Scale,
	const Vector3DF&	vec3RotationAngleSpeed
) 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pChaseCamera );
	ASSERT_POINTER_CHECK( m_pPlayerModel );



	m_fMoveSpeed				= fMoveSpeed;
	m_Transform.position		= vec3Position;
	m_Transform.rotation		= vec3Rotation;
	m_Transform.scale			= vec3Scale;
	m_vec3RotationAngleSpeed	= vec3RotationAngleSpeed;

	

	m_SphereCollider.SetRadius( 1 );


	// �v���C���[���J�����̒ǐՑΏۂɐݒ肷��
	m_pChaseCamera->SetTarget( &m_Transform.position );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�V����
//
// @note : 
//
// �X�V�������s���B
// �V�[���̍X�V�����ōs���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void Player::Update() 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pChaseCamera );

printf( "%f\n", Fps::Instance()->GetFPS() );
//printf( "%f %f %f\n", m_Transform.position.x, m_Transform.position.y, m_Transform.position.z );

	// �ړ�����
	Move();
	
	// �e���ˊJ�n����
	ShootStart();


	
	// �J�����̐���������]�p��ݒ肷��
	m_pChaseCamera->SetVerticalAngle( m_Transform.rotation.x + 0.0f );

	// �J�����̐���������]�p��ݒ肷��
	m_pChaseCamera->SetHorizontalAngle( -m_Transform.rotation.y + 180.0f ); 
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
// �`�揈�����s���B
// �V�[���̕`�揈���ōs���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void Player::Draw()
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pPlayerModel );



	glPushMatrix();



	glTranslatef( m_Transform.position.x, m_Transform.position.y, m_Transform.position.z );

	glRotatef( m_Transform.rotation.y, 0, 1, 0 );
	glRotatef( m_Transform.rotation.x, 1, 0, 0 );
	glRotatef( m_Transform.rotation.z, 0, 0, 1 );

	
	glColor3f( 1.0, 0.0, 0.5 );
	NS_Graphic::NS_Graphic3D::DrawLine( 1, Vector3DF( 0, 0, -50 ), Vector3DF( 0, 0, 50 ) );

	glScalef( m_Transform.scale.x, m_Transform.scale.y, m_Transform.scale.z );
	


	// ���f����`�悷��
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
// @purpose : �O�Ɉړ�������͂���������?
//
// @return / bool : �O�Ɉړ�������͂���������?( true : ���͂��� | false : ���͂Ȃ� )
//
// @note : 
//
// �O�Ɉړ�������͂������������肵�Č��ʂ�Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputMoveForward() const 
{
	return NS_Input::NS_Keyboard::GetKey( 'W' );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���Ɉړ�������͂���������?
//
// @return / bool : ���Ɉړ�������͂���������?( true : ���͂��� | false : ���͂Ȃ� )
//
// @note : 
//
// ���Ɉړ�������͂������������肵�Č��ʂ�Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputMoveBack() const
{
	return NS_Input::NS_Keyboard::GetKey( 'S' );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �E�ɐ��񂷂���͂���������?
//
// @return / bool : �E�ɐ��񂷂���͂���������?( true : ���͂��� | false : ���͂Ȃ� )
//
// @note : 
//
// �E�ɐ��񂷂���͂������������肵�Č��ʂ�Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputYawRotationRight() const
{
	return NS_Input::NS_Keyboard::GetKey( VK_RIGHT );
}
	


//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���ɐ��񂷂���͂���������?
//
// @return / bool : ���ɐ��񂷂���͂���������?( true : ���͂��� | false : ���͂Ȃ� )
//
// @note : 
//
// ���ɐ��񂷂���͂������������肵�Č��ʂ�Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputYawRotationLeft() const
{
	return NS_Input::NS_Keyboard::GetKey( VK_LEFT );
}
	


//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ��Ƀs�b�`��]������͂���������?
//
// @return / bool : ��Ƀs�b�`��]������͂���������?( true : ���͂��� | false : ���͂Ȃ� )
//
// @note : 
//
// ��Ƀs�b�`��]������͂������������肵�Č��ʂ�Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputPitchRotationUp() const
{
	return NS_Input::NS_Keyboard::GetKey( VK_DOWN );
}
	


//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���Ƀs�b�`��]������͂���������?
//
// @return / bool : ���Ƀs�b�`��]������͂���������?( true : ���͂��� | false : ���͂Ȃ� )
//
// @note : 
//
// ���Ƀs�b�`��]������͂������������肵�Č��ʂ�Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputPitchRotationDown() const
{
	return NS_Input::NS_Keyboard::GetKey( VK_UP );
}
	

	
//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e�𔭎˂�����͂���������?
//
// @return / bool : �e�𔭎˂�����͂���������?( true : ���͂��� | false : ���͂Ȃ� )
//
// @note : 
//
// �e�𔭎˂�����͂������������肵�Č��ʂ�Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
bool Player::IsInputShoot() const 
{
	return NS_Input::NS_Keyboard::GetKeyDown( VK_SPACE );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �ړ�����
//
// @note : 
//
// �v���C���[�̍��W���X�V����B
//----------------------------------------------------------------------------------------------------------------------------------
void Player::Move() 
{
/*
	// �ړ������x�N�g��
	m_vec3MoveDirection = Vector3DF();

	// �O�Ɉړ�
	m_vec3MoveDirection.z -= ( IsInputMoveForward() ) ? 1 : 0;
	
	// ���Ɉړ�	
	m_vec3MoveDirection.z += ( IsInputMoveBack() ) ? 1 : 0;

	// �ړ������x�N�g���𐳋K��
	m_vec3MoveDirection = ( 0 < m_vec3MoveDirection.Length() ) ? m_vec3MoveDirection.Normalized() : Vector3DF();
*/
	// �ړ������x�N�g��
	m_vec3MoveDirection = Vector3DF( 0, 0, -1 );



	// �s�b�`��]

	// �s�b�`��]�p
	const float fPitchRotationAngle = abs( m_vec3RotationAngleSpeed.x ) * Fps::Instance()->GetSPF();

	// �p�x��������
	m_Transform.rotation.x -= ( IsInputPitchRotationUp() )		? fPitchRotationAngle : 0;
	
	// �p�x���グ��
	m_Transform.rotation.x += ( IsInputPitchRotationDown() )	? fPitchRotationAngle : 0;

	// �p�x�̏グ�����ɕω����Ȃ���΃s�b�`��]�p����ɖ߂�
	if ( IsInputPitchRotationUp() == IsInputPitchRotationDown() ) 
	{
		m_Transform.rotation.x += fPitchRotationAngle * ( ( 0 > m_Transform.rotation.x ) ? 1 : -1 );
		if ( abs( m_Transform.rotation.x ) <= fPitchRotationAngle ) { m_Transform.rotation.x = 0; }
	}

	// �s�b�`��]�p�𒲐�����
	m_Transform.rotation.x = (float)Clamp( m_Transform.rotation.x, -30.0f, 30.0f );

	// �ړ������x�N�g�����s�b�`��]����
	m_vec3MoveDirection = NS_Graphic::NS_GraphicMathematics::RotateVector( m_vec3MoveDirection, Vector3DF( 1, 0, 0 ), m_Transform.rotation.x );



	// ���[��]
		
	// ���[��]�p
	const float fYawRotationAngle = abs( m_vec3RotationAngleSpeed.y ) * Fps::Instance()->GetSPF();

	// �p�x���グ��
	m_Transform.rotation.y -= ( IsInputYawRotationRight() ) ? fYawRotationAngle : 0;

	// �p�x��������
	m_Transform.rotation.y += ( IsInputYawRotationLeft() )	? fYawRotationAngle : 0;

	// �ړ������x�N�g�������[��]����
	m_vec3MoveDirection = NS_Graphic::NS_GraphicMathematics::RotateVector( m_vec3MoveDirection, Vector3DF( 0, 1, 0 ), -m_Transform.rotation.y - 180.0f );
//m_vec3MoveDirection *= -1;



	// ���[����]

	// ���[����]�p
	const float fRollRotationAngle = abs( m_vec3RotationAngleSpeed.z ) * Fps::Instance()->GetSPF();

	// �p�x���グ��
	m_Transform.rotation.z += ( IsInputYawRotationRight() )	? fRollRotationAngle : 0;

	// �p�x��������
	m_Transform.rotation.z -= ( IsInputYawRotationLeft() )	? fRollRotationAngle : 0;

	// �p�x�̏グ�����ɕω����Ȃ���΃��[����]�p����ɖ߂�
	if ( IsInputYawRotationRight() == IsInputYawRotationLeft() ) 
	{
		m_Transform.rotation.z += fRollRotationAngle * ( ( 0 > m_Transform.rotation.z ) ? 1 : -1 );
		if ( abs( m_Transform.rotation.z ) <= fRollRotationAngle ) { m_Transform.rotation.z = 0; }
	}

	// ���[����]�p�𒲐�����
	m_Transform.rotation.z = (float)Clamp( m_Transform.rotation.z, -30.0f, 30.0f );



	// �v���C���[�̍��W�Ɉړ��̃x�N�g�������Z����
	m_Transform.position += m_vec3MoveDirection * abs( m_fMoveSpeed ) * Fps::Instance()->GetSPF();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �e���ˊJ�n����
//
// @note : 
//
// �e�𐶐����A�Q�[���I�u�W�F�N�g�Ƃ��ăV�[���ɒǉ�����B
//----------------------------------------------------------------------------------------------------------------------------------
void Player::ShootStart() 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pBulletModel );
	ASSERT_POINTER_CHECK( m_pGameObjectManager );



	// �e�𔭎˂�����͂�������Ώ������Ȃ�
	if ( !IsInputShoot() ) { return; }



	// �e�𐶐�����
	Bullet* pBullet = new Bullet( m_pBulletModel, m_strSEShotName, m_strSEHitName );
	
	// �e�̉�]�l��ݒ�
	Vector3DF vec3Rotation = Vector3DF( 90, 180, 0 ) + Vector3DF( m_Transform.rotation.x, m_Transform.rotation.y + 180, 0 );

	// �e�̐i�s������ݒ�
	Vector3DF vec3Forward( 0, 0, -1 );
	vec3Forward = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Forward, VECTOR3DF_RIGHT, m_Transform.rotation.x );
	vec3Forward = NS_Graphic::NS_GraphicMathematics::RotateVector( vec3Forward, VECTOR3DF_UP, -( m_Transform.rotation.y + 180 ) );

	// �e�̏���������
	pBullet->Initialize( 
		50, 
		m_Transform.position, 
		vec3Rotation,
		Vector3DF( 0.008f, 0.008f, 0.008f ),
		vec3Forward
	);

	// �Q�[���I�u�W�F�N�g��ǉ�
	m_pGameObjectManager->AddGameObject( pBullet );
}