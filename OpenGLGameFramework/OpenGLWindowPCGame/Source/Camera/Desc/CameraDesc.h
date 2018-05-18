#ifndef _INCLUDE_GUARD_CAMERADESC_H_
#define _INCLUDE_GUARD_CAMERADESC_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_VIEWPORTDESC_H_
#include "ViewportDesc.h"
#endif	// #ifndef _INCLUDE_GUARD_VIEWPORTDESC_H_



//==================================================================================================================================
// ���O���
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Q�[�����O���
//
// @note : 
//
// �Q�[���A�v���P�[�V�����֘A�̊֐���N���X���Ǘ����閼�O��ԁB
// �Q�[�����\������N���X�͑S�Ă��̖��O��Ԃɒu���悤�ɂ���B
//----------------------------------------------------------------------------------------------------------------------------------
namespace NS_OpenGLWindowPCGame
{



//==================================================================================================================================
// �\���̒�`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �J�����L�q�q
//
// @note : 
//
// �J�����̏����Ǘ�����\���́B
//----------------------------------------------------------------------------------------------------------------------------------
struct CAMERA_DESC
{
	// ����p
	float			fieldOfView;

	// �A�X�y�N�g��
	float			aspect;

	// Near��
	float			zNear;

	// Far��
	float			zFar;

	// ���s���e�O���t�B�b�N�̕\���̈�̃T�C�Y
	float			orthoSize;

	// ���s���e���[�h��?( true : ���s���e���[�h | false : �������e���[�h )
	bool			isOrthoGraphic;

	// �N���A�J���[
	Color4F			clearColor;

	// �r���[�|�[�g�L�q�q
	VIEWPORT_DESC	viewport;

	// ���_
	Vector3DF		eye;

	// �����_
	Vector3DF		lookAt;

	// �J�����̏�x�N�g��
	Vector3DF		up;



	// �R���X�g���N�^
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

	// �R���X�g���N�^
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