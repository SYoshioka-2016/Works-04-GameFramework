//==================================================================================================================================
// �C���N���[�h
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
// @param [in] / const float fViewingAngle	: ����p
// @param [in] / const float fAspect		: �A�X�y�N�g��
// @param [in] / const float fNear			: Near��
// @param [in] / const float fFar			: Far��
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
	// �J�����̎���p��ݒ�
	SetViewingAngle( fViewingAngle );

	// �J�����̃A�X�y�N�g���ݒ�
	m_fAspect = fAspect;

	// �J�����̃N���b�v�ʂ�ݒ�
	SetClippingPlane( 0.1f, 100.0f );
*/
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
GameCamera::~GameCamera() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������荞�݃g���b�N����
//
// @param [in] / float fVerticalAngle	: �J�����̐���������]�p
// @param [in] / float fDeltaAngle		: 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̐���������]�p���w��̐��l�ɂȂ�܂ŕω�������B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackVerticalToward( float fVerticalAngle, float fDeltaAngle ) 
{
	// �w��̐���������]�p�ƌ��݂̐���������]�p����v�����珈�����Ȃ�
	if ( m_fVerticalAngle == fVerticalAngle ) { return; }



	// 1�t���[���̉�]�p�𒲐�
	fDeltaAngle = abs( fDeltaAngle );
	fDeltaAngle *= ( m_fVerticalAngle > fVerticalAngle ) ? -1 : 1;

	// ���݂̐���������]�p��1�t���[���̉�]�p�����Z����
	m_fVerticalAngle += fDeltaAngle;

	// �w��̐���������]�p�ƌ��݂̐���������]�p�̍����������Ȃ������]�I��
	if ( abs( m_fVerticalAngle - fVerticalAngle ) < fDeltaAngle ) {
	
		// ���݂̐���������]�p�Ɏw��̐���������]�p��ݒ肷��
		m_fVerticalAngle = fVerticalAngle;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������荞�݃g���b�N����
//
// @param [in] / float fHorizontalAngle	: �J�����̐���������]�p
// @param [in] / float fDeltaAngle		: 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̐���������]�p���w��̐��l�ɂȂ�܂ŕω�������B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackHorizontalToward( float fHorizontalAngle, float fDeltaAngle ) 
{
//fHorizontalAngle *= -1;

	// �w��̐���������]�p�ƌ��݂̐���������]�p����v�����珈�����Ȃ�
	if ( m_fHorizontalAngle == fHorizontalAngle ) { return; }



	// 1�t���[���̉�]�p�𒲐�
	fDeltaAngle = abs( fDeltaAngle );
	fDeltaAngle *= ( m_fHorizontalAngle > fHorizontalAngle ) ? -1 : 1;

	// ���݂̐���������]�p��1�t���[���̉�]�p�����Z����
	m_fHorizontalAngle += fDeltaAngle;

	// �w��̐���������]�p�ƌ��݂̐���������]�p�̍����������Ȃ������]�I��
	if ( abs( m_fHorizontalAngle - fHorizontalAngle ) < fDeltaAngle ) {
	
		// ���݂̐���������]�p�Ɏw��̐���������]�p��ݒ肷��
		m_fHorizontalAngle = fHorizontalAngle;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���荞�݃g���b�N����
//
// @param [in] / float fDeltaAngle : 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̐���������]�p�����Z����B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackUpToward( float fDeltaAngle ) 
{
	// ���݂̐���������]�p��1�t���[���̉�]�p�����Z����
	m_fVerticalAngle += abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����荞�݃g���b�N����
//
// @param [in] / float fDeltaAngle : 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̐���������]�p�����Z����B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackDownToward( float fDeltaAngle ) 
{
	// ���݂̐���������]�p��1�t���[���̉�]�p�����Z����
	m_fVerticalAngle -= abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �E��荞�݃g���b�N����
//
// @param [in] / float fDeltaAngle : 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̐���������]�p�����Z����B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackRightToward( float fDeltaAngle ) 
{
	// ���݂̐���������]�p��1�t���[���̉�]�p�����Z����
	m_fHorizontalAngle -= abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����荞�݃g���b�N����
//
// @param [in] / float fDeltaAngle : 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̐���������]�p�����Z����B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::WraparoundTrackLeftToward( float fDeltaAngle ) 
{
	// ���݂̐���������]�p��1�t���[���̉�]�p�����Z����
	m_fHorizontalAngle += abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Y�[������
//
// @param [in] / float fViewingAngle	: ����p
// @param [in] / float fDeltaAngle		: 1�t���[���̎���p�̕ω��ʂ̑傫��
//
// @note : 
//
// �J�����̎���p���w��̐��l�ɂȂ�܂ŕω�������B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::ZoomToward( float fViewingAngle, float fDeltaAngle ) 
{
/*
	// �w��̎���p�ƌ��݂̎���p����v�����珈�����Ȃ�
	if ( m_fViewingAngle == fViewingAngle ) { return; }



	// 1�t���[���̎���p�̕ω��ʂ̑傫���𒲐�
	fDeltaAngle = abs( fDeltaAngle );
	fDeltaAngle *= ( m_fViewingAngle > fViewingAngle ) ? -1 : 1;

	// ���݂̎���p��1�t���[���̎���p�̕ω��ʂ̑傫�������Z����
	m_fViewingAngle += fDeltaAngle;

	// �w��̎���p�ƌ��݂̎���p�̍����������Ȃ�����I��
	if ( abs( m_fViewingAngle - fViewingAngle ) < fDeltaAngle ) {
	
		// ���݂̎���p�Ɏw��̎���p��ݒ肷��
		m_fViewingAngle = fViewingAngle;
	}
*/
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Y�[���C������
//
// @param [in] / float fDeltaAngle : 1�t���[���̎���p�̕ω��ʂ̑傫��
//
// @note : 
//
// �J�����̎���p����������B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::ZoomInToward( float fDeltaAngle ) 
{
	// ���݂̎���p��1�t���[���̎���p�̕ω��ʂ̑傫�������Z����
//	m_fViewingAngle -= abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Y�[���A�E�g����
//
// @param [in] / float fDeltaAngle : 1�t���[���̎���p�̕ω��ʂ̑傫��
//
// @note : 
//
// �J�����̎���p���L������B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::ZoomOutToward( float fDeltaAngle ) 
{
	// ���݂̎���p��1�t���[���̎���p�̕ω��ʂ̑傫�������Z����
//	m_fViewingAngle += abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Y�[������
//
// @param [in] / float fZoomInViewingAngle	: �Y�[���C���̎���p
// @param [in] / float fZoomOutViewingAngle	: �Y�[���A�E�g�̎���p
// @param [in] / float fDeltaAngle			: 1�t���[���̎���p�̕ω��ʂ̑傫��
//
// @note : 
//
// �J�����̎���p���w��̐��l�ɂȂ�܂ŕω�������B
// �ǐՑΏۂ̈ړ������ƃJ�����̑O�����ɂ���ăY�[����؂�ւ���B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::ZoomToward( 
	float fZoomInViewingAngle, 
	float fZoomOutViewingAngle, 
	float fDeltaAngle 
) 
{
	// �����^�[�Q�b�g�̈ʒu��������Ώ������Ȃ�
	if ( NULL_CHECK( m_pvec3LookTarget ) ) { return; }



	// �^�[�Q�b�g�̈ړ������x�N�g��
	Vector3DF vec3TargetMoveDirection = GetTergetMoveDirection();
	if ( vec3TargetMoveDirection.Length() <= 0 ) { return; }

	// �J�����̑O�����x�N�g��
	Vector3DF vec3CameraForwardDirection = GetCameraForward();
	if ( vec3CameraForwardDirection.Length() <= 0 ) { return; }



	// �^�[�Q�b�g�̈ړ������x�N�g���ƃJ�����̑O�����x�N�g���̓���
	float fDot = Vector3DF::Dot( vec3TargetMoveDirection, vec3CameraForwardDirection );



	// ����p�̍ŏ��l�𒲐�
	fZoomInViewingAngle = (float)Clamp( fZoomInViewingAngle, fZoomInViewingAngle, fZoomOutViewingAngle );



	// ���ς̒l�ɂ���Ď���p��ݒ肷��
	float fZoomViewingAngle = ( ( 0 <= fDot ) && ( 1 >= fDot ) ) ? fZoomOutViewingAngle : fZoomInViewingAngle;

	// �Y�[������
	ZoomToward( fZoomViewingAngle, fDeltaAngle * fDot );



	// �����^�[�Q�b�g�̈ʒu��ۑ�
	m_vec3PrevLookTarget = *m_pvec3LookTarget;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���[����]����
//
// @param [in] / const float fRollAngle		: ���[����]�p
// @param [in] / float		 fDeltaAngle	: 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̃��[����]�p���w��̐��l�ɂȂ�܂ŕω�������B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::RollToward( const float fRollAngle, float fDeltaAngle ) 
{
	// �w��̃��[����]�p�ƌ��݂̃��[����]�p����v�����珈�����Ȃ�
	if ( m_fRollAngle == fRollAngle ) { return; }



	// 1�t���[���̉�]�p�𒲐�
	fDeltaAngle *= ( m_fRollAngle > fRollAngle ) ? -1 : 1;

	// ���݂̃��[����]�p��1�t���[���̉�]�p�����Z����
	m_fRollAngle += fDeltaAngle;

	// �w��̃��[����]�p�ƌ��݂̃��[����]�p�̍����������Ȃ������]�I��
	if ( abs( m_fRollAngle - fRollAngle ) < fDeltaAngle ) {
	
		// ���݂̃��[����]�p�Ɏw��̃��[����]�p��ݒ肷��
		m_fRollAngle = fRollAngle;
	}
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �E���[����]����
//
// @param [in] / float fDeltaAngle : 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̃��[����]�p�����Z����B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::RollRightToward( float fDeltaAngle ) 
{
	// ���݂̃��[����]�p��1�t���[���̉�]�p�����Z����
	m_fRollAngle += abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �����[����]����
//
// @param [in] / float fDeltaAngle : 1�t���[���̉�]�p
//
// @note : 
//
// �J�����̃��[����]�p�����Z����B
// �X�V�����̒��ŌĂԂ悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::RollLeftToward( float fDeltaAngle )
{
	// ���݂̃��[����]�p��1�t���[���̉�]�p�����Z����
	m_fRollAngle -= abs( fDeltaAngle );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������]�p�̎擾
//
// @return / float : ����������]�p
//	
// @note : 
//
// ����������]�p��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
float GameCamera::GetVerticalAngle() const { return m_fVerticalAngle; }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������]�p�̎擾
//
// @return / float : ����������]�p
//	
// @note : 
//
// ����������]�p��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
float GameCamera::GetHorizontalAngle() const { return m_fHorizontalAngle; }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �ړ��x�N�g���̎擾
//
// @return / Vector3DF : �ړ��x�N�g��
//	
// @note : 
//
// �ړ��x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF GameCamera::GetMoveVector() const { return GetEye() - m_vec3PrevPosition; }



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������]�p�̐ݒ�
//
// @param [in] / const float fVerticalAngle	: ���������̉�]�p
//	
// @note : 
//
// �J�����̐���������]�p��ݒ肷��B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::SetVerticalAngle( const float fVerticalAngle ) 
{ 
	m_fVerticalAngle = fVerticalAngle; 
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ����������]�p�̐ݒ�
//
// @param [in] / const float fVerticalAngle	: ���������̉�]�p
//	
// @note : 
//
// �J�����̐���������]�p��ݒ肷��B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::SetHorizontalAngle( const float fHorizontalAngle ) 
{ 
	m_fHorizontalAngle = fHorizontalAngle; 
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �ǐՑΏۂ̐ݒ�
//
// @param [in] / Vector3DF*		pvec3LookTarget				: ��������^�[�Q�b�g�̈ʒu
// @param [in] / const float	fDistance					: �����_���王�_�܂ł̋���
//	
// @note : 
//
// ��������^�[�Q�b�g�̈ʒu�A�ǐՑΏۂƂ̋�����ݒ肷��B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::SetChaseTarget( 
	Vector3DF*		pvec3LookTarget, 
	const float		fDistance
)
{
	// ��������^�[�Q�b�g�̈ʒu��������Ώ������Ȃ�
	if ( NULL_CHECK( pvec3LookTarget ) ) { return; }



	// ��������^�[�Q�b�g�̈ʒu��ݒ�
	m_pvec3LookTarget	= pvec3LookTarget;

	// �^�[�Q�b�g�ƃJ�����̋�����ݒ�
	m_fDistance			= fDistance;



	// �^�[�Q�b�g�̍��W��ۑ�����
	m_vec3PrevLookTarget = *m_pvec3LookTarget;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�V����
//
// @note : 
//
//
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::update() 
{
	// ���_��ۑ�����
	m_vec3PrevPosition = GetEye();



	// �J�����̃Z�b�e�B���O
	SettingCamera();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �J�����̃Z�b�e�B���O
//
// @note : 
//
// ���_�A��x�N�g���A�����_��ݒ肷��B
// ��������^�[�Q�b�g�̈ʒu������Ɏw��̋��������ړ����A
// ��������^�[�Q�b�g�̈ʒu�𒆐S�ɐ����A���������ɂ��ꂼ��w��̊p�x������]�����ʒu�Ɏ��_��ݒ肷��B
//----------------------------------------------------------------------------------------------------------------------------------
void GameCamera::SettingCamera() 
{
	// ��������^�[�Q�b�g�̈ʒu��������Ώ������Ȃ�
	if ( NULL_CHECK( m_pvec3LookTarget ) ) { return; }

	
/*
	// ���_���w��̋�����������āAx���Ɏw��̊p�x������]�����ʒu�ɂ���
	m_vec3Eye = Rotate( Vector3DF( 0, 0, m_fDistance ), Vector3DF( 1, 0, 0 ), m_fVerticalAngle );

	// ���_��y���Ɏw��̊p�x������]�����ʒu�ɂ���
	m_vec3Eye = Rotate( m_vec3Eye, Vector3DF( 0, 1, 0 ), m_fHorizontalAngle );
	
	

	// �J�����̏�x�N�g����^�ォ��x���Ɏw��̊p�x������]�����x�N�g���ɂ���
	m_vec3Up = Rotate( Vector3DF( 0, 1, 0 ), Vector3DF( 1, 0, 0 ), m_fVerticalAngle );
	
	// �J�����̏�x�N�g����y���Ɏw��̊p�x������]�����x�N�g���ɂ���
	m_vec3Up = Rotate( m_vec3Up, Vector3DF( 0, 1, 0 ), m_fHorizontalAngle );



	// �J���������[����]����
	RollCamera( m_fRollAngle );

	// �����_�ɒ����^�[�Q�b�g�̈ʒu��ݒ肷��
	m_vec3LookAt = *m_pvec3LookTarget;

	// ���_�̊�����_���璍���_�Ɉړ�����
	m_vec3Eye += m_vec3LookAt;
	
	// �����_�̐ݒ�
	SetLookAt( m_vec3LookAt );
*/
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �J�����̑O�����x�N�g���̎擾
//
// @return / Vector3DF : �J�����̑O�����x�N�g��
//	
// @note : 
//
// �J�����̑O�����x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF GameCamera::GetCameraForward() const
{
	// �J�����̑O�����x�N�g��
	Vector3DF vec3CameraForwardDirection = GetLookAt() - GetEye();
	if ( vec3CameraForwardDirection.Length() <= 0 ) { return Vector3DF(); }



	// �J�����̑O�����x�N�g���𐳋K��
	return vec3CameraForwardDirection.Normalized();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �^�[�Q�b�g�̈ړ��x�N�g���̎擾
//
// @return / Vector3DF : �^�[�Q�b�g�̈ړ��x�N�g��
//	
// @note : 
//
// �^�[�Q�b�g�̈ړ��x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF GameCamera::GetTergetMoveVector() const 
{
	// �����^�[�Q�b�g�̈ʒu��������Ώ������Ȃ�
	if ( NULL_CHECK( m_pvec3LookTarget ) ) { return Vector3DF(); }



	// �^�[�Q�b�g�̈ړ��x�N�g��
	return *m_pvec3LookTarget - m_vec3PrevLookTarget;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �^�[�Q�b�g�̈ړ������x�N�g���̎擾
//
// @return / Vector3DF : �^�[�Q�b�g�̈ړ������x�N�g��
//	
// @note : 
//
// �^�[�Q�b�g�̈ړ������x�N�g����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
Vector3DF GameCamera::GetTergetMoveDirection() const 
{
	// �^�[�Q�b�g�̈ړ��x�N�g��
	Vector3DF vec3TerGetMoveVector = GetTergetMoveVector();
	if ( vec3TerGetMoveVector.Length() <= 0 ) { return Vector3DF(); }



	// �^�[�Q�b�g�̈ړ��x�N�g���𐳋K��
	return vec3TerGetMoveVector.Normalized();
}