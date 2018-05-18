#ifndef _INCLUDE_GUARD_BOXCOLLIDER_H_
#define _INCLUDE_GUARD_BOXCOLLIDER_H_



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
// @purpose : �{�b�N�X�R���C�_�N���X
//
// @note : 
//
// ����̃R���C�_��\������N���X�B
// OBB�̏Փ˔�����s���B
//----------------------------------------------------------------------------------------------------------------------------------
class BoxCollider
{
public:

	// �R���X�g���N�^
	BoxCollider( const Vector3DF* pvec3VertexPositionData, const unsigned int uiVertexPositionCount, const Transform& transform );

	// �f�X�g���N�^
	~BoxCollider();

	
	const Vector3DF& GetCenter() const;
	
	const Vector3DF& GetSize() const;

	void SetCenter( const Vector3DF& vec3Center );

	void SetSize( const Vector3DF& vec3Size );



	bool CollisionDetection( const BoxCollider* pBoxCollider );



	void DrawBox();

private:

	void CreateBox( const Vector3DF* pvec3VertexPositionData, const unsigned int uiVertexPositionCount );

	Matrix4x4F GetWorldMatrix() const;

private:
	
	// �����o�ϐ�

	Vector3DF m_vec3Center;

	Vector3DF m_vec3Size;


	const Transform& m_Transform;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_BOXCOLLIDER_H_