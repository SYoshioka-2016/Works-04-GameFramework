//==================================================================================================================================
// �C���N���[�h
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
// @param [in] / const NS_Resource::NS_Model::OGLModel* pModel			: ���f��
// @param [in] / const char*							strSEShotName	: ���˂�SE��
// @param [in] / const char*							strSEHitName	: �e�̏Փ˂�SE��
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
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pModel );



	SetName( BULLET_NAME );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
Bullet::~Bullet() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������
//
// @param [in] / const float		fMoveSpeed				: �ړ��̑���
// @param [in] / const Vector3DF&	vec3Position			: ���W
// @param [in] / const Vector3DF&	vec3Rotation			: ��]�p
// @param [in] / const Vector3DF&	vec3Scale				: �X�P�[���l
// @param [in] / const Vector3DF&	vec3MoveDirection		: �ړ�����
//
// @note : 
//
// �������������s���B
// �V�[���̏����������ōs���悤�ɂ���B
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

	// ���˂�SE���Đ�����
	NS_Sound::Play( m_strSEShotName );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�V����
//
// @note : 
//
// �X�V�������s���B
// �V�[���̍X�V�����ōs���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Update() 
{
	// �ړ�����
	Move();

	// �j������
	Destroy();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
// �`�揈�����s���B
// �V�[���̕`�揈���ōs���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Draw()
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( m_pModel );



	glPushMatrix();



	glTranslatef( m_Transform.position.x, m_Transform.position.y, m_Transform.position.z );

	glRotatef( m_Transform.rotation.y, 0, 1, 0 );
	glRotatef( m_Transform.rotation.z, 0, 0, 1 );
	glRotatef( m_Transform.rotation.x, 1, 0, 0 );

	glScalef( m_Transform.scale.x, m_Transform.scale.y, m_Transform.scale.z );
	


	// ���f����`�悷��
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



	// �e�̏Փ˂�SE���Đ�����
	NS_Sound::Play( m_strSEHitName );
}






//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �ړ�����
//
// @note : 
//
// �v���C���[�̈ړ��������s���B
// ���W�A�ړ������A��]�p���X�V����B
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Move() 
{
	m_Transform.position += m_vec3MoveDirection * m_fMoveSpeed * Fps::Instance()->GetSPF();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �j������
//
// @note : 
//
// �e��j������t���O�𗧂Ă�B
//----------------------------------------------------------------------------------------------------------------------------------
void Bullet::Destroy() 
{
	// �j���t���O�������Ă���Ώ������Ȃ�
	if ( m_bDestroyFlg ) { return; }

	

	m_bDestroyFlg = ( m_fTimer >= 0.5f );

	m_fTimer += Fps::Instance()->GetSPF();
}