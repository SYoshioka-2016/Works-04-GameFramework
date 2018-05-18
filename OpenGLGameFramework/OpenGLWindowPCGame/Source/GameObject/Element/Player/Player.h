#ifndef _INCLUDE_GUARD_PLAYER_H_
#define _INCLUDE_GUARD_PLAYER_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_GAMEOBJECT_H_
#include "../../Base/GameObject.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECT_H_



//==================================================================================================================================
// �O���錾
//==================================================================================================================================

// �ǐՃJ�����N���X
namespace NS_OpenGLWindowPCGame { class ChaseCamera; }

// ���f���N���X
namespace NS_Resource 
{
	namespace NS_Model 
	{ 
		class OGLModel;
	}
}

// �Q�[���I�u�W�F�N�g�Ǘ��N���X
namespace NS_OpenGLWindowPCGame { class GameObjectManager; }



//==================================================================================================================================
// ���O���
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �Q�[�����O���
//
// @extends / GameObject : �Q�[���I�u�W�F�N�g�N���X
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
// @purpose : �v���C���[�N���X
//
// @note : 
//
// �v���C���[���\������N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class Player : public GameObject
{
public:

	// �R���X�g���N�^
	Player( 
		ChaseCamera*							pChaseCamera,
		const NS_Resource::NS_Model::OGLModel*	pPlayerModel,
		const NS_Resource::NS_Model::OGLModel*	pBulletModel,
		GameObjectManager*						pGameObjectManager,
		const char*								strSEShotName,
		const char*								strSEHitName
	);

	// �f�X�g���N�^
	~Player();
	


	// �X�V����
	void Update();

	// �`�揈��
	void Draw();



	// ����������
	void Initialize(
		const float			fMoveSpeed, 
		const Vector3DF&	vec3Position,
		const Vector3DF&	vec3Rotation, 
		const Vector3DF&	vec3Scale,
		const Vector3DF&	vec3RotationAngleSpeed
	);

private:
	
	// �Փ˒�����
	void OnColliding( const GameObject& gameObject );



	// �O�Ɉړ�������͂���������?
	bool IsInputMoveForward() const;

	// ���Ɉړ�������͂���������?
	bool IsInputMoveBack() const;

	// �E�Ƀ��[��]������͂���������?
	bool IsInputYawRotationRight() const;
	
	// ���Ƀ��[��]������͂���������?
	bool IsInputYawRotationLeft() const;
	
	// ��Ƀs�b�`��]������͂���������?
	bool IsInputPitchRotationUp() const;
	
	// ���Ƀs�b�`��]������͂���������?
	bool IsInputPitchRotationDown() const;

	
	
	// �e�𔭎˂�����͂���������?
	bool IsInputShoot() const;



	// �ړ�����
	void Move();

	// �e���ˊJ�n����
	void ShootStart();

private:

	// �����o�ϐ�

	// �ړ��̑���
	float										m_fMoveSpeed;

	// �e��]���̉�]�̑���
	Vector3DF									m_vec3RotationAngleSpeed;

	// �ړ������x�N�g��
	Vector3DF									m_vec3MoveDirection;

	// �v���C���[�̃��f��
	const NS_Resource::NS_Model::OGLModel*		m_pPlayerModel;

	// �e�̃��f��
	const NS_Resource::NS_Model::OGLModel*		m_pBulletModel;

	// �ǐՃJ����
	ChaseCamera*								m_pChaseCamera;

	// �Q�[���I�u�W�F�N�g�Ǘ��N���X
	GameObjectManager*							m_pGameObjectManager;

	// ���˂�SE��
	const char*									m_strSEShotName;

	// �e�̏Փ˂�SE��
	const char*									m_strSEHitName;
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_PLAYER_H_