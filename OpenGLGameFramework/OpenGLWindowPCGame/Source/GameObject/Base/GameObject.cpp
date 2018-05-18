//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_GAMEOBJECT_H_
#include "GameObject.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECT_H_



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
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
GameObject::GameObject() : 
	m_Transform( Transform() ), 
	m_SphereCollider( SphereCollider( m_Transform ) ),
	m_bCollisionFlg( false ),
	m_bPrevCollisionFlg( false ),
	m_bDestroyFlg( false ),
	m_strName( "" )
{ 

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
GameObject::~GameObject() 
{
	// �I������
	End();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �J�n����
//
// @note : 
//
// �Q�[���I�u�W�F�N�g�̊Ǘ��N���X�Ɏ��g���ǉ����ꂽ����1����s�����B
//----------------------------------------------------------------------------------------------------------------------------------
void GameObject::Start() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�V����
//
// @note : 
//
// �Q�[���I�u�W�F�N�g�̊Ǘ��N���X�ɊǗ�����Ă���Ԏ��s�����B
//----------------------------------------------------------------------------------------------------------------------------------
void GameObject::Update() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �`�揈��
//
// @note : 
//
// �Q�[���I�u�W�F�N�g�̊Ǘ��N���X�ɊǗ�����Ă���Ԏ��s�����B
//----------------------------------------------------------------------------------------------------------------------------------
void GameObject::Draw() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �I������
//
// @note : 
//
// ���g���폜����鎞��1����s�����B
//----------------------------------------------------------------------------------------------------------------------------------
void GameObject::End() 
{

}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Փˏ���
//
// @param [in] / const GameObject& gameObject : �Q�[���I�u�W�F�N�g�̎Q��
//
// @note : 
//
// �Q�[���I�u�W�F�N�g���m�̏Փˏ������s���B
// �Փ˂̔�����t���O�ŊǗ����A�t���O�̏�Ԃɂ���ďՓˏ����̉��z�֐������s����B
//----------------------------------------------------------------------------------------------------------------------------------
void GameObject::CollisionHandling( const GameObject& gameObject )
{
	// �Q�[���I�u�W�F�N�g���m�̏Փ˔�����擾
	if ( !m_SphereCollider.CollisionDetection( gameObject.GetSphereCollider() ) ) { return; }



	// �Փ˒�����
	OnColliding( gameObject );
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �j�����邩?
//
// @return / bool : �j�����邩?( true : �j������ | false : �j�����Ȃ� )
//
// @note : 
//
// �j���t���O��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
bool GameObject::IsDestroy() const 
{
	return m_bDestroyFlg;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �g�����X�t�H�[���̎擾
//
// @return / const Transform& : �g�����X�t�H�[��
//
// @note : 
//
// �g�����X�t�H�[����Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
const Transform& GameObject::GetTransform() const 
{
	return m_Transform;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �X�t�B�A�R���C�_�̎擾
//
// @return / const SphereCollider& : �X�t�B�A�R���C�_
//
// @note : 
//
// �X�t�B�A�R���C�_��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
const SphereCollider& GameObject::GetSphereCollider() const 
{
	return m_SphereCollider;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���O�̎擾
//
// @return / const char* : ���O
//
// @note : 
//
// ���O��Ԃ��B
//----------------------------------------------------------------------------------------------------------------------------------
const char* GameObject::GetName() const 
{
	return m_strName.c_str();
}

	

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���O�̐ݒ�
//
// @param [in] / const char* strName : ���O
//
// @note : 
//
// ���O��ݒ肷��B
//----------------------------------------------------------------------------------------------------------------------------------
void GameObject::SetName( const char* strName ) 
{
	// �|�C���^�`�F�b�N
	ASSERT_POINTER_CHECK( strName );



	m_strName = strName;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Փ˒�����
//
// @note : 
//
// ���̃Q�[���I�u�W�F�N�g�ƏՓ˂��Ă���Ԏ��s�����B
//----------------------------------------------------------------------------------------------------------------------------------
void GameObject::OnColliding( const GameObject& gameObject ) 
{

}