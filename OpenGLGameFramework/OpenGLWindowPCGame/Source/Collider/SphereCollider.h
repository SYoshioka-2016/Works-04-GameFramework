#ifndef _INCLUDE_GUARD_SPHERECOLLIDER_H_
#define _INCLUDE_GUARD_SPHERECOLLIDER_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TRANSFORM_H_
#include "../Transform/Transform.h"
#endif	// #ifndef _INCLUDE_GUARD_TRANSFORM_H_

#ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_
#include <MyUtilityLib.h>
#endif	// #ifndef _INCLUDE_GUARD_MYUTILITYLIB_H_



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
// @purpose : �X�t�B�A�R���C�_�N���X
//
// @note : 
//
// ����̃R���C�_��\������N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class SphereCollider
{
public:

	// �R���X�g���N�^
	SphereCollider( const Transform& transform );

	// �f�X�g���N�^
	~SphereCollider();



	// �Փ˔���
	bool CollisionDetection( const SphereCollider& sphereCollider );


	
	// ���S�ʒu�̎擾
	const Vector3DF& GetCenter() const;

	// ���a�̎擾
	const float GetRadius() const;
	
	// ���s�ړ��������S�ʒu�̎擾
	Vector3DF GetTranslatedCenter() const;
	
	// ���S�ʒu�̐ݒ�
	void SetCenter( const Vector3DF& vec3Center );
	
	// ���a�̐ݒ�
	void SetRadius( const float fRadius );

private:
	
	// �����o�ϐ�

	// ���S�ʒu
	Vector3DF				m_vec3Center;

	// ���̔��a
	float					m_fRadius;

	// �g�����X�t�H�[��
	const Transform&		m_Transform;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_SPHERECOLLIDER_H_