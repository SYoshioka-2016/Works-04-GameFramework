#ifndef _INCLUDE_GUARD_GAMEOBJECTREMOVE_H_
#define _INCLUDE_GUARD_GAMEOBJECTREMOVE_H_



//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_GAMEOBJECT_H_
#include "GameObject.h"
#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECT_H_



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
// @purpose : �Q�[���I�u�W�F�N�g�폜�N���X
//
// @note : 
//
// �Q�[���I�u�W�F�N�g�N���X�����X�g����폜����ׂ̃N���X�B
//----------------------------------------------------------------------------------------------------------------------------------
class GameObjectRemove 
{
public:

	// ()���Z�q�I�[�o�[���[�h
	bool operator () ( GameObject* pGameObject )
	{
		if ( pGameObject->IsDestroy() )
		{
			SAFE_DELETE( pGameObject );

			return true;
		}
		


		return false;
	}
};



}	// namespace NS_OpenGLWindowPCGame



#endif	// #ifndef _INCLUDE_GUARD_GAMEOBJECTREMOVE_H_