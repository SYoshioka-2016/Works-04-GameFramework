#ifndef _INCLUDE_GUARD_CAMERA_H_
#define _INCLUDE_GUARD_CAMERA_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_

#ifndef _INCLUDE_GUARD_CAMERADESC_H_
#include "../Desc/CameraDesc.h"
#endif	// #ifndef _INCLUDE_GUARD_CAMERADESC_H_



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
// �N���X��`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �J�����N���X
//
// @note : 
//
// �J������\������N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class Camera 
{
public:

	// �R���X�g���N�^
	Camera();

	// �R���X�g���N�^
	Camera( const CAMERA_DESC& desc );
	
	// �f�X�g���N�^
	~Camera();



	// �B�e�J�n
	void Start();

	// �B�e�I��
	void End();

	// �������e���[�h�ɕύX
	void ChangeToPerspectiveGraphicMode();

	// ���s���e���[�h�ɕύX
	void ChangeToOrthoGraphicMode();



	// �ˉe�ϊ��s��̎擾
	Matrix4x4F GetProjectionMatrix();
	
	// ����ϊ��s��̎擾
	Matrix4x4F GetViewMatrix();

	// �������e�ϊ��s��̎擾
	Matrix4x4F GetPerspectiveMatrix();
	
	// ���s���e�ϊ��s��̎擾
	Matrix4x4F GetOrthoMatrix();
	
	// ���_�ϊ��s��̎擾
	Matrix4x4F GetLookAtMatrix();



	// ���_�̎擾
	const Vector3DF& GetEye() const;

	// ���_�̐ݒ�
	void SetEye( const Vector3DF& vec3Eye );

	// �����_�̎擾
	Vector3DF GetLookAt() const;

	// �����_�̐ݒ�
	void SetLookAt( const Vector3DF& vec3LookAt );

	// ��x�N�g���̎擾
	const Vector3DF& GetUp() const;

	// ��x�N�g���̐ݒ�
	void SetUp( const Vector3DF& vec3Up );



	// �J�����L�q�q�̎擾
	const CAMERA_DESC& GetCameraDesc() const;
	
	// �J�����L�q�q�̐ݒ�
	void SetCameraDesc( const CAMERA_DESC& desc );
	
	// ����p�̐ݒ�
	void SetFieldOfView( const float fFieldOfView );
	
	// �A�X�y�N�g��̐ݒ�
	void SetAspect( const float fAspect );
	
	// Near�ʂ̐ݒ�
	void SetZNear( const float fZNear );
	
	// Far�ʂ̐ݒ�
	void SetZFar( const float fZFar );
	
	// ���s���e�O���t�B�b�N�̕\���̈�̃T�C�Y�̐ݒ�
	void SetOrthoSize( const float fOrthoSize );
	
	// �N���A�J���[�̐ݒ�
	void SetClearColor( const Color4F& clearColor );
	
	// �r���[�|�[�g�̐ݒ�
	void SetViewport( const VIEWPORT_DESC& viewport );

protected:

	// �����o�ϐ�

	// �J�����L�q�q
	CAMERA_DESC			m_Desc;

	// �B�e�J�n�t���O
	bool				m_bStartedFlg;

	// �ޔ�p�r���[�|�[�g�o�b�t�@
	VIEWPORT_DESC		m_ViewportBuffer;

	// �ޔ�p�v���W�F�N�V�����s��o�b�t�@
	Matrix4x4F			m_mat4ProjectionMatrixBuffer;

	// �ޔ�p���f���r���[�s��o�b�t�@
	Matrix4x4F			m_mat4ModelViewMatrixBuffer;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_CAMERA_H_