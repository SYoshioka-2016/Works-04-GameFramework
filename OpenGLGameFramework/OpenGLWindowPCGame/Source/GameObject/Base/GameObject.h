#ifndef _INCLUDE_GUARD_GAMEOBJECT_H_
#define _INCLUDE_GUARD_GAMEOBJECT_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_TRANSFORM_H_
#include "../../Transform/Transform.h"
#endif	// #ifndef _INCLUDE_GUARD_TRANSFORM_H_

#ifndef _INCLUDE_GUARD_SPHERECOLLIDER_H_
#include "../../Collider/SphereCollider.h"
#endif	// #ifndef _INCLUDE_GUARD_SPHERECOLLIDER_H_



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
// @purpose : �Q�[���I�u�W�F�N�g�N���X
//
// @note : 
//
// �Q�[���V�[���ɒu���I�u�W�F�N�g�̃x�[�X�ƂȂ�N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class GameObject 
{
public:

	// �R���X�g���N�^
	GameObject();

	// �f�X�g���N�^
	virtual ~GameObject();



	// �J�n����
	virtual void Start();

	// �X�V����
	virtual void Update();

	// �`�揈��
	virtual void Draw();

	// �I������
	virtual void End();


	
	// �Փˏ���
	void CollisionHandling( const GameObject& gameObject );



	// �j�����邩?
	bool IsDestroy() const;
	


	// �g�����X�t�H�[���̎擾
	const Transform& GetTransform() const;

	// �X�t�B�A�R���C�_�̎擾
	const SphereCollider& GetSphereCollider() const;

	// ���O�̎擾
	const char* GetName() const;

	// ���O�̐ݒ�
	void SetName( const char* strName );

protected:

	// �Փ˒�����
	virtual void OnColliding( const GameObject& gameObject );

protected:

	// �����o�ϐ�

	// �g�����X�t�H�[��
	Transform			m_Transform;

	// �X�t�B�A�R���C�_
	SphereCollider		m_SphereCollider;

	// �Փ˃t���O
	bool				m_bCollisionFlg;
	
	// ���O�̏Փ˃t���O
	bool				m_bPrevCollisionFlg;

	// �j���t���O
	bool				m_bDestroyFlg;

	// ���O
	std::string			m_strName;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECT_H_